PORTNAME=	opus
DISTVERSION=	1.5.2
CATEGORIES=	audio
MASTER_SITES=	https://downloads.xiph.org/releases/opus/

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	IETF audio codec
WWW=		https://opus-codec.org/

LICENSE=	bsd3
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		cpe gmake libtool pathfix
CPE_VENDOR=	opus-codec
USE_LDCONFIG=	yes

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--enable-custom-modes \
		--enable-dred \
		--enable-osce \
		--disable-doc   # requires doxygen
CONFIGURE_TARGET=${ARCH:S/amd64/x86_64/}-portbld-${OPSYS:tl}${OSREL}
INSTALL_TARGET=	install-strip
TEST_TARGET=	check

.include <bsd.port.mk>
