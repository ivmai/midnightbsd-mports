PORTNAME=	mksh
DISTVERSION=	R59c
CATEGORIES=	shells
MASTER_SITES=	http://www.mirbsd.org/MirOS/dist/mir/mksh/ \
		https://pub.allbsd.org/MirOS/dist/mir/mksh/
		
DISTFILES=	${PORTNAME}-${DISTVERSION}.tgz

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	MirBSD enhanced shell based on pdksh

LICENSE=	agg

WRKSRC=		${WRKDIR}/${PORTNAME}

PLIST_FILES=	bin/mksh share/examples/mksh/dot.mkshrc share/man/man1/mksh.1.gz
PLIST_DIRS=	share/examples/mksh

PKGINSTALL=	pkg-install
PKGDEINSTALL=	pkg-deinstall

.include <bsd.port.pre.mk>

do-build:
	cd ${WRKSRC} && CFLAGS="${CFLAGS}" CC="${CC}" LDFLAGS="${LDFLAGS}" CPPFLAGS="${CPPFLAGS}" SHELL=${SH} ${SH} ${WRKSRC}/Build.sh -Q -r

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/mksh ${PREFIX}/bin
	${MKDIR} ${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/dot.mkshrc ${EXAMPLESDIR}
	${INSTALL_MAN} ${WRKSRC}/mksh.1 ${PREFIX}/share/man/man1

.include <bsd.port.post.mk>
