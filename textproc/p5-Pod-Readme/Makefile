PORTNAME=	Pod-Readme
PORTVERSION=	1.2.3
DISTVERSIONPREFIX=	v
CATEGORIES=	textproc perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Convert POD to README file
WWW=		https://metacpan.org/release/Pod-Readme

LICENSE=	artistic gpl+
LICENSE_COMB=	dual
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-CPAN-Changes>=0.300000:devel/p5-CPAN-Changes \
		p5-Class-Method-Modifiers>=0:devel/p5-Class-Method-Modifiers \
		p5-File-Slurp>=0:devel/p5-File-Slurp \
		p5-Getopt-Long-Descriptive>=0:devel/p5-Getopt-Long-Descriptive \
		p5-Moo>=0:devel/p5-Moo \
		p5-MooX-HandlesVia>=0:devel/p5-MooX-HandlesVia \
		p5-Path-Tiny>=0:devel/p5-Path-Tiny \
		p5-Role-Tiny>=0:devel/p5-Role-Tiny \
		p5-Try-Tiny>=0:lang/p5-Try-Tiny \
		p5-Type-Tiny>=1.000000:devel/p5-Type-Tiny \
		p5-namespace-autoclean>=0:devel/p5-namespace-autoclean
TEST_DEPENDS=	p5-IO-String>=0:devel/p5-IO-String \
		p5-Test-Deep>=0:devel/p5-Test-Deep \
		p5-Test-Exception>=0:devel/p5-Test-Exception

USES=		perl5 shebangfix
USE_PERL5=	configure

NO_ARCH=	yes

SHEBANG_FILES=	bin/pod2readme

.include <bsd.port.mk>
