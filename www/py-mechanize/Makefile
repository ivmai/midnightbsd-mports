PORTNAME=	mechanize
PORTVERSION=	0.4.8
CATEGORIES=	www python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Stateful programmatic web browsing in Python
WWW=		https://github.com/python-mechanize/mechanize

LICENSE=	bsd3

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}html5lib>=0.9:www/py-html5lib@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}html5-parser>0:www/py-html5-parser@${PY_FLAVOR}

USES=		python
USE_PYTHON=	distutils autoplist

NO_ARCH=	yes

.include <bsd.port.mk>
