PORTNAME=	xpk
PORTVERSION=	0.1.4
PORTREVISION=	3
CATEGORIES=	archivers
MASTER_SITES=	http://vesuri.jormas.com/xpk/ \
		http://www.energyhq.es.eu.org/files/

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	The eXternal PacKer (XPK) library system
WWW=		http://www.jormas.com/~vesuri/xpk/

LICENSE=	gpl2+
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		libtool
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes

post-install:
	${STRIP_CMD} ${PREFIX}/lib/libxpk*.so

.include <bsd.port.mk>
