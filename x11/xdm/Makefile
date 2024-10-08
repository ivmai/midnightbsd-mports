PORTNAME=	xdm
PORTVERSION=	1.1.14
PORTREVISION=	0
CATEGORIES=	x11

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	X.Org X display manager

LICENSE=	mit
LICENSE_FILE=	${WRKSRC}/COPYING

RUN_DEPENDS=	xsm:x11/xsm

EXTRACT_SUFX=	.tar.xz
USES=		cpe libtool xorg xorg-cat:app
USE_LDCONFIG=	yes
USE_XORG=	x11 xau xaw xdmcp xext xinerama xmu xpm xrender xt
USE_RC_SUBR=	xdm
CPE_PRODUCT=	x_display_manager
CPE_VENDOR=	x

CONFIGURE_ARGS+=	--with-xdmconfigdir=${PREFIX}/etc/X11/xdm \
			--with-xdmscriptdir=${PREFIX}/etc/X11/xdm \
			--with-pixmapdir=${PREFIX}/share/pixmaps \
			--with-authdir=/var/db/xdm

CFFILES=	GiveConsole TakeConsole Xaccess Xreset Xresources \
		Xservers Xsession Xsetup_0 Xstartup Xwilling xdm-config

OPTIONS_SUB=	yes

OPTIONS_DEFINE=	XDMSHELL XFT
OPTIONS_DEFAULT=	XFT
XDMSHELL_DESC=	Install xdmshell

XDMSHELL_CONFIGURE_ENABLE=	xdmshell

XFT_USE=	xorg=xft
XFT_CONFIGURE_WITH=	xft

INSTALL_TARGET=	install-strip

post-patch:
	@${REINPLACE_CMD} 's/test.*-traditional.*;/true;/' \
		${WRKSRC}/configure
	@${REINPLACE_CMD} -e "s|@DESTDIR@||" ${WRKSRC}/Makefile.in

post-install:
.for f in ${CFFILES}
	@${MV} ${STAGEDIR}${PREFIX}/etc/X11/xdm/${f} ${STAGEDIR}${PREFIX}/etc/X11/xdm/${f}.sample
.endfor
	@${MKDIR} ${STAGEDIR}/var/db/xdm

.include <bsd.port.mk>
