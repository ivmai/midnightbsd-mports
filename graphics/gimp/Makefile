PORTNAME=	gimp
DISTVERSION?=	2.10.38
PORTEPOCH?=	2
CATEGORIES=	graphics gnome

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	The "meta-port" for The Gimp
WWW=		https://www.gimp.org/

RUN_DEPENDS=	gimp-2.10:graphics/gimp-app

USES+=	metaport

OPTIONS_DEFINE=	PRINT HELP
OPTIONS_DEFAULT=PRINT
PRINT_DESC=	Gutenprint (gimp-print) plugin
HELP_DESC=	Gimp-Help (50+MB distfile)

HELP_RUN_DEPENDS+=	en-gimp-help-html>=0:misc/gimp-help-en
PRINT_RUN_DEPENDS+=	${LOCALBASE}/libexec/gimp/2.2/plug-ins/gutenprint:print/gimp-gutenprint \
			gutenprint>0:print/gutenprint

.include <bsd.port.mk>
