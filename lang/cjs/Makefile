PORTNAME=	cjs
PORTVERSION=	4.8.2
PORTREVISION=	1
CATEGORIES=	lang gnome
DIST_SUBDIR=	gnome

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	JavaScript bindings based on gobject-introspection
WWW=		https://github.com/linuxmint/cinnamon

LICENSE=		mit lgpl+
LICENSE_COMB=		dual
LICENSE_FILE_mit=	${WRKSRC}/COPYING
LICENSE_FILE_lgpl+ =	${WRKSRC}/COPYING.LGPL

LIB_DEPENDS=	libffi.so:devel/libffi \
		libmozjs-78.so:lang/spidermonkey78

USES=		compiler:c++14-lang gettext gnome localbase meson pkgconfig \
		python:3.5+,build readline shebangfix xorg
USE_GNOME=	cairo gdkpixbuf2 gtk30 introspection
USE_XORG=	x11 xext
MESON_ARGS=	-Dinstalled_tests=false \
		-Dcairo=enabled \
		-Dreadline=enabled \
		-Dprofiler=disabled \
		-Dskip_dbus_tests=true \
		-Dskip_gtk_tests=true
USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	linuxmint

SHEBANG_GLOB=	*.py

PORTSCOUT=	limit:^[0-9.]+$$	# ignore master.mint* tags

NO_TEST=	yes

.include <bsd.port.mk>
