PORTNAME=	fping
PORTVERSION=	5.0
PORTREVISION=	1
CATEGORIES=	net
MASTER_SITES=	http://fping.org/dist/ \
		https://github.com/schweikert/${PORTNAME}/releases/download/v${PORTVERSION}/

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Quickly ping N hosts w/o flooding the network

LICENSE=	PreviousBSD
LICENSE_GROUPS=	FSF
LICENSE_NAME=	Previous BSD License
LICENSE_FILE=	${WRKSRC}/COPYING
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

USES=		autoreconf

GNU_CONFIGURE=	yes
INSTALL_TARGET=	install-strip

OPTIONS_DEFINE=	IPV6
OPTIONS_SUB=	yes
IPV6_CONFIGURE_OFF=--disable-ipv6

post-install-IPV6-on:
	${RLN} ${FAKE_DESTDIR}${PREFIX}/sbin/fping  ${FAKE_DESTDIR}${PREFIX}/sbin/fping6
	${RLN} ${FAKE_DESTDIR}${PREFIX}/share/man/man8/fping.8 ${FAKE_DESTDIR}${PREFIX}/share/man/man8/fping6.8

.include <bsd.port.mk>
