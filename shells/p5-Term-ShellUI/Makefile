PORTNAME=	Term-ShellUI
PORTVERSION=	0.92
PORTREVISION=	3
CATEGORIES=	shells perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Fully-featured shell-like command line environment
WWW=		https://metacpan.org/release/Term-ShellUI

LICENSE=	artistic gpl
LICENSE_COMB=	dual

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Term-ReadLine-Gnu>=0:devel/p5-Term-ReadLine-Gnu

USES=		perl5 shebangfix
SHEBANG_FILES=	examples/*
USE_PERL5=	configure
NO_ARCH=	yes

OPTIONS_DEFINE=	EXAMPLES

post-install:
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	(cd ${WRKSRC}/examples/ && ${INSTALL_SCRIPT} \
		fileman-example synopsis synopsis-big tui-sample ${STAGEDIR}${EXAMPLESDIR})

.include <bsd.port.mk>
