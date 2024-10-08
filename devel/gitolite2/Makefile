PORTNAME=	gitolite
PORTVERSION=	2.3.1
DISTVERSIONPREFIX=	v
CATEGORIES=	devel
PKGNAMESUFFIX=	2

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Access control layer on top of git
WWW=		https://github.com/sitaramc/gitolite/tree/g2

LICENSE=	gpl2
LICENSE_FILE=	${WRKSRC}/doc/COPYING

RUN_DEPENDS=	git>=0:devel/git

USE_GITHUB=	yes
GH_ACCOUNT=	sitaramc

CONFLICTS=	gitolite-[^2]*

USES=		cpe perl5 shebangfix
SHEBANG_FILES=	hooks/common/update \
		src/gl-admin-push \
		src/gl-auth-command \
		src/gl-compile-conf \
		src/gl-conf-convert \
		src/gl-dryrun \
		src/gl-install \
		src/gl-mirror-push \
		src/gl-mirror-shell \
		src/gl-query-rc \
		src/gl-setup \
		src/gl-setup-authkeys \
		src/gl-time \
		src/gl-tool \
		src/sshkeys-lint
NO_ARCH=	yes

SUB_FILES=	pkg-message

OPTIONS_DEFINE=	GITUSER
OPTIONS_SUB=	yes

GITUSER_DESC=	Create git user as gitolite provider
GITUSER_VARS=	USERS=git GROUPS=git

GLAUTHCOMMAND=	\
\#!/bin/sh\n \
exec ${PREFIX}/libexec/gitolite/gl-auth-command \"\$$@\"\n

GLSETUP=	\
\#!/bin/sh\n \
exec ${PREFIX}/libexec/gitolite/gl-setup \"\$$@\"\n

post-patch:
	@${ECHO} -e "${GLAUTHCOMMAND}" > ${WRKDIR}/auth-command
	@${ECHO} -e "${GLSETUP}" > ${WRKDIR}/setup

do-build:
	echo "v${PORTVERSION}-0-g${GH_TAGNAME}" > ${WRKSRC}/conf/VERSION
	-@${RM} ${WRKSRC}/src/gl-system-install
	@${REINPLACE_CMD} \
		-E 's%^GL_PACKAGE_CONF=.*%GL_PACKAGE_CONF=${DATADIR}/conf;%' \
		${WRKSRC}/src/gl-setup
	@${REINPLACE_CMD} \
		-E "s%^[[:blank:]]*\\\$$GL_PACKAGE_CONF[[:blank:]]*=.*%\$$GL_PACKAGE_CONF = '${DATADIR}/conf';%" \
		${WRKSRC}/conf/example.gitolite.rc
	@${REINPLACE_CMD} \
		-E "s%^[[:blank:]]*\\\$$GL_PACKAGE_HOOKS[[:blank:]]*=.*%\$$GL_PACKAGE_HOOKS = '${DATADIR}/hooks';%" \
		${WRKSRC}/conf/example.gitolite.rc

post-build:
	@${FIND} ${WRKSRC} -name "*.bak" -delete
	@${FIND} ${WRKSRC} -name "*.orig" -delete

do-install:
	@${MKDIR} ${PREFIX}/libexec/gitolite
	${INSTALL_SCRIPT} ${WRKSRC}/src/* ${PREFIX}/libexec/gitolite/
	@${MKDIR} ${DATADIR}/conf
	${INSTALL_DATA} ${WRKSRC}/conf/* ${DATADIR}/conf
	@${MKDIR} ${DATADIR}/hooks
	(cd ${WRKSRC}/hooks && ${COPYTREE_BIN} \* ${DATADIR}/hooks)
	${INSTALL_SCRIPT} ${WRKDIR}/auth-command ${PREFIX}/bin/gl-auth-command
	${INSTALL_SCRIPT} ${WRKDIR}/setup ${PREFIX}/bin/gl-setup

.include <bsd.port.mk>
