PORTNAME=	libbind
PORTVERSION=	6.0
PORTREVISION=	6
CATEGORIES=	dns net
MASTER_SITES=	ISC/libbind/${PORTVERSION}
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} ${DISTNAME}${EXTRACT_SUFX}.asc
EXTRACT_ONLY=	${DISTNAME}${EXTRACT_SUFX}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Standard C resolver library
WWW=		https://www.isc.org/software/libbind

LICENSE=	mit
LICENSE_FILE=	${WRKSRC}/COPYRIGHT

MAKE_JOBS_UNSAFE=	yes

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--localstatedir=/var --with-randomdev=/dev/random
CONFIGURE_TARGET=	${ARCH}-portbld-freebsd12.4
USES=		groff

OPTIONS_DEFINE=	IPV6 THREADS
OPTIONS_DEFAULT=	THREADS

IPV6_CONFIGURE_ENABLE=		ipv6
THREADS_CONFIGURE_ENABLE=	threads

verify:	checksum
	gpg --verify ${DISTDIR}/${DISTNAME}${EXTRACT_SUFX}.asc

post-patch:
	${REINPLACE_CMD} -e '/#include <utmp.h>/ d' ${WRKSRC}/irs/*.c

.include <bsd.port.mk>
