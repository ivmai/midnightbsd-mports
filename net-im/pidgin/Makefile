PORTNAME=	pidgin

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Pidgin multi-protocol messaging client (GTK UI)

LIB_DEPENDS=	libstartup-notification-1.so:x11/startup-notification \
		libpurple.so:net-im/libpurple
RUN_DEPENDS=	${LOCALBASE}/share/fonts/noto/NotoColorEmoji.ttf:x11-fonts/noto-emoji

MASTERDIR=	${.CURDIR}/../libpurple
BUILD_WRKSRC=	${WRKSRC}/pidgin
INSTALL_WRKSRC=	${BUILD_WRKSRC}
INSTALLS_ICONS=	yes
DESCR=		${.CURDIR}/pkg-descr
PLIST=		${.CURDIR}/pkg-plist

PIDGIN_SLAVE=	yes
WITH_GTKUI=	yes

USES=		gnome python:build xorg
USE_LDCONFIG=	yes
USE_GNOME=	gnomeprefix gtk20 intltool
USE_XORG=	xscrnsaver sm
CONFIGURE_ARGS=	--disable-consoleui \
		--disable-nm \
		--enable-screensaver \
		--disable-schemas-install \
		--with-dynamic_prpls=${PRPL_MODULES:S/,$//}

post-install:
	${INSTALL_MAN} ${WRKSRC}/doc/pidgin.1 ${PREFIX}/share/man/man1

.include "${MASTERDIR}/Makefile"
