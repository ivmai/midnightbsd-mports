PORTNAME=	rspamd
PORTVERSION=	3.7.4
PORTREVISION=	3
CATEGORIES=	mail

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Fast spam filtering system
WWW=		https://rspamd.com/

LICENSE=	apache2
LICENSE_FILE=	${WRKSRC}/LICENSE.md

LIB_DEPENDS=	libicui18n.so:devel/icu \
		libpcre2-8.so:devel/pcre2 \
		libsodium.so:security/libsodium
BUILD_DEPENDS=	ragel:devel/ragel
RUN_DEPENDS=	ca_root_nss>=3:security/ca_root_nss

USES=		cmake compiler:c++20-lang cpe gnome perl5 pkgconfig sqlite ssl
CPE_VENDOR=	rspamd_project
USE_LDCONFIG=	yes
USE_PERL5=	build run
USE_GNOME=	glib20

CONFLICTS=		elfutils
CONFLICTS_INSTALL=	rspamd-devel

USERS=		rspamd
GROUPS=		rspamd

OPTIONS_DEFINE=			BLAS CGP GPERF LUAJIT
OPTIONS_DEFINE_amd64=		HYPERSCAN
OPTIONS_DEFAULT_amd64=		HYPERSCAN LUAJIT
OPTIONS_DEFAULT_armv7=		LUAJIT
OPTIONS_DEFAULT_i386=		LUAJIT
OPTIONS_SUB=	yes

BLAS_DESC=	Use OpenBLAS to accelerate KANN
CGP_DESC=	Install Communigate Pro(tm) helper
GPERF_DESC=	Google perf-tools profiling
HYPERSCAN_DESC=	Use hyperscan optimizations (amd64 only)
LUAJIT_DESC=	Use LuaJIT instead of standard Lua

SUB_FILES=	pkg-message rspamd.newsyslog.conf.sample
PLIST_SUB+=	ETCDIR=etc/rspamd \
		RSPAMDVERSION=${PORTVERSION}
CMAKE_ARGS+=	-DCONFDIR=${PREFIX}/etc/rspamd \
		-DLOGDIR=/var/log/rspamd \
		-DDBDIR=/var/db/rspamd \
		-DRUNDIR=/var/run/rspamd \
		-DMANDIR=${PREFIX}/share/man \
		-DCMAKE_INSTALL_PREFIX=${PREFIX} \
		-DBUILD_PORT=yes \
		-DLIBDIR=${PREFIX}/lib/rspamd

USE_GITHUB=	yes

USE_RC_SUBR=	rspamd

BLAS_CMAKE_ON=	-DENABLE_BLAS=ON
BLAS_LIB_DEPENDS=	libblis.so:math/blis liblapack.so:math/lapack
BLAS_USES=	blaslapack:openblas

GPERF_CMAKE_ON=	-DENABLE_GPERF_TOOLS=ON
GPERF_LIB_DEPENDS=	libprofiler.so:devel/google-perftools

HYPERSCAN_CMAKE_ON=	-DENABLE_HYPERSCAN=ON
HYPERSCAN_LIB_DEPENDS=	libhs.so:devel/hyperscan

LUAJIT_CMAKE_OFF=	-DENABLE_LUAJIT=OFF
LUAJIT_USES=		luajit
LUAJIT_USES_OFF=	lua:51+

CGP_RUN_DEPENDS+=	\
	p5-AnyEvent-HTTP>=0:www/p5-AnyEvent-HTTP \
	p5-AnyEvent>=0:devel/p5-AnyEvent \
	p5-EV>=0:devel/p5-EV \
	p5-JSON-XS>=0:converters/p5-JSON-XS

post-install:
	@${MKDIR} \
		${FAKE_DESTDIR}/var/log/rspamd \
		${FAKE_DESTDIR}/var/db/rspamd \
		${FAKE_DESTDIR}/var/run/rspamd
	${INSTALL_DATA} ${WRKDIR}/rspamd.newsyslog.conf.sample ${ETCDIR}
	@${MKDIR} ${PREFIX}/etc/newsyslog.conf.d
	${LN} -sf ${ETCDIR}/rspamd.newsyslog.conf ${PREFIX}/etc/newsyslog.conf.d

post-install-CGP-on:
	${INSTALL_SCRIPT} ${WRKSRC}/utils/cgp_rspamd.pl ${FAKE_DESTDIR}${PREFIX}/bin/rspamd-cgp-helper

.include <bsd.port.mk>
