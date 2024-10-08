PORTNAME=	openjdk8
PORTVERSION=	${DISTVERSION_${JDK_ARCH}}
CATEGORIES=	java devel
MASTER_SITES=	FREEBSD_LOCAL/jkim \
		FREEBSD_LOCAL/pkubaj
PKGNAMEPREFIX=	bootstrap-
DISTNAME=	${JDK_PORT}-${JDK_ARCH}-${PORTVERSION}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Java Development Kit 8
WWW=		https://openjdk.java.net/

LICENSE=	gpl2

ONLY_FOR_ARCHS=		aarch64 amd64 armv6 armv7 i386

DISTINFO_FILE=	${.CURDIR}/distinfo.${JDK_ARCH}
DISTVERSION_aarch64=	r453315
DISTVERSION_amd64=	r450802
DISTVERSION_arm=	r450802
DISTVERSION_i386=	r450802

JDK_ARCH=	${ARCH:C/armv.*/arm/:S/powerpc/ppc/}
JDK_PORT=	openjdk8
JDK_ROOT=	bootstrap-${PORTNAME}

NO_BUILD=	yes
PLIST_SUB=	JDK_ARCH=${JDK_ARCH} JDK_ROOT=${JDK_ROOT}
USES=		tar:xz
WRKSRC=		${WRKDIR}/${JDK_ROOT}

INSTALLDIR=	${STAGEDIR}${PREFIX}/${JDK_ROOT}

.include <bsd.port.pre.mk>

.if ${ARCH} == aarch64 || ${ARCH:Marmv*}
RUN_DEPENDS+=	${LOCALBASE}/lib/libffi.so.6:devel/libffi
.endif

do-install:
	@cd ${WRKSRC} && ${COPYTREE_SHARE} . ${INSTALLDIR}
	@cd ${WRKSRC} && ${COPYTREE_BIN} bin ${INSTALLDIR}
	${MKDIR} ${INSTALLDIR}/include/midnightbsd
	${CP} ${INSTALLDIR}/include/freebsd/jni_md.h ${INSTALLDIR}/include/midnightbsd/jni_md.h

update:
	@${MAKE} -f ${.CURDIR}/Makefile.update \
	    JDK_PORT=${JDK_PORT} JDK_ROOT=${JDK_ROOT}

.include <bsd.port.post.mk>
