PORTNAME=	Email-Abstract
PORTVERSION=	3.010
CATEGORIES=	mail perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Unified interface to mail representations
WWW=		https://metacpan.org/release/Email-Abstract

LICENSE=	artistic gpl+
LICENSE_COMB=	dual
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Email-Simple>=1.998:mail/p5-Email-Simple \
		p5-MRO-Compat>=0:devel/p5-MRO-Compat \
		p5-Module-Pluggable>1.5:devel/p5-Module-Pluggable

USES=		perl5
USE_PERL5=	configure

.include <bsd.port.mk>
