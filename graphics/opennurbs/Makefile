PORTNAME=	opennurbs
PORTVERSION=	20130711
CATEGORIES=	graphics
MASTER_SITES=	http://files.na.mcneel.com/opennurbs/5.0/2013-07-11/
DISTNAME=	${PORTNAME}_${PORTVERSION}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Tools to accurately transfer 3-D geometry between applications
WWW=		https://www.rhino3d.com/opennurbs

LICENSE_FILE=	${WRKSRC}/readme.txt

USES=		iconv:build dos2unix gmake zip
MAKE_ARGS=	CC="${CC}" CCC="${CXX}"

MAKEFILE=	makefile

OPTIONS_DEFINE=	EXAMPLES

.include <bsd.port.pre.mk>

# In r311275 zlib.h was moved to contrib/zlib/zlib.h from lib/libz/zlib.h
LIBZ=		${SRC_BASE}/contrib/zlib
.if !exists(${LIBZ}/zlib.h)
LIBZ=		${SRC_BASE}/sys/contrib/zlib
.endif
.if !exists(${LIBZ}/zlib.h)
LIBZ:=		${SRC_BASE}/lib/libz
.endif
.if !exists(${LIBZ}/zlib.h)
IGNORE=		needs SRC_BASE to compile. Install base system sources and try again
.endif

.if ${ARCH} != i386
MAKE_ARGS+=	ON_GNU_OPTIMIZER_FLAGS="-g -fPIC"
.endif

pre-build:
	@${RM} -r ${WRKSRC}/zlib
	${CP} -R ${LIBZ} ${WRKSRC}/zlib

do-install:
	@${MKDIR} ${PREFIX}/include/openNURBS/zlib
	${INSTALL_DATA} ${WRKSRC}/libopenNURBS.a ${PREFIX}/lib
	${INSTALL_DATA} ${WRKSRC}/*.h ${PREFIX}/include/openNURBS
	${INSTALL_DATA} ${WRKSRC}/zlib/*.h \
		${PREFIX}/include/openNURBS/zlib

do-install-EXAMPLES-on:
	@${MKDIR} ${FAKE_DESTDIR}${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/examples_linking_pragmas.h \
		${FAKE_DESTDIR}${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/opennurbs.h ${FAKE_DESTDIR}${EXAMPLESDIR}
.for i in brep read roundtrip userdata write
	@${MKDIR} ${FAKE_DESTDIR}${EXAMPLESDIR}/example_${i}
	${INSTALL_PROGRAM} ${WRKSRC}/example_${i}/example_${i} ${FAKE_DESTDIR}${EXAMPLESDIR}/example_${i}
	cd ${WRKSRC}/example_${i} && ${COPYTREE_SHARE} . ${FAKE_DESTDIR}${EXAMPLESDIR}/example_${i} "-name *\.cpp -or -name *\.h"
.endfor

.include <bsd.port.post.mk>
