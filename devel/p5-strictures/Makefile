PORTNAME=	strictures
PORTVERSION=	2.000006
PORTEPOCH=	1
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
MASTER_SITE_SUBDIR=	CPAN:HAARG
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Turn on strict and make all warnings fatal
WWW=		https://metacpan.org/release/strictures

LICENSE=	artistic gpl+
LICENSE_COMB=	dual

NO_ARCH=	yes
USES=		perl5
USE_PERL5=	configure

OPTIONS_DEFINE=	STRICTURES_EXTRA
OPTIONS_DEFAULT=STRICTURES_EXTRA

STRICTURES_EXTRA_DESC=		Enable full set of strictures (recommended)
STRICTURES_EXTRA_BUILD_DEPENDS=	p5-bareword-filehandles>=0:devel/p5-bareword-filehandles \
				p5-indirect>=0:devel/p5-indirect \
				p5-multidimensional>=0:devel/p5-multidimensional
STRICTURES_EXTRA_RUN_DEPENDS=	${STRICTURES_EXTRA_BUILD_DEPENDS}

.include <bsd.port.mk>
