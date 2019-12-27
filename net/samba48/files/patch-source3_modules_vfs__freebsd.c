--- /dev/null	2018-11-29 02:13:13 UTC
+++ source3/modules/vfs_freebsd.c
@@ -0,0 +1,795 @@
+/*
+ * This module implements VFS calls specific to FreeBSD
+ *
+ * Copyright (C) Timur I. Bakeyev, 2018
+ *
+ * This program is free software; you can redistribute it and/or modify
+ * it under the terms of the GNU General Public License as published by
+ * the Free Software Foundation; either version 3 of the License, or
+ * (at your option) any later version.
+ *  
+ * This program is distributed in the hope that it will be useful,
+ * but WITHOUT ANY WARRANTY; without even the implied warranty of
+ * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+ * GNU General Public License for more details.
+ *  
+ * You should have received a copy of the GNU General Public License
+ * along with this program; if not, see <http://www.gnu.org/licenses/>.
+ */
+
+#include "includes.h"
+
+#include "lib/util/tevent_unix.h"
+#include "lib/util/tevent_ntstatus.h"
+#include "system/filesys.h"
+
+#include <sys/sysctl.h>
+
+static int vfs_freebsd_debug_level = DBGC_VFS;
+
+#undef DBGC_CLASS
+#define DBGC_CLASS vfs_freebsd_debug_level
+
+#ifndef EXTATTR_MAXNAMELEN
+#define EXTATTR_MAXNAMELEN		UINT8_MAX
+#endif
+
+#define EXTATTR_NAMESPACE(NS)		EXTATTR_NAMESPACE_ ## NS, \
+					EXTATTR_NAMESPACE_ ## NS ## _STRING ".", \
+					.data.len = (sizeof(EXTATTR_NAMESPACE_ ## NS ## _STRING ".") - 1)
+
+#define EXTATTR_EMPTY			0x00
+#define EXTATTR_USER			0x01
+#define EXTATTR_SYSTEM			0x02
+#define EXTATTR_SECURITY		0x03
+#define EXTATTR_TRUSTED			0x04
+
+enum extattr_mode {
+	FREEBSD_EXTATTR_SECURE,
+	FREEBSD_EXTATTR_COMPAT,
+	FREEBSD_EXTATTR_LEGACY
+};
+
+typedef struct {
+	int namespace;
+	char name[EXTATTR_MAXNAMELEN+1];
+	union {
+		uint16_t len;
+		uint16_t flags;
+	} data;
+} extattr_attr;
+
+typedef struct {
+	enum {
+		EXTATTR_FILE, EXTATTR_LINK, EXTATTR_FDES
+	} method;
+	union {
+		const char *path;
+		int filedes;
+	} param;
+} extattr_arg;
+
+static const struct enum_list extattr_mode_param[] = {
+	{ FREEBSD_EXTATTR_SECURE, "secure" },		/*  */
+	{ FREEBSD_EXTATTR_COMPAT, "compat" },		/*  */
+	{ FREEBSD_EXTATTR_LEGACY, "legacy" },		/*  */
+	{ -1, NULL }
+};
+
+
+/* */
+struct freebsd_handle_data {
+	enum extattr_mode extattr_mode;
+};
+
+
+/* XXX: This order doesn't match namespace ids order! */
+static extattr_attr extattr[] = {
+	{ EXTATTR_NAMESPACE(EMPTY) },
+	{ EXTATTR_NAMESPACE(SYSTEM) },
+	{ EXTATTR_NAMESPACE(USER) },
+};
+
+
+static bool freebsd_in_jail(void) {
+	int val = 0;
+	size_t val_len = sizeof(val);
+
+	if((sysctlbyname("security.jail.jailed", &val, &val_len, NULL, 0) != -1) && val == 1) {
+		return true;
+	}
+	return false;
+}
+
+static uint16_t freebsd_map_attrname(const char *name)
+{
+	if(name == NULL || name[0] == '\0') {
+		return EXTATTR_EMPTY;
+	}
+
+	switch(name[0]) {
+		case 'u':
+			if(strncmp(name, "user.", 5) == 0)
+				return EXTATTR_USER;
+			break;
+		case 't':
+			if(strncmp(name, "trusted.", 8) == 0)
+				return EXTATTR_TRUSTED;
+			break;
+		case 's':
+			/* name[1] could be any character, including '\0' */
+			switch(name[1]) {
+				case 'e':
+					if(strncmp(name, "security.", 9) == 0)
+						return EXTATTR_SECURITY;
+					break;
+				case 'y':
+					if(strncmp(name, "system.", 7) == 0)
+						return EXTATTR_SYSTEM;
+					break;
+			}
+			break;
+	}
+	return EXTATTR_USER;
+}
+
+/* security, system, trusted or user */
+static extattr_attr* freebsd_map_xattr(enum extattr_mode extattr_mode, const char *name, extattr_attr *attr)
+{
+	int attrnamespace = EXTATTR_NAMESPACE_EMPTY;
+	const char *attrname = name;
+
+	if(name == NULL || name[0] == '\0') {
+		return NULL;
+	}
+
+	if(attr == NULL) {
+		return NULL;
+	}
+
+	uint16_t flags = freebsd_map_attrname(name);
+
+	switch(flags) {
+		case EXTATTR_USER:
+			attrnamespace = EXTATTR_NAMESPACE_USER;
+			if(extattr_mode == FREEBSD_EXTATTR_LEGACY)
+				attrname = name + 5;
+			break;
+		case EXTATTR_SECURITY:
+		case EXTATTR_TRUSTED:
+			attrnamespace = (extattr_mode == FREEBSD_EXTATTR_SECURE) ?
+					EXTATTR_NAMESPACE_SYSTEM :
+					EXTATTR_NAMESPACE_USER;
+			break;
+		case EXTATTR_SYSTEM:
+			attrnamespace = (extattr_mode == FREEBSD_EXTATTR_SECURE) ?
+					EXTATTR_NAMESPACE_SYSTEM :
+					EXTATTR_NAMESPACE_USER;
+			if (extattr_mode == FREEBSD_EXTATTR_LEGACY)
+				attrname = name + 7;
+			break;
+		default:
+			/* Default to "user" namespace if nothing else was specified */
+			attrnamespace = EXTATTR_NAMESPACE_USER;
+			flags = EXTATTR_USER;
+	}
+
+	attr->namespace = attrnamespace;
+	attr->data.flags = flags;
+	strlcpy(attr->name, attrname, EXTATTR_MAXNAMELEN+1);
+
+	return attr;
+}
+
+static ssize_t extattr_size(extattr_arg arg, extattr_attr *attr)
+{
+	ssize_t result;
+
+	switch(arg.method) {
+#if defined(HAVE_EXTATTR_GET_FILE)
+		case EXTATTR_FILE:
+			result = extattr_get_file(arg.param.path, attr->namespace, attr->name, NULL, 0);
+			break;
+#endif
+#if defined(HAVE_EXTATTR_GET_LINK)
+		case EXTATTR_LINK:
+			result = extattr_get_link(arg.param.path, attr->namespace, attr->name, NULL, 0);
+			break;
+#endif
+#if defined(HAVE_EXTATTR_GET_FD)
+		case EXTATTR_FDES:
+			result = extattr_get_fd(arg.param.filedes, attr->namespace, attr->name, NULL, 0);
+			break;
+#endif
+		default:
+			errno = ENOSYS;
+			return -1;
+	}
+
+	if(result < 0) {
+		errno = EINVAL;
+		return -1;
+	}
+
+	return result;
+}
+
+
+/*
+ * The list of names is returned as an unordered array of NULL-terminated
+ * character strings (attribute names are separated by NULL characters),
+ * like this:
+ *      user.name1\0system.name1\0user.name2\0
+ *
+ * Filesystems like ext2, ext3 and XFS which implement POSIX ACLs using
+ * extended attributes, might return a list like this:
+ *      system.posix_acl_access\0system.posix_acl_default\0
+ */
+/*
+ * The extattr_list_file() returns a list of attributes present in the
+ * requested namespace. Each list entry consists of a single byte containing
+ * the length of the attribute name, followed by the attribute name. The
+ * attribute name is not terminated by ASCII 0 (nul).
+*/
+
+static ssize_t freebsd_extattr_list(extattr_arg arg, enum extattr_mode extattr_mode, char *list, size_t size)
+{
+	ssize_t list_size, total_size = 0;
+	char *p, *q, *list_end;
+	int len;
+	/*
+	 Ignore all but user namespace when we are not root or in jail
+	 See: https://bugzilla.samba.org/show_bug.cgi?id=10247
+	*/
+	bool as_root = (geteuid() == 0);
+
+	int ns = (extattr_mode == FREEBSD_EXTATTR_SECURE && as_root) ? 1 : 2;
+
+	/* Iterate through extattr(2) namespaces */
+	for(; ns < ARRAY_SIZE(extattr); ns++) {
+		switch(arg.method) {
+#if defined(HAVE_EXTATTR_LIST_FILE)
+			case EXTATTR_FILE:
+				list_size = extattr_list_file(arg.param.path, extattr[ns].namespace, list, size);
+				break;
+#endif
+#if defined(HAVE_EXTATTR_LIST_LINK)
+			case EXTATTR_LINK:
+				list_size = extattr_list_link(arg.param.path, extattr[ns].namespace, list, size);
+				break;
+#endif
+#if defined(HAVE_EXTATTR_LIST_FD)
+			case EXTATTR_FDES:
+				list_size = extattr_list_fd(arg.param.filedes, extattr[ns].namespace, list, size);
+				break;
+#endif
+			default:
+				errno = ENOSYS;
+				return -1;
+		}
+		/* Some error happend. Errno should be set by the previous call */
+		if(list_size < 0)
+			return -1;
+		/* No attributes in this namespace */
+		if(list_size == 0)
+			continue;
+		/*
+		 Call with an empty buffer may be used to calculate
+		 necessary buffer size.
+		*/
+		if(list == NULL) {
+			/*
+			 XXX: Unfortunately, we can't say, how many attributes were
+			 returned, so here is the potential problem with the emulation.
+			*/
+			if(extattr_mode == FREEBSD_EXTATTR_LEGACY) {
+				/*
+				 Take the worse case of one char attribute names -
+				 two bytes per name plus one more for sanity.
+				*/
+				total_size += list_size + (list_size/2 + 1)*extattr[ns].data.len;
+			}
+			else {
+				total_size += list_size;
+			}
+			continue;
+		}
+
+		if(extattr_mode == FREEBSD_EXTATTR_LEGACY) {
+			/* Count necessary offset to fit namespace prefixes */
+			int extra_len = 0;
+			uint16_t flags;
+			list_end = list + list_size;
+			for(list_size = 0, p = q = list; p < list_end; p += len) {
+				len = p[0] + 1;
+				(void)strlcpy(q, p + 1, len);
+				flags = freebsd_map_attrname(q);
+				/* Skip secure attributes for non-root user */
+				if(extattr_mode != FREEBSD_EXTATTR_SECURE && !as_root && flags > EXTATTR_USER) {
+					continue;
+				}
+				if(flags <= EXTATTR_USER) {
+					/* Don't count trailing '\0' */
+					extra_len += extattr[ns].data.len;
+				}
+				list_size += len;
+				q += len;
+			}
+			total_size += list_size + extra_len;
+			/* Buffer is too small to fit the results */
+			if(total_size > size) {
+				errno = ERANGE;
+				return -1;
+			}
+			/* Shift results backwards, so we can prepend prefixes */
+			list_end = list + extra_len;
+			p = (char*)memmove(list_end, list, list_size);
+			/*
+			 We enter the loop with `p` pointing to the shifted list and
+			 `extra_len` having the total margin between `list` and `p`
+			*/
+			for(list_end += list_size; p < list_end; p += len) {
+				len = strlen(p) + 1;
+				flags = freebsd_map_attrname(p);
+				if(flags <= EXTATTR_USER) {
+					/* Add namespace prefix */
+					(void)strncpy(list, extattr[ns].name, extattr[ns].data.len);
+					list += extattr[ns].data.len;
+				}
+				/* Append attribute name */
+				(void)strlcpy(list, p, len);
+				list += len;
+			}
+		}
+		else {
+			/* Convert UCSD strings into nul-terminated strings */
+			for(list_end = list + list_size; list < list_end; list += len) {
+				len = list[0] + 1;
+				(void)strlcpy(list, list + 1, len);
+			}
+			total_size += list_size;
+		}
+	}
+	return total_size;
+}
+
+/*
+static ssize_t freebsd_getxattr_size(vfs_handle_struct *handle,
+				const struct smb_filename *smb_fname,
+				const char *name)
+{
+	struct freebsd_handle_data *data;
+	extattr_arg arg = { EXTATTR_FILE, smb_fname->base_name };
+	extattr_attr attr;
+
+
+	SMB_VFS_HANDLE_GET_DATA(handle, data,
+				struct freebsd_handle_data,
+				return -1);
+
+	if(!freebsd_map_xattr(data->extattr_mode, name, &attr)) {
+		errno = EINVAL;
+		return -1;
+	}
+
+	if(data->extattr_mode != FREEBSD_EXTATTR_SECURE && geteuid() != 0 && attr.data.flags > EXTATTR_USER) {
+		errno = ENOATTR;
+		return -1;
+	}
+
+	return extattr_size(arg, &attr);
+}
+*/
+
+/* VFS entries */
+static ssize_t freebsd_getxattr(vfs_handle_struct *handle,
+				const struct smb_filename *smb_fname,
+				const char *name,
+				void *value,
+				size_t size)
+{
+#if defined(HAVE_EXTATTR_GET_FILE)
+	struct freebsd_handle_data *data;
+	extattr_arg arg = { EXTATTR_FILE, .param.path = smb_fname->base_name };
+	extattr_attr attr;
+	ssize_t res;
+
+	SMB_VFS_HANDLE_GET_DATA(handle, data,
+				struct freebsd_handle_data,
+				return -1);
+
+	if(!freebsd_map_xattr(data->extattr_mode, name, &attr)) {
+		errno = EINVAL;
+		return -1;
+	}
+
+	/* Filter out 'secure' entries */
+	if(data->extattr_mode != FREEBSD_EXTATTR_SECURE && geteuid() != 0 && attr.data.flags > EXTATTR_USER) {
+		errno = ENOATTR;
+		return -1;
+	}
+
+	/*
+	 * The BSD implementation has a nasty habit of silently truncating
+	 * the returned value to the size of the buffer, so we have to check
+	 * that the buffer is large enough to fit the returned value.
+	 */
+	if((res=extattr_size(arg, &attr)) < 0) {
+		return -1;
+	}
+
+	if (size == 0) {
+		return res;
+	}
+	else if (res > size) {
+		errno = ERANGE;
+		return -1;
+	}
+
+	if((res=extattr_get_file(smb_fname->base_name, attr.namespace, attr.name, value, size)) >= 0) {
+		return res;
+	}
+	return -1;
+#else
+	errno = ENOSYS;
+	return -1;
+#endif
+}
+
+
+static ssize_t freebsd_fgetxattr(vfs_handle_struct *handle,
+			      struct files_struct *fsp, const char *name,
+			      void *value, size_t size)
+{
+#if defined(HAVE_EXTATTR_GET_FD)
+	struct freebsd_handle_data *data;
+	extattr_arg arg = { EXTATTR_FDES, .param.filedes = fsp->fh->fd };
+	extattr_attr attr;
+	ssize_t res;
+
+	SMB_VFS_HANDLE_GET_DATA(handle, data,
+				struct freebsd_handle_data,
+				return -1);
+
+	if(!freebsd_map_xattr(data->extattr_mode, name, &attr)) {
+		errno = EINVAL;
+		return -1;
+	}
+
+	/* Filter out 'secure' entries */
+	if(data->extattr_mode != FREEBSD_EXTATTR_SECURE && geteuid() != 0 && attr.data.flags > EXTATTR_USER) {
+		errno = ENOATTR;
+		return -1;
+	}
+
+	/*
+	 * The BSD implementation has a nasty habit of silently truncating
+	 * the returned value to the size of the buffer, so we have to check
+	 * that the buffer is large enough to fit the returned value.
+	 */
+	if((res=extattr_size(arg, &attr)) < 0) {
+		return -1;
+	}
+
+	if (size == 0) {
+		return res;
+	}
+	else if (res > size) {
+		errno = ERANGE;
+		return -1;
+	}
+
+	if((res=extattr_get_fd(fsp->fh->fd, attr.namespace, attr.name, value, size)) >= 0) {
+		return res;
+	}
+	return -1;
+#else
+	errno = ENOSYS;
+	return -1;
+#endif
+}
+
+
+static ssize_t freebsd_listxattr(vfs_handle_struct *handle,
+				const struct smb_filename *smb_fname,
+				char *list,
+				size_t size)
+{
+#if defined(HAVE_EXTATTR_LIST_FILE)
+	struct freebsd_handle_data *data;
+
+	SMB_VFS_HANDLE_GET_DATA(handle, data,
+				struct freebsd_handle_data,
+				return -1);
+
+	extattr_arg arg = { EXTATTR_FILE, .param.path = smb_fname->base_name };
+
+	return freebsd_extattr_list(arg, data->extattr_mode, list, size);
+#else
+	errno = ENOSYS;
+	return -1;
+#endif
+}
+
+
+static ssize_t freebsd_flistxattr(vfs_handle_struct *handle,
+			       struct files_struct *fsp, char *list,
+			       size_t size)
+{
+#if defined(HAVE_EXTATTR_LIST_FD)
+	struct freebsd_handle_data *data;
+	extattr_arg arg = { EXTATTR_FDES, .param.filedes = fsp->fh->fd };
+
+	SMB_VFS_HANDLE_GET_DATA(handle, data,
+				struct freebsd_handle_data,
+				return -1);
+
+	return freebsd_extattr_list(arg, data->extattr_mode, list, size);
+#else
+	errno = ENOSYS;
+	return -1;
+#endif
+}
+
+static int freebsd_removexattr(vfs_handle_struct *handle,
+			const struct smb_filename *smb_fname,
+			const char *name)
+{
+#if defined(HAVE_EXTATTR_DELETE_FILE)
+	struct freebsd_handle_data *data;
+	extattr_attr attr;
+
+	SMB_VFS_HANDLE_GET_DATA(handle, data,
+				struct freebsd_handle_data,
+				return -1);
+
+
+	/* Filter out 'secure' entries */
+	if(data->extattr_mode != FREEBSD_EXTATTR_SECURE && geteuid() != 0 && attr.data.flags > EXTATTR_USER) {
+		errno = ENOATTR;
+		return -1;
+	}
+
+	return extattr_delete_file(smb_fname->base_name, attr.namespace, attr.name);
+#else
+	errno = ENOSYS;
+	return -1;
+#endif
+}
+
+
+static int freebsd_fremovexattr(vfs_handle_struct *handle,
+			     struct files_struct *fsp, const char *name)
+{
+#if defined(HAVE_EXTATTR_DELETE_FD)
+	struct freebsd_handle_data *data;
+	extattr_attr attr;
+
+	SMB_VFS_HANDLE_GET_DATA(handle, data,
+				struct freebsd_handle_data,
+				return -1);
+
+	if(!freebsd_map_xattr(data->extattr_mode, name, &attr)) {
+		errno = EINVAL;
+		return -1;
+	}
+
+	/* Filter out 'secure' entries */
+	if(data->extattr_mode != FREEBSD_EXTATTR_SECURE && geteuid() != 0 && attr.data.flags > EXTATTR_USER) {
+		errno = ENOATTR;
+		return -1;
+	}
+
+	return extattr_delete_fd(fsp->fh->fd, attr.namespace, attr.name);
+#else
+	errno = ENOSYS;
+	return -1;
+#endif
+}
+
+
+static int freebsd_setxattr(vfs_handle_struct *handle,
+			const struct smb_filename *smb_fname,
+			const char *name,
+			const void *value,
+			size_t size,
+			int flags)
+{
+#if defined(HAVE_EXTATTR_SET_FILE)
+	struct freebsd_handle_data *data;
+	extattr_attr attr;
+	ssize_t res;
+
+	SMB_VFS_HANDLE_GET_DATA(handle, data,
+				struct freebsd_handle_data,
+				return -1);
+
+	if(!freebsd_map_xattr(data->extattr_mode, name, &attr)) {
+		errno = EINVAL;
+		return -1;
+	}
+
+	/* Filter out 'secure' entries */
+	if(data->extattr_mode != FREEBSD_EXTATTR_SECURE && geteuid() != 0 && attr.data.flags > EXTATTR_USER) {
+		errno = ENOATTR;
+		return -1;
+	}
+
+	if (flags) {
+		extattr_arg arg = { EXTATTR_FILE, .param.path = smb_fname->base_name };
+		/* Check attribute existence */
+		res = extattr_size(arg, &attr);
+		if (res < 0) {
+			/* REPLACE attribute, that doesn't exist */
+			if ((flags & XATTR_REPLACE) && errno == ENOATTR) {
+				errno = ENOATTR;
+				return -1;
+			}
+			/* Ignore other errors */
+		}
+		else {
+			/* CREATE attribute, that already exists */
+			if (flags & XATTR_CREATE) {
+				errno = EEXIST;
+				return -1;
+			}
+		}
+	}
+	res = extattr_set_file(smb_fname->base_name, attr.namespace, attr.name, value, size);
+
+	return (res >= 0) ? 0 : -1;
+#else
+	errno = ENOSYS;
+	return -1;
+#endif
+}
+
+
+static int freebsd_fsetxattr(vfs_handle_struct *handle, struct files_struct *fsp,
+			  const char *name, const void *value, size_t size,
+			  int flags)
+{
+#if defined(HAVE_EXTATTR_SET_FD)
+	struct freebsd_handle_data *data;
+	extattr_attr attr;
+	ssize_t res;
+
+	SMB_VFS_HANDLE_GET_DATA(handle, data,
+				struct freebsd_handle_data,
+				return -1);
+
+	if(!freebsd_map_xattr(data->extattr_mode, name, &attr)) {
+		errno = EINVAL;
+		return -1;
+	}
+
+	/* Filter out 'secure' entries */
+	if(data->extattr_mode != FREEBSD_EXTATTR_SECURE && geteuid() != 0 && attr.data.flags > EXTATTR_USER) {
+		errno = ENOATTR;
+		return -1;
+	}
+
+	if (flags) {
+		extattr_arg arg = { EXTATTR_FDES, .param.filedes = fsp->fh->fd };
+		/* Check attribute existence */
+		res = extattr_size(arg, &attr);
+		if (res < 0) {
+			/* REPLACE attribute, that doesn't exist */
+			if ((flags & XATTR_REPLACE) && errno == ENOATTR) {
+				errno = ENOATTR;
+				return -1;
+			}
+			/* Ignore other errors */
+		}
+		else {
+			/* CREATE attribute, that already exists */
+			if (flags & XATTR_CREATE) {
+				errno = EEXIST;
+				return -1;
+			}
+		}
+	}
+
+	res = extattr_set_fd(fsp->fh->fd, attr.namespace, attr.name, value, size);
+
+	return (res >= 0) ? 0 : -1;
+#else
+	errno = ENOSYS;
+	return -1;
+#endif
+}
+
+static int freebsd_connect(vfs_handle_struct *handle, const char *service,
+			const char *user)
+{
+	struct freebsd_handle_data *data;
+	int enumval, saved_errno;
+
+	int ret = SMB_VFS_NEXT_CONNECT(handle, service, user);
+
+	if (ret < 0) {
+		return ret;
+	}
+
+	data = talloc_zero(handle->conn, struct freebsd_handle_data);
+	if (!data) {
+		saved_errno = errno;
+		SMB_VFS_NEXT_DISCONNECT(handle);
+		DEBUG(0, ("talloc_zero() failed\n"));
+		errno = saved_errno;
+		return -1;
+	}
+
+	enumval = lp_parm_enum(SNUM(handle->conn), "freebsd",
+			       "extattr mode", extattr_mode_param, FREEBSD_EXTATTR_LEGACY);
+	if (enumval == -1) {
+		saved_errno = errno;
+		SMB_VFS_NEXT_DISCONNECT(handle);
+		DBG_DEBUG("value for freebsd: 'extattr mode' is unknown\n");
+		errno = saved_errno;
+		return -1;
+	}
+
+	if(freebsd_in_jail()) {
+		enumval = FREEBSD_EXTATTR_COMPAT;
+		DBG_WARNING("running in jail, enforcing 'compat' mode\n");
+	}
+
+	data->extattr_mode = (enum extattr_mode)enumval;
+
+	SMB_VFS_HANDLE_SET_DATA(handle, data, NULL,
+				struct freebsd_handle_data,
+				return -1);
+
+	DBG_DEBUG("connect to service[%s] with '%s' extattr mode\n",
+		  service, extattr_mode_param[data->extattr_mode].name);
+
+	return 0;
+}
+
+static void freebsd_disconnect(vfs_handle_struct *handle)
+{
+	SMB_VFS_NEXT_DISCONNECT(handle);
+}
+
+/* VFS operations structure */
+
+struct vfs_fn_pointers freebsd_fns = {
+	/* Disk operations */
+
+	.connect_fn = freebsd_connect,
+	.disconnect_fn = freebsd_disconnect,
+
+	/* EA operations. */
+	.getxattr_fn = freebsd_getxattr,
+	.fgetxattr_fn = freebsd_fgetxattr,
+	.listxattr_fn = freebsd_listxattr,
+	.flistxattr_fn = freebsd_flistxattr,
+	.removexattr_fn = freebsd_removexattr,
+	.fremovexattr_fn = freebsd_fremovexattr,
+	.setxattr_fn = freebsd_setxattr,
+	.fsetxattr_fn = freebsd_fsetxattr,
+};
+
+static_decl_vfs;
+NTSTATUS vfs_freebsd_init(TALLOC_CTX *ctx)
+{
+	NTSTATUS ret;
+
+	ret = smb_register_vfs(SMB_VFS_INTERFACE_VERSION, "freebsd",
+				&freebsd_fns);
+
+	if (!NT_STATUS_IS_OK(ret)) {
+		return ret;
+	}
+
+	vfs_freebsd_debug_level = debug_add_class("freebsd");
+	if (vfs_freebsd_debug_level == -1) {
+		vfs_freebsd_debug_level = DBGC_VFS;
+		DEBUG(0, ("vfs_freebsd: Couldn't register custom debugging class!\n"));
+	} else {
+		DEBUG(10, ("vfs_freebsd: Debug class number of 'fileid': %d\n", vfs_freebsd_debug_level));
+	}
+
+	return ret;
+}
