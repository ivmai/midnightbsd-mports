PORTNAME=	Params-Validate
PORTVERSION=	1.31
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Validate method/function parameters
WWW=		https://metacpan.org/release/Params-Validate

LICENSE=	artistic2
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Module-Implementation>=0.04:devel/p5-Module-Implementation
TEST_DEPENDS=	p5-Readonly>=0:devel/p5-Readonly \
		p5-Test-Fatal>=0:devel/p5-Test-Fatal \
		p5-Test-Requires>0:devel/p5-Test-Requires \
		p5-Test-Taint>=0.02:devel/p5-Test-Taint

USES=		perl5
USE_PERL5=	modbuild

.include <bsd.port.mk>
