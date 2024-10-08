PORTNAME=	sharutils
PORTVERSION=	4.15.2
PORTREVISION=	2
CATEGORIES=	archivers
MASTER_SITES=	GNU

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Pack, send, and unpack shell archives; synchronize via e-mail
WWW=		https://www.gnu.org/s/sharutils/

LICENSE=	gpl3

USES=		charsetfix cpe perl5 tar:xz

OPTIONS_DEFINE=	NLS

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--program-prefix=g --disable-uucode
INSTALL_TARGET=	install install-man
INFO=		sharutils
USE_PERL5=	build
OPTIONS_SUB=	yes
CPE_VENDOR=	gnu

NLS_USES=	gettext
NLS_CONFIGURE_ON=	--with-libintl-prefix="${LOCALBASE}"
NLS_CONFIGURE_OFF=	--disable-nls

post-patch:
	@${REINPLACE_CMD} -e '/Please include config.h first./ s,^.*$$,#include <config.h>,' \
		${WRKSRC}/lib/unistd.in.h
	@${REINPLACE_CMD} -e '/char const . const program_name/d' \
		${WRKSRC}/src/shar-opts.h \
		${WRKSRC}/src/shar-opts.c \
		${WRKSRC}/src/unshar-opts.h \
		${WRKSRC}/src/unshar-opts.c \
		${WRKSRC}/src/uudecode-opts.h \
		${WRKSRC}/src/uudecode-opts.c \
		${WRKSRC}/src/uuencode-opts.h
.for man in shar.1 unshar.1
	@${REINPLACE_CMD} \
		-e 's, SHAR , GSHAR ,' \
		-e 's,Shar,Gshar,' \
		-e 's, shar , gshar ,g' \
		-e 's,^shar ,gshar ,' \
		-e 's, UNSHAR , GUNSHAR ,' \
		-e 's,Unshar,Gunshar,' \
		-e 's,^unshar ,gunshar ,' \
		-e 's,f2shar\\f1,f2gshar\\f1,' \
		-e 's, unshar , gunshar ,g' \
		-e 's,gshar file,shar file,g' \
		-e 's,shar\,,gshar\,,' \
		-e 's,shar(,gshar(,' \
		-e 's,unshar(,gunshar(,' \
		-e 's, shar\$$, gshar,' \
		${WRKSRC}/doc/${man}
.endfor

.include <bsd.port.mk>
