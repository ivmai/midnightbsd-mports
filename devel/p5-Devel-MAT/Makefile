PORTNAME=	Devel-MAT
PORTVERSION=	0.42
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Perl Memory Analysis Tool

LICENSE=	artistic gpl
LICENSE_COMB=	dual
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-Commandable>=0.03:devel/p5-Commandable \
		p5-Devel-MAT-Dumper>=0.35:devel/p5-Devel-MAT-Dumper \
		p5-File-ShareDir>=0:devel/p5-File-ShareDir \
		p5-Heap>=0:devel/p5-Heap \
		p5-List-UtilsBy>=0:devel/p5-List-UtilsBy \
		p5-Module-Pluggable>=0:devel/p5-Module-Pluggable \
		p5-String-Tagged>=0:textproc/p5-String-Tagged \
		p5-String-Tagged-Terminal>=0.03:textproc/p5-String-Tagged-Terminal \
		p5-Struct-Dumb>=0.07:devel/p5-Struct-Dumb

NO_TEST=	yes

USES=		perl5
USE_PERL5=	modbuild

.include <bsd.port.pre.mk>

.if ${PERL_LEVEL} < 502501
BUILD_DEPENDS+=	p5-Scalar-List-Utils>=1.44:lang/p5-Scalar-List-Utils
RUN_DEPENDS+=	p5-Scalar-List-Utils>=1.44:lang/p5-Scalar-List-Utils
.endif

.include <bsd.port.post.mk>
