# New ports collection makefile for:	p5-PatchReader
# Date created:				2004-02-11
# Whom:					Toni Viemer� <toni.viemero@iki.fi>
#

#

PORTNAME=	PatchReader
PORTVERSION=	0.9.6
CATEGORIES=	devel perl5
MASTER_SITES=${MASTER_SITE_PERL_CPAN}
MASTER_SITE_SUBDIR=	../by-authors/id/T/TM/TMANNERM/
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Perl module with utilities to read and manipulate patches and CVS

LICENSE=	perl

USES=		perl5
USE_PERL5=	configure

.include <bsd.port.pre.mk>

.if ${PERL_LEVEL} < 500800
BUILD_DEPENDS+=	${SITE_PERL}/File/Temp.pm:devel/p5-File-Temp
RUN_DEPENDS+=	${SITE_PERL}/File/Temp.pm:devel/p5-File-Temp
.endif

.include <bsd.port.post.mk>
