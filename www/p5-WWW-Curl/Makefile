PORTNAME=	WWW-Curl
PORTVERSION=	4.17
PORTREVISION=	5
CATEGORIES=	www ftp perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Perl extension interface for libcurl
WWW=		https://metacpan.org/release/WWW-Curl

LICENSE=	mit

LIB_DEPENDS=	libcurl.so:ftp/curl
TEST_DEPENDS=	p5-Test-CPAN-Meta>=0:devel/p5-Test-CPAN-Meta \
		p5-Test-Pod>=1.14:devel/p5-Test-Pod \
		p5-Test-Pod-Coverage>=1.04:devel/p5-Test-Pod-Coverage

USE_PERL5=	configure
USES=		perl5
NO_TEST=	yes

post-install:
	${STRIP_CMD} ${PREFIX}/${SITE_ARCH_REL}/auto/WWW/Curl/Curl.so

.include <bsd.port.mk>
