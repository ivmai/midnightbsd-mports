PORTNAME=	yudit
PORTVERSION=	3.1.0
CATEGORIES=	editors converters print
MASTER_SITES=	http://yudit.org/download/ \
		SUNSITE/apps/editors/X

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Multi-lingual Unicode text editor with TTF support
WWW=		https://www.yudit.org/

LICENSE=	gpl2
LICENSE_FILE=	${WRKSRC}/COPYING.TXT

USES=		gmake xorg

CONFLICTS=	netatalk

USE_XORG=	x11
GNU_CONFIGURE=	yes
GNU_CONFIGURE_MANPREFIX=	${PREFIX}/share
MAKE_JOBS_UNSAFE=	yes

PORTDATA=	*

DESKTOP_ENTRIES="Yudit" "${COMMENT}" "${PREFIX}/share/pixmaps/yudit.xpm" \
		"yudit" "Office;" false

post-install:
	${INSTALL_DATA} ${WRKSRC}/icons/SS_Yudit_XPM.xpm \
		${STAGEDIR}${PREFIX}/share/pixmaps/yudit.xpm

.include <bsd.port.mk>
