PORTNAME=	libraw
PORTVERSION=	0.21.2
CATEGORIES=	graphics
MASTER_SITES=	http://www.libraw.org/data/
DISTNAME=	LibRaw-${PORTVERSION}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Library for manipulating raw images
WWW=		https://www.libraw.org/

LICENSE=	lgpl2.1 cddl
LICENSE_COMB=	dual

USES=		autoreconf cpe libtool localbase pathfix pkgconfig
USE_LDCONFIG=	yes

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--disable-examples
INSTALL_TARGET=	install-strip

PORTDOCS=	*
PORTEXAMPLES=	*

OPTIONS_DEFINE=		DOCS EXAMPLES JASPER JPEG LCMS2 OPENMP OPTIMIZED_CFLAGS \
			RPIRAW X3F
OPTIONS_DEFAULT=	JPEG LCMS2

JASPER_CONFIGURE_ENABLE=		jasper
JASPER_LIB_DEPENDS=			libjasper.so:graphics/jasper

JPEG_CONFIGURE_ENABLE=			jpeg
JPEG_USES=				jpeg

LCMS2_CONFIGURE_ENABLE=			lcms
LCMS2_LIB_DEPENDS=			liblcms2.so:graphics/lcms2

OPENMP_DESC=				OpenMP support (implies GCC)
OPENMP_CONFIGURE_ENABLE=		openmp
OPENMP_USES=				compiler:openmp

RPIRAW_DESC=				Raspberry Pi RAW+JPEG support
RPIRAW_CPPFLAGS=			-DUSE_6BY9RPI

X3F_DESC=				X3F (Foveon) support
X3F_CPPFLAGS=				-DUSE_X3FTOOLS

OPTIMIZED_CFLAGS_CFLAGS=		-O3

post-patch:
	@${REINPLACE_CMD} -e 's|-lstdc++||g' ${WRKSRC}/*.pc.in
	@${TOUCH} -r ${WRKSRC}/configure.ac ${WRKSRC}/aclocal.m4

# Use "\*" instead of "." in COPYTREE_SHARE commands as "." has
# the undesired effect of copying ".deps" directory
post-install-DOCS-on:
	@${MKDIR} ${FAKE_DESTDIR}${DOCSDIR}
	cd ${WRKSRC}/doc && \
		${COPYTREE_SHARE} \* ${FAKE_DESTDIR}${DOCSDIR}

post-install-EXAMPLES-on:
	@${MKDIR} ${FAKE_DESTDIR}${EXAMPLESDIR}
	cd ${WRKSRC}/samples && \
		${COPYTREE_SHARE} \* ${FAKE_DESTDIR}${EXAMPLESDIR}

.include <bsd.port.mk>
