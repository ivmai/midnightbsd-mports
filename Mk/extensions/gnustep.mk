# $MidnightBSD$
# $FreeBSD: head/Mk/Uses/gnustep.mk 383626 2015-04-09 07:44:41Z bapt $
#
# Handle GNUstep related ports
#
# Feature:	gnustep
# Usage:	USES=gnustep
#
# Defined specific dependencies under USE_GNUSTEP
# Expected arguments for USE_GNUSTEP:
#
# base:		depends on the gnustep-base port
# gui:		depends on the gnustep-gui port
# back:		depends on the gnustep-back port
# build:	prepare the build dependencies for a regular GNUstep port
#

.if !defined(_INCLUDE_USES_GNUSTEP_MK)
_INCLUDE_USES_GNUSTEP_MK=	yes
.include "${PORTSDIR}/Mk/extensions/gmake.mk"

GNUSTEP_PREFIX?=	${LOCALBASE}/GNUstep
DEFAULT_LIBVERSION?=	0.0.1

GNUSTEP_SYSTEM_ROOT=		${GNUSTEP_PREFIX}/System
GNUSTEP_MAKEFILES=		${GNUSTEP_SYSTEM_ROOT}/Library/Makefiles
GNUSTEP_SYSTEM_LIBRARIES=	${GNUSTEP_SYSTEM_ROOT}/Library/Libraries
GNUSTEP_SYSTEM_TOOLS=		${GNUSTEP_SYSTEM_ROOT}/Tools

GNUSTEP_LOCAL_ROOT=	${GNUSTEP_PREFIX}/Local
GNUSTEP_LOCAL_LIBRARIES=	${GNUSTEP_LOCAL_ROOT}/Library/Libraries
GNUSTEP_LOCAL_TOOLS=		${GNUSTEP_LOCAL_ROOT}/Tools

LIB_DIRS+=	${GNUSTEP_SYSTEM_LIBRARIES} \
		${GNUSTEP_LOCAL_LIBRARIES}

.for a in FLAGS CFLAGS CPPFLAGS OBJCFLAGS INCLUDE_DIRS LDFLAGS LIB_DIRS
MAKE_ENV+=	ADDITIONAL_${a}="${ADDITIONAL_${a}}"
.endfor

MAKEFILE=	GNUmakefile
#MAKE_ENV+=	GNUSTEP_CONFIG_FILE=${PORTSDIR}/devel/gnustep-make/files/GNUstep.conf
GNU_CONFIGURE_PREFIX=	${GNUSTEP_PREFIX}

.if ${MACHINE_ARCH} == "i386"
GNU_ARCH=	ix86
.else
GNU_ARCH=	${MACHINE_ARCH}
.endif

PLIST_SUB+=	GNU_ARCH=${GNU_ARCH} VERSION=${PORTVERSION}
PLIST_SUB+=	MAJORVERSION=${PORTVERSION:C/([0-9]).*/\1/1}
PLIST_SUB+=	LIBVERSION=${DEFAULT_LIBVERSION}
PLIST_SUB+=	MAJORLIBVERSION=${DEFAULT_LIBVERSION:C/([0-9]).*/\1/1}

.if defined(USE_GNUSTEP)
.  if ${USE_GNUSTEP:Mbase}
LIB_DEPENDS+=	libgnustep-base.so:${PORTSDIR}/lang/gnustep-base
.  endif

.  if ${USE_GNUSTEP:Mbuild}
PATH:=	${GNUSTEP_SYSTEM_TOOLS}:${GNUSTEP_LOCAL_TOOLS}:${PATH}
MAKE_ENV+=	PATH="${PATH}" GNUSTEP_MAKEFILES="${GNUSTEP_MAKEFILES}" GNUSTEP_SYSTEM_ROOT="${GNUSTEP_SYSTEM_ROOT}"
CONFIGURE_ENV+=	PATH="${PATH}" GNUSTEP_MAKEFILES="${GNUSTEP_MAKEFILES}" GNUSTEP_SYSTEM_ROOT="${GNUSTEP_SYSTEM_ROOT}"
BUILD_DEPENDS+=	gnustep-make>0:${PORTSDIR}/devel/gnustep-make
.include "${PORTSDIR}/Mk/extensions/objc.mk"
.  endif

.  if ${USE_GNUSTEP:Mgui}
LIB_DEPENDS+=	libgnustep-gui.so:${PORTSDIR}/x11-toolkits/gnustep-gui
.  endif

.  if ${USE_GNUSTEP:Mback}
BUILD_DEPENDS+=	gnustep-back>0:${PORTSDIR}/x11-toolkits/gnustep-back
RUN_DEPENDS+=	gnustep-back>0:${PORTSDIR}/x11-toolkits/gnustep-back
.  endif

.endif

.endif
