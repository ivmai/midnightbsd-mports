PORTNAME=	finch

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Finch multi-protocol messaging client (Console UI)

LIB_DEPENDS=	libpurple.so:net-im/libpurple \
		libgnt.so:devel/libgnt

MASTERDIR=	${.CURDIR}/../libpurple
BUILD_WRKSRC=	${WRKSRC}/finch
INSTALL_WRKSRC=	${BUILD_WRKSRC}
DESCR=		${.CURDIR}/pkg-descr
PLIST=		${.CURDIR}/pkg-plist

PIDGIN_SLAVE=	yes
WITH_CONSOLEUI=	yes

CPPFLAGS+=	-DNCURSES_WIDECHAR -D_XOPEN_SOURCE_EXTENDED
USE_LDCONFIG=	yes
CONFIGURE_ARGS=	--disable-gtkui \
		--disable-schemas-install \
		--disable-nm \
		--with-dynamic_prpls=${PRPL_MODULES:S/,$//}

CPE_PRODUCT=	pidgin

post-install:
	${INSTALL_MAN} ${WRKSRC}/doc/finch.1 ${STAGEDIR}${PREFIX}/share/man/man1

.include "${MASTERDIR}/Makefile"
