PORTNAME=	startup-notification
PORTVERSION=	0.12
PORTREVISION=	6
CATEGORIES=	x11 gnome
MASTER_SITES=	http://www.freedesktop.org/software/startup-notification/releases/
DIST_SUBDIR=	gnome2

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Library that supports startup notification spec from freedesktop.org
WWW=		https://www.freedesktop.org/wiki/Software/startup-notification/

LICENSE=	lgpl mit
LICENSE_COMB=	multi

LIB_DEPENDS=	libxcb-util.so:x11/xcb-util

USE_XORG=	x11
USES=		gmake libtool pathfix pkgconfig xorg
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes
CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib
CONFIGURE_ARGS+=ac_cv_lib_ICE_IceConnectionNumber=no
INSTALL_TARGET=	install-strip

.include <bsd.port.mk>
