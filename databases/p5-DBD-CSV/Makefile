PORTNAME=	DBD-CSV
PORTVERSION=	0.60
PORTEPOCH=	1
CATEGORIES=	databases perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	DBI driver for CSV files

LICENSE=	artistic gpl+
LICENSE_COMB=	dual

BUILD_DEPENDS=	${RUN_DEPENDS}
RUN_DEPENDS=	p5-DBI>=1.628:databases/p5-DBI \
		p5-SQL-Statement>=1.405:databases/p5-SQL-Statement \
		p5-Text-CSV_XS>=1.44:textproc/p5-Text-CSV_XS

USES=		perl5 tar:tgz
USE_PERL5=	configure

NO_ARCH=	yes

.include <bsd.port.mk>
