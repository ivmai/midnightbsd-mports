PORTNAME=	Image-Magick-Iterator
PORTVERSION=	0.01
PORTREVISION=	3
CATEGORIES=	graphics perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Sequentially read Image::Magick object from a filehandle
WWW=		https://metacpan.org/release/Image-Magick-Iterator

LICENSE=	artistic gpl
LICENSE_COMB=	dual

RUN_DEPENDS=	${SITE_PERL}/Image/PBMlib.pm:graphics/p5-Image-PBMlib

USES=		magick:build,run perl5
USE_PERL5=	configure

NO_ARCH=	yes
NO_TEST=	yes

.include <bsd.port.mk>
