PORTNAME=	sensors
PORTVERSION=	${QT6_VERSION}
PORTREVISION=	1
CATEGORIES=	comms
PKGNAMEPREFIX=	qt6-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Qt sensors module
WWW=		https://qt.io

BUILD_DEPENDS=	vulkan-headers>0:graphics/vulkan-headers

USES=		cmake compiler:c++11-lang pkgconfig qt-dist:6
USE_QT=		base declarative

.include <bsd.port.mk>
