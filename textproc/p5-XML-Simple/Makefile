PORTNAME=	XML-Simple
PORTVERSION=	2.25
CATEGORIES=	textproc perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Trivial API for reading and writing XML (esp config files)
WWW=		https://www.mclean.net.nz/

LICENSE=	artistic gpl+
LICENSE_COMB=	dual
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-XML-Parser>=0:textproc/p5-XML-Parser \
		p5-XML-SAX>=0.15:textproc/p5-XML-SAX \
		p5-XML-SAX-Expat>=0:textproc/p5-XML-SAX-Expat

MAKE_JOBS_UNSAFE=	yes
NO_ARCH=	yes
USES=		perl5
USE_PERL5=	configure

.include <bsd.port.mk>
