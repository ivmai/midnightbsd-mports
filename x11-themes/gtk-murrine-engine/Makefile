PORTNAME=	murrine
PORTVERSION=	0.98.2
PORTREVISION=	2
CATEGORIES=	x11-themes
MASTER_SITES=	GNOME
PKGNAMEPREFIX=	gtk-
PKGNAMESUFFIX=	-engine

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Murrine GTK+ 2.x cairo based engine

LICENSE=	lgpl3

USES=		gettext gmake gnome libtool pkgconfig tar:xz xorg
USE_XORG=	pixman
USE_GNOME=	gtk20 intltool intlhack
USE_LDCONFIG=	yes
GNU_CONFIGURE=	yes

OPTIONS_DEFINE=	ANIMATION
ANIMATION_DESC=	Animation support
ANIMATION_CONFIGURE_ENABLE=	animation

post-patch:
	@${REINPLACE_CMD} -e 's|glib/gtimer.h|glib.h|g' \
		${WRKSRC}/src/animation.c

.include <bsd.port.mk>
