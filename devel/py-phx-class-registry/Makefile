PORTNAME=	phx-class-registry
DISTVERSION=	3.0.5
CATEGORIES=	devel python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Factory+Registry pattern for Python classes
WWW=		https://github.com/todofixthis/class-registry/

LICENSE=	mit
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}six>=1.13:devel/py-six@${PY_FLAVOR}

TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}nose>0:devel/py-nose@${PY_FLAVOR}

USES=		python
USE_PYTHON=	distutils autoplist concurrent

NO_ARCH=	yes
NO_TEST=	yes

.include <bsd.port.mk>
