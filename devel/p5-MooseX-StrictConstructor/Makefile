PORTNAME=	MooseX-StrictConstructor
PORTVERSION=	0.21
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Make your MooseX object constructors blow up on unknown attributes
WWW=		https://metacpan.org/release/MooseX-StrictConstructor

LICENSE=	artistic2

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Moose>=0.94:devel/p5-Moose \
		p5-namespace-autoclean>=0:devel/p5-namespace-autoclean

USES=		perl5
USE_PERL5=	configure
NO_ARCH=	yes
NO_TEST=	yes

.include <bsd.port.mk>
