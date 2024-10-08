PORTNAME=	jadetex
PORTVERSION=	3.13
PORTREVISION=	5
CATEGORIES=	print
MASTER_SITES=	FREEBSD_LOCAL/tex
PKGNAMEPREFIX=	tex-
DISTNAME=	${PKGNAMEPREFIX}${PORTNAME}-${TEXLIVE_VERSION}-freebsd
DIST_SUBDIR=	TeX
EXTRACT_ONLY=

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	TeX backend for Jade, DSSSL processor for SGML/XML documents
WWW=		https://jadetex.sourceforge.net/

LICENSE=	gpl2

USES=		tar:xz tex
USE_TEX=	fmtutil pdftex xmltex

NO_ARCH=	yes
NO_BUILD=	yes

TEXHASHDIRS=	${TEXMFDISTDIR} ${TEXMFVARDIR}
TEX_FORMATS=	jadetex

do-install:
	${TAR} -Jxf ${DISTDIR}/${DIST_SUBDIR}/${DISTNAME}${EXTRACT_SUFX} \
		-C ${STAGEDIR}${PREFIX}/share \
		--strip-components 1 --no-same-permission --no-same-owner

.if defined(MAINTAINER_MODE)
_EXTRACT_FILES= \
	texmf-dist/doc/otherformats/jadetex \
	texmf-dist/source/jadetex/base \
	texmf-dist/tex/jadetex/base
_WRKSRC=	${WRKDIR}/${PKGNAMEPREFIX}${PORTNAME}-${TEXLIVE_VERSION}

_maintainer-extract:
	${MAKE} clean
	${MKDIR} ${_WRKSRC}
	${TAR} -xf ${DISTDIR}/${DIST_SUBDIR}/${DISTNAME_TEXMF}${EXTRACT_SUFX} \
		-C ${_WRKSRC}$ \
		--strip-components 1 --no-same-permission --no-same-owner \
		${_EXTRACT_FILES:S,^,${DISTNAME_TEXMF}/,}

_maintainer-dist: _maintainer-extract
	${TAR} --options xz:compression-level=9 -Jcvf \
		${WRKDIR}/${PKGNAMEPREFIX}${PORTNAME}-${TEXLIVE_VERSION}-freebsd.tar.xz \
		-C ${WRKDIR} ${PKGNAMEPREFIX}${PORTNAME}-${TEXLIVE_VERSION}
	scp ${WRKDIR}/${PKGNAMEPREFIX}${PORTNAME}-${TEXLIVE_VERSION}-freebsd.tar.xz \
		bofh@freefall.freebsd.org://home/tex/public_distfiles/

.endif

.include <bsd.port.mk>
