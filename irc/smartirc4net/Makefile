PORTNAME=	smartirc4net
PORTVERSION=	1.1
CATEGORIES=	irc
MASTER_SITES=	https://smuxi.im/jaws/data/files/

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Multi-layered IRC library
WWW=		http://smartirc4net.meebey.net/jaws/

LICENSE=	lgpl2.1
LICENSE_FILE=	${WRKSRC}/LICENSE

GNU_CONFIGURE=	yes
CONFIGURE_ENV=	ac_cv_path_MCS=${LOCALBASE}/bin/mcs
USES=		gmake mono pathfix pkgconfig

.include <bsd.port.mk>
