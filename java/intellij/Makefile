# Created by: Tobias Kortkamp <t@tobik.me>


# Based on the devel/intellij port from OpenBSD by
# Vadim Zhukov <zhuk@openbsd.org>

PORTNAME=	intellij
PORTVERSION=	2016.2.2
CATEGORIES=	java devel
MASTER_SITES=	https://download.jetbrains.com/idea/ \
		http://download.jetbrains.com/idea/
DISTNAME=	ideaIC-${PORTVERSION}

MAINTAINER=	ports@MidnightBSD.org
COMMENT=	IntelliJ IDEA Community Edition

LICENSE=	apache2

BUILD_DEPENDS=	${DEPEND_JAVA}
RUN_DEPENDS=	intellij-fsnotifier>0:${PORTSDIR}/java/intellij-fsnotifier \
		intellij-pty4j>0:${PORTSDIR}/java/intellij-pty4j

USE_JAVA=	yes
JAVA_VERSION=	1.7+
JAVA_RUN=	yes

NO_ARCH=	yes
NO_BUILD=	yes

WRKDIST=	${WRKDIR}/idea-IC-162.1628.40

.include "common.mk"

PLIST_SUB+=	IDEA_HOME=${IDEA_HOME_REL}
SUB_FILES+=	idea idea.desktop pkg-message
SUB_LIST+=	IDEA_HOME=${IDEA_HOME}

do-install:
	${MKDIR} ${STAGEDIR}${IDEA_HOME}
	@${TAR} -czf - -C ${WRKDIST} . | ${TAR} xzf - -C ${STAGEDIR}${IDEA_HOME}
# Linux/Windows/OS X only so remove them
	@${RM} ${STAGEDIR}${IDEA_HOME}/bin/fsnotifier \
		${STAGEDIR}${IDEA_HOME}/bin/fsnotifier-arm \
		${STAGEDIR}${IDEA_HOME}/bin/fsnotifier64 \
		${STAGEDIR}${IDEA_HOME}/bin/libbreakgen.so \
		${STAGEDIR}${IDEA_HOME}/bin/libbreakgen64.so \
		${STAGEDIR}${IDEA_HOME}/plugins/gradle/lib/native-platform-linux-amd64-0.10.jar \
		${STAGEDIR}${IDEA_HOME}/plugins/gradle/lib/native-platform-linux-i386-0.10.jar \
		${STAGEDIR}${IDEA_HOME}/plugins/gradle/lib/native-platform-osx-amd64-0.10.jar \
		${STAGEDIR}${IDEA_HOME}/plugins/gradle/lib/native-platform-osx-i386-0.10.jar \
		${STAGEDIR}${IDEA_HOME}/plugins/gradle/lib/native-platform-windows-amd64-0.10.jar \
		${STAGEDIR}${IDEA_HOME}/plugins/gradle/lib/native-platform-windows-i386-0.10.jar
# Remove the bundled native Pty4J support libraries, they are replaced
# by java/intellij-pty4j
	@${RM} -r ${STAGEDIR}${IDEA_HOME}/lib/libpty
	@${RM} -r ${STAGEDIR}${IDEA_HOME}/jre/jre
	${INSTALL_SCRIPT} ${WRKDIR}/idea ${STAGEDIR}${PREFIX}/bin/idea
	${INSTALL_MAN} ${FILESDIR}/idea.1 ${STAGEDIR}${PREFIX}/man/man1
	${INSTALL_DATA} ${WRKDIR}/idea.desktop ${STAGEDIR}${PREFIX}/share/applications/
	cd ${WRKDIST}/lib && ${JAVA_HOME}/bin/jar xf icons.jar
	${INSTALL_DATA} ${WRKDIST}/lib/icon.png ${STAGEDIR}${IDEA_HOME}/idea.png
# TODO: Remove and enable fsnotifier when devel/libinotify is fixed
# Disable filewatcher warning message on IDEA startup
	${ECHO} "idea.filewatcher.disabled=true" >> ${STAGEDIR}${IDEA_HOME}/bin/idea.properties
# Use fsnotifier replacement provided by java/intellij-fsnotifier
#	${ECHO} "idea.filewatcher.executable.path=${IDEA_HOME}/bin/fsnotifier" >> ${STAGEDIR}${IDEA_HOME}/bin/idea.properties

.include <bsd.port.mk>
