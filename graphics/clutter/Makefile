# Created by: Martin Wilke <miwi@FreeBSD.org>

PORTNAME=	clutter
DISTVERSION=	1.26.4
PORTREVISION=	1
CATEGORIES=	graphics
MASTER_SITES=	GNOME

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	OpenGL based interactive canvas library

LICENSE=	lgpl2.1
LICENSE_FILE=	${WRKSRC}/COPYING

LIB_DEPENDS=	libjson-glib-1.0.so:devel/json-glib \
		libfontconfig.so:x11-fonts/fontconfig \
		libfreetype.so:print/freetype2 \
		libcogl.so:graphics/cogl \
		libharfbuzz.so:print/harfbuzz

PORTSCOUT=	limit:1,even

USES=		cpe gettext gl gmake gnome libtool localbase pathfix pkgconfig \
		tar:xz xorg
USE_GNOME=	atk cairo gdkpixbuf2 pango introspection:build
USE_GL=		egl
USE_XORG=	x11 xcomposite xdamage xext xfixes xi xrandr
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes
CONFIGURE_ARGS=	--with-x --enable-conformance=no \
		--disable-evdev-input \
		--enable-egl-backend=yes \
		--enable-x11-backend=yes \
		--enable-gdk-backend=no \
		--enable-wayland-compositor=no
INSTALL_TARGET=	install-strip
CPE_VENDOR=	clutter_project

.include <bsd.port.mk>
