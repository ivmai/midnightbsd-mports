PORTNAME=	pythran
PORTVERSION=	0.16.1
CATEGORIES=	devel python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Ahead of Time compiler for numeric kernels
WWW=		https://github.com/serge-sans-paille/pythran

LICENSE=	bsd3
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYNUMPY} \
		${PYTHON_PKGNAMEPREFIX}ply>=3.4:devel/py-ply@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}gast>=0.5.0:devel/py-gast@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}beniget>=0.4.0:devel/py-beniget@${PY_FLAVOR}

USES=		python
USE_PYTHON=	autoplist concurrent distutils

NO_ARCH=	yes

post-extract:
	-${RM} ${WRKSRC}/third_party/xsimd/config/*.rej
	-${RM} ${WRKSRC}/third_party/xsimd/*.rej
	-${RM} ${WRKSRC}/third_party/xsimd/math/.xsimd_gamma.hpp.swp

.include <bsd.port.mk>
