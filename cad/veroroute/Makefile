PORTNAME=	veroroute
DISTVERSION=	2.39
CATEGORIES=	cad
MASTER_SITES=	SF/${PORTNAME}/

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	PCB (printed circuit board) design software
WWW=		https://sourceforge.net/projects/veroroute/

LICENSE=	gpl3
LICENSE_FILE=	${WRKSRC}/../licenses/license_GPLv3.txt

USES=		compiler:c++11-lang gl qmake qt:5
USE_QT=		core gui network widgets buildtools:build
USE_GL=		gl

WRKSRC=		${WRKDIR}/VeroRoute
WRKSRC_SUBDIR=	Src

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/veroroute

.include <bsd.port.mk>
