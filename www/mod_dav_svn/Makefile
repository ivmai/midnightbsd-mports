PORTNAME=	mod_dav_svn
DISTNAME=	subversion-${PORTVERSION}

CATEGORIES=	www

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	Apache module for subversion serving
WWW=		https://subversion.apache.org/

USES=		apache:2.4+

PORTREVISION_LATEST=	2
PORTREVISION_LTS=		2

.include "${.CURDIR}/../../devel/subversion/Makefile.addons"

CONFIGURE_ARGS+=	--with-apxs=${APXS} \
			--with-apache-libexecdir \
			--without-gnome-keyring \
			--without-kwallet
CONFIGURE_TARGET=      ${ARCH}-portbld-freebsd12.4
SUB_FILES+=	220_subversion.conf.sample

PLIST_SUB+=	SED=${SED}

ALL_TARGET=	apache-mod
INSTALL_TARGET=	install-mods-shared

post-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/${APACHEETCDIR}/modules.d
	${INSTALL_DATA} ${WRKDIR}/220_subversion.conf.sample \
		${STAGEDIR}${PREFIX}/${APACHEETCDIR}/modules.d

.include <bsd.port.post.mk>
