PORTNAME=	SDL
PORTVERSION=	2.548
PORTREVISION=	2
CATEGORIES=	devel perl5
MASTER_SITES=	CPAN
PKGNAMEPREFIX=	p5-

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Perl Bindings for SDL
WWW=		http://sdl.perl.org/

LICENSE=	gpl2

BUILD_DEPENDS=	${RUN_DEPENDS}
LIB_DEPENDS=	libpng.so:graphics/png \
		libtiff.so:graphics/tiff \
		libsmpeg.so:multimedia/smpeg
RUN_DEPENDS=	p5-Alien-SDL>=1.446:devel/p5-Alien-SDL \
		p5-File-ShareDir>=1.0:devel/p5-File-ShareDir \
		p5-Tie-Simple>=0:devel/p5-Tie-Simple

USES=		gl jpeg perl5 sdl
USE_GL=		glu
USE_PERL5=	modbuild
USE_SDL=	gfx image mixer pango sdl ttf

NO_TEST=	yes

.include <bsd.port.mk>
