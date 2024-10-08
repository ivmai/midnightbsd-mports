
PORTNAME=	netio
PORTVERSION=	1.32
CATEGORIES=	benchmarks net ipv6
MASTER_SITES=	FREEBSD_LOCAL/arved
DISTNAME=	netio132

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Network benchmark

LICENSE=	netio
LICENSE_NAME=	netio license
LICENSE_FILE=	${WRKSRC}/netio.doc
LICENSE_PERMS=	dist-mirror pkg-mirror

RESTRICTED=	No commercial use

WRKSRC=		${WRKDIR}
USES=		gmake zip
PATCH_ARGS=	-d ${PATCH_WRKSRC} -N -s -E ${PATCH_STRIP} -l
PLIST_FILES=	bin/netio

CFLAGS+=	-DUNIX -DSOCKLEN_T
LIBS+=		-pthread
MAKE_ENV+=	OUT=-o

OPTIONS_DEFINE=	IPV6
IPV6_PLIST_FILES=	bin/netio6

.include <bsd.mport.options.mk>

do-build:
	@(cd ${WRKSRC} && \
	${SETENV} ${MAKE_ENV} O=.o CFLAGS="${CFLAGS}" ${MAKE_CMD} all)
.if ${PORT_OPTIONS:MIPV6}
	@(cd ${WRKSRC} && \
	${MAKE_ENV} O=.6o X=6 CFLAGS="${CFLAGS} -DUSE_IPV6" ${MAKE_CMD} all)
.endif

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/netio ${STAGEDIR}${PREFIX}/bin
.if ${PORT_OPTIONS:MIPV6}
	${INSTALL_PROGRAM} ${WRKSRC}/netio6 ${STAGEDIR}${PREFIX}/bin
.endif

.include <bsd.port.mk>
