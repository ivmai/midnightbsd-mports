PORTNAME=	dosbox
DISTVERSION=	0.74-3
PORTREVISION=	3
CATEGORIES=	emulators
MASTER_SITES=	SF/${PORTNAME}/${PORTNAME}/${DISTVERSION}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Emulator of a PC with DOS

LICENSE=	gpl2

LIB_DEPENDS=	libpng.so:graphics/png

GNU_CONFIGURE=	yes
USES=		cpe sdl
USE_SDL=	sdl net sound
PORTDOCS=	NEWS README

PKGMESSAGE=	${WRKDIR}/pkg-message

CPPFLAGS+=		-I${LOCALBASE}/include
CONFIGURE_ARGS+=	--enable-core-inline

DESKTOP_ENTRIES="DOSBox" "${COMMENT}" \
		"${TRUE_PREFIX}/share/pixmaps/dosbox.ico" "dosbox" \
		"System;Emulator;" "true"

OPTIONS_RADIO=	DEBUGGER
OPTIONS_RADIO_DEBUGGER=DEBUGGER_ENABLE DEBUGGER_HEAVY
DEBUGGER_ENABLE_DESC=Enable internal debugger
DEBUGGER_HEAVY_DESC=Enable internal debugger with extra features

DEBUGGER_ENABLE_CONFIGURE_ON=	--enable-debug=yes
DEBUGGER_HEAVY_CONFIGURE_ON=	--enable-debug=heavy

post-patch:
	@${REINPLACE_CMD} -e 's#\/usr\/share\/doc\/dosbox#${DOCSDIR}#g' \
		${WRKSRC}/docs/dosbox.1

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/src/dosbox ${PREFIX}/bin/dosbox
	${INSTALL_DATA} ${WRKSRC}/src/dosbox.ico ${PREFIX}/share/pixmaps/
	${INSTALL_MAN} ${WRKSRC}/docs/dosbox.1 ${PREFIX}/share/man/man1/
	@${MKDIR} ${DOCSDIR}
	${INSTALL_DATA} ${PORTDOCS:S|^|${WRKSRC}/|} ${DOCSDIR}

.include <bsd.port.mk>
