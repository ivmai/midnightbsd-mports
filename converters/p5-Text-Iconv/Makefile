PORTNAME=	Text-Iconv
PORTVERSION=	1.7
PORTREVISION=	3
CATEGORIES=	converters perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Perl interface to iconv() codeset conversion function
WWW=		https://metacpan.org/release/Text-Iconv

LICENSE=	artistic gpl+
LICENSE_COMB=	dual

USES=		perl5 iconv:translit
USE_PERL5=	configure
CONFIGURE_ARGS+=INC="-I${ICONV_PREFIX}/include ${CFLAGS}" \
		LIBS="-L${ICONV_PREFIX}/lib ${ICONV_LIB}"

post-install:
	${STRIP_CMD} ${PREFIX}/${SITE_ARCH_REL}/auto/Text/Iconv/Iconv.so

.include <bsd.port.mk>
