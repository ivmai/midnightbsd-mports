PORTNAME=	pyasn1-modules
PORTVERSION=	0.2.8
CATEGORIES=	devel python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Collection of ASN.1 data structures for py-pyasn1

LICENSE=	bsd2
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}pyasn1>=0.4.1:devel/py-pyasn1@${PY_FLAVOR}

OPTIONS_DEFINE=	DOCS

NO_ARCH=	yes
USES=		python shebangfix
SHEBANG_FILES=	tools/*.py
USE_PYTHON=	autoplist concurrent distutils

PORTDOCS=	CHANGES.txt README.md
TOOLS=		cmcdump.py cmpdump.py crldump.py crmfdump.py ocspclient.py \
		ocspreqdump.py ocsprspdump.py pkcs10dump.py pkcs1dump.py \
		pkcs7dump.py pkcs8dump.py snmpget.py x509dump-rfc5280.py \
		x509dump.py

post-install:
	${INSTALL_SCRIPT} ${TOOLS:S|^|${WRKSRC}/tools/|} ${STAGEDIR}${PREFIX}/bin
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${PORTDOCS:S|^|${WRKSRC}/|} ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
