PORTNAME=	qhull
DISTVERSION=	8.0.2
PORTREVISION=	3
PORTEPOCH=	1
CATEGORIES=	math
MASTER_SITES=	http://www.qhull.org/download/
DISTNAME=	${PORTNAME}-2020-src-${DISTVERSION}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Qhull computes convex hulls, Delaunay triangulations, and halfspaces
WWW=		http://www.qhull.org

LICENSE=	Qhull
LICENSE_NAME=	Qhull License
LICENSE_FILE=	${WRKSRC}/COPYING.txt
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

USES=		cmake tar:tgz
USE_LDCONFIG=	yes
CFLAGS+=	-fPIC

CONFLICTS=	afni qhull7

WRKSRC=		${WRKDIR}/${PORTNAME}-2020.2

OPTIONS_DEFINE=	DOCS

PORTDOCS=	*

DOCS_EXTRA_PATCHES_OFF=	${PATCHDIR}/extra-patch-CMakeLists.txt

.include <bsd.port.mk>
