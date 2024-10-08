PORTNAME=	numpy
PORTVERSION=	1.25.0
PORTREVISION=	2
PORTEPOCH=	1
CATEGORIES=	math python
MASTER_SITES=	PYPI \
		https://numpy.org/doc/1.23/:doc
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} \
		${PORTNAME}-ref.pdf:doc \
		${PORTNAME}-user.pdf:doc
DIST_SUBDIR=	${PORTNAME}-${PORTVERSION:R}
EXTRACT_ONLY=	${DISTNAME}${EXTRACT_SUFX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	The New Numeric Extension to Python
WWW=		https://www.numpy.org/

LICENSE=	bsd3
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

USES=		compiler:c11 cpe fortran python:3.9-3.11
USE_PYTHON=	allflavors autoplist concurrent cython distutils
# circular depends for test
NO_TEST=	yes

GCCLIBDIR_CMDS=	${FC} -print-file-name=libgfortran.so | ${SED} -e s/libgfortran.so//
LDFLAGS+=	-s
PYDISTUTILS_BUILDARGS=		--fcompiler=gnu95
PYDISTUTILS_CONFIGUREARGS=	--fcompiler=gnu95

PORTDOCS=	*

OPTIONS_DEFINE=		DOCS SUITESPARSE
OPTIONS_SINGLE=		BLASLIB
OPTIONS_SINGLE_BLASLIB=	ATLAS NETLIB OPENBLAS
OPTIONS_DEFAULT=	OPENBLAS SUITESPARSE
SUITESPARSE_DESC=	Use AMD and UMFPACK in SuiteSparse

ATLAS_USES=		blaslapack:atlas
ATLAS_VARS=		BLASLIBS="ptf77blas, ptcblas" BLASNAME=atlas LAPACKLIBS=alapack LIBRARIES=atlas_libs
NETLIB_USES=		blaslapack:netlib
NETLIB_VARS=		BLASLIBS="blas, cblas" BLASNAME=atlas LAPACKLIBS=lapack LIBRARIES=atlas_libs
NETLIB_LIB_DEPENDS=	libcblas.so:math/cblas
OPENBLAS_USES=		blaslapack:openblas
OPENBLAS_VARS=		BLASLIBS="openblas, gfortran" BLASNAME=openblas LAPACKLIBS="openblas, gfortran" LIBRARIES=libraries
SUITESPARSE_LIB_DEPENDS=libumfpack.so:math/suitesparse-umfpack

post-extract:
	@${TOUCH} ${WRKSRC}/numpy/f2py/tests/src/temp
	@${TOUCH} ${WRKSRC}/numpy/random/_examples/temp
	@${TOUCH} ${WRKSRC}/numpy/core/tests/examples/temp

pre-configure-SUITESPARSE-off:
	@${REINPLACE_CMD} -e 's|:%%LOCALBASE%%/include/suitesparse||' ${WRKSRC}/site.cfg

pre-configure:
	@${REINPLACE_CMD} -e 's|%%FC%%|${FC}|' ${WRKSRC}/numpy/distutils/fcompiler/gnu.py
	@${CP} ${FILESDIR}/site.cfg ${WRKSRC}/site.cfg
	${REINPLACE_CMD} -e 's|%%LOCALBASE%%|${LOCALBASE}|g' \
		-e 's|%%BLASLIBS%%|${BLASLIBS}|; s|%%BLASNAME%%|${BLASNAME}|' \
		-e 's|%%LAPACKLIBS%%|${LAPACKLIBS}|; s|%%LIBRARIES%%|${LIBRARIES}|' \
			${WRKSRC}/site.cfg
	@${REINPLACE_CMD} -e "s|%%GCCLIBDIR%%|$$(${GCCLIBDIR_CMDS})|" ${WRKSRC}/site.cfg ${WRKSRC}/numpy/distutils/system_info.py

do-configure:

post-install:
	${FIND} ${FAKE_DESTDIR}${PYTHON_SITELIBDIR} -name '*.so' | ${XARGS} ${STRIP_CMD}

post-install-DOCS-on:
	@${MKDIR} ${FAKE_DESTDIR}${DOCSDIR}
	${INSTALL_DATA} ${_DISTDIR}/${PORTNAME}-ref.pdf ${FAKE_DESTDIR}${DOCSDIR}
	${INSTALL_DATA} ${_DISTDIR}/${PORTNAME}-user.pdf ${FAKE_DESTDIR}${DOCSDIR}

.include <bsd.port.mk>
