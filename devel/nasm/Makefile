PORTNAME=	nasm
PORTVERSION=	2.16.03
PORTEPOCH=	1
CATEGORIES=	devel lang
MASTER_SITES=	https://www.nasm.us/pub/nasm/releasebuilds/${PORTVERSION}/ \
		https://mirror.sobukus.de/files/src/nasm/

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	General-purpose multi-platform x86 and amd64 assembler
WWW=		https://www.nasm.us/

LICENSE=	bsd2
LICENSE_FILE=	${WRKSRC}/LICENSE

GNU_CONFIGURE=	yes
CONFIGURE_ENV=	ac_cv_func_strspn=yes
USES=		compiler:c11 cpe tar:xz gmake perl5
USE_PERL5=	build
MAKE_ARGS+=	INSTALLROOT=${FAKE_DESTDIR}
INSTALL_TARGET=	install #needed for RDOFF_INSTALL_TARGET
CPE_VENDOR=	nasm
CPE_PRODUCT=	netwide_assembler
USE_PERL5=	build

OPTIONS_DEFINE=	DOCS
OPTIONS_SUB=	yes

DOCS_DISTFILES=	${DISTNAME}${EXTRACT_SUFX} ${DISTNAME}-xdoc${EXTRACT_SUFX}
PORTDOCS=	*

post-install-DOCS-on:
	@${MKDIR} ${FAKE_DESTDIR}${DOCSDIR}
	(cd ${WRKSRC}/doc && ${COPYTREE_SHARE} html ${FAKE_DESTDIR}${DOCSDIR})
	${INSTALL_DATA} ${WRKSRC}/doc/nasmdoc.txt ${FAKE_DESTDIR}${DOCSDIR}

.include <bsd.port.mk>
