PORTNAME=	xdg-utils
PORTVERSION=	1.1.3
CATEGORIES=	devel
MASTER_SITES=	https://portland.freedesktop.org/download/

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Tools to allow all applications to integrate with the free desktop
WWW=		https://www.freedesktop.org/wiki/Software/xdg-utils/

LICENSE=	mit
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	minixmlto:textproc/minixmlto
RUN_DEPENDS=	${LOCALBASE}/share/icons/hicolor/index.theme:misc/hicolor-icon-theme

USES=		cpe gmake

CPE_VENDOR=	freedesktop

CONFIGURE_ENV=	XMLTO=${LOCALBASE}/bin/minixmlto
GNU_CONFIGURE=	yes
GNU_CONFIGURE_MANPREFIX=${PREFIX}/share
NO_ARCH=	yes
MAKE_ENV=	PREFER_DOCBOOK2MDOC=1

OPTIONS_DEFINE=	X11
OPTIONS_DEFAULT=X11
X11_RUN_DEPENDS=xprop:x11/xprop \
		xset:x11/xset

post-patch:
	@${REINPLACE_CMD} -e 's|%%LOCALBASE%%|${LOCALBASE}|' \
		${WRKSRC}/scripts/xdg-*

.include <bsd.port.mk>
