PORTNAME=	xetex
PORTVERSION=	0.99993
PORTREVISION=	3
CATEGORIES=	print
MASTER_SITES=	ftp://tug.org/historic/systems/texlive/2015/
PKGNAMEPREFIX=	tex-
DISTNAME=	texlive-${TEXLIVE_VERSION}-source
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} \
		${DISTNAME_TEXMF}${EXTRACT_SUFX}
DIST_SUBDIR=	TeX
EXTRACT_ONLY=	texlive-${TEXLIVE_VERSION}-source${EXTRACT_SUFX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	TeX System with Unicode and Modern Font Technologies

LICENSE=	other

LIB_DEPENDS=	libfontconfig.so:x11-fonts/fontconfig \
		libfreetype.so:print/freetype2 \
		libgraphite2.so:graphics/graphite2 \
		libicuio.so:devel/icu \
		libharfbuzz.so:print/harfbuzz \
		libharfbuzz-icu.so:print/harfbuzz-icu \
		libpng.so:graphics/png \
		libTECkit.so:textproc/teckit

USES=		compiler:c++11-lib localbase gnome perl5 pkgconfig \
		python:build tar:xz tex xorg
USE_CXXSTD=	gnu++11
USE_GNOME=	cairo
USE_PERL5=	build
USE_TEX=	kpathsea web2c formats fmtutil dvipdfmx
USE_XORG=	pixman

GNU_CONFIGURE=	yes
CONFIGURE_ARGS+=CC="${CC}" \
		CXX="${CXX}" \
		${EXCLUDE_ENGINES:S/^/--disable-/} \
		--enable-xetex \
		--with-system-freetype2 \
		--with-freetype2-includes=${LOCALBASE}/include/freetype2 \
		--with-freetype2-libdir=${LOCALBASE}/lib \
		--with-system-graphite2 \
		--with-graphite2-includes=${LOCALBASE}/include/graphite2 \
		--with-graphite2-libdir=${LOCALBASE}/lib \
		--with-system-harfbuzz \
		--with-system-teckit \
		--with-teckit-includes=${LOCALBASE}/include/teckit \
		--with-teckit-libdir=${LOCALBASE}/lib \
		--with-system-zziplib \
		--with-system-zlib
.for L in cairo gmp kpathsea libpng mpfr pixman ptexenc icu
CONFIGURE_ARGS+=--with-system-$L \
		--with-$L-include=${LOCALBASE}/include \
		--with-$L-libdir=${LOCALBASE}/lib
.endfor

MAKE_JOBS_UNSAFE=	yes

CPPFLAGS=	-I${LOCALBASE}/include/harfbuzz

EXTRACT_AFTER_ARGS=	${EXTRACT_FILES:S,^,${DISTNAME}/,}
EXTRACT_FILES=	build-aux \
		libs/pplib \
		libs/xpdf \
		texk/web2c
EXTRACT_AFTER_ARGS_TEXMF= \
	| ${TAR} -xf - -C ${STAGEDIR}${PREFIX}/share \
		--strip-components 1 --no-same-permission --no-same-owner \
		${EXTRACT_FILES_TEXMF:S,^,${DISTNAME_TEXMF}/,}
EXTRACT_FILES_TEXMF= \
	texmf-dist/doc/xelatex \
	texmf-dist/doc/xetex \
	texmf-dist/fonts/misc/xetex \
	texmf-dist/source/xelatex \
	texmf-dist/tex/xelatex \
	texmf-dist/tex/xetex
EXCLUDE_ENGINES=aleph etex pdftex luatex luajittex mf mf-nowin \
		mflua mfluajit luahbtex luajithbtex ptex eptex uptex euptex \
		otangle mp pmp upmp web2c web-progs tex synctex

WRKSRC=		${WRKDIR}/${DISTNAME}/texk/web2c

TEXHASHDIRS=	${TEXMFDISTDIR} ${TEXMFVARDIR}
TEX_FORMATS=	xetex

post-extract:
	@${FIND} ${WRKSRC} -name '*.orig' -delete

pre-configure:
	for D in libs/xpdf libs/pplib; do \
		cd ${WRKDIR}/${DISTNAME}/$$D && \
		    ${SETENV} ${CONFIGURE_ENV} ${SH} ${CONFIGURE_SCRIPT} \
			${CONFIGURE_ARGS}; \
	done
	cd ${WRKDIR}/${DISTNAME}/libs/pplib && \
		${MAKE}

pre-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/share
	${CAT} ${DISTDIR}/${DIST_SUBDIR}/texlive-${TEXLIVE_VERSION}-texmf${EXTRACT_SUFX} \
		${EXTRACT_AFTER_ARGS_TEXMF}

post-fake:
	${REINPLACE_CMD} -i '' -e 's|/bin/bash|${PREFIX}/bin/bash|' \
		${FAKE_DESTDIR}${PREFIX}/share/texmf-dist/doc/xelatex/hanzibox/build.sh
	${REINPLACE_CMD} -i '' -e 's|/usr/bin/env python|${PYTHON_CMD}|g' \
		${FAKE_DESTDIR}${PREFIX}/share/texmf-dist/doc/xelatex/xepersian/dkun-0.3.py \
		${FAKE_DESTDIR}${PREFIX}/share/texmf-dist/doc/xelatex/xepersian/dkun-0.4.py \
		${FAKE_DESTDIR}${PREFIX}/share/texmf-dist/doc/xelatex/xepersian/undk-0.6.py \
		${FAKE_DESTDIR}${PREFIX}/share/texmf-dist/doc/xelatex/xepersian/unldk-0.2.py
	${REINPLACE_CMD} -i '' -e 's|/usr/bin/perl|${PERL}|g' \
		${FAKE_DESTDIR}${PREFIX}/share/texmf-dist/source/xelatex/arabxetex/makemaps.pl
	${FIND} -s ${FAKE_DESTDIR}${PREFIX}/share/texmf-dist -not -type d | ${SORT} | \
		${SED} -e 's#^${FAKE_DESTDIR}${PREFIX}/##' >> ${TMPPLIST}
	${FIND} -s ${FAKE_DESTDIR}${PREFIX}/share/texmf-dist -type d -empty | ${SORT} -r | \
		${SED} -e 's#^${FAKE_DESTDIR}${PREFIX}/#@dir #' >> ${TMPPLIST}

.include <bsd.port.mk>
