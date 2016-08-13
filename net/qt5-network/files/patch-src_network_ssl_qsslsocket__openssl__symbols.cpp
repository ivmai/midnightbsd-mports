--- src/network/ssl/qsslsocket_openssl_symbols.cpp.orig	2015-02-17 04:56:38 UTC
+++ src/network/ssl/qsslsocket_openssl_symbols.cpp
@@ -611,8 +611,8 @@ static QPair<QLibrary*, QLibrary*> loadO
 #endif
 #if defined(SHLIB_VERSION_NUMBER) && !defined(Q_OS_QNX) // on QNX, the libs are always libssl.so and libcrypto.so
     // first attempt: the canonical name is libssl.so.<SHLIB_VERSION_NUMBER>
-    libssl->setFileNameAndVersion(QLatin1String("ssl"), QLatin1String(SHLIB_VERSION_NUMBER));
-    libcrypto->setFileNameAndVersion(QLatin1String("crypto"), QLatin1String(SHLIB_VERSION_NUMBER));
+    libssl->setFileNameAndVersion(QLatin1String("/usr/local/libssl"), QLatin1String(SHLIB_VERSION_NUMBER));
+    libcrypto->setFileNameAndVersion(QLatin1String("/usr/local/libcrypto"), QLatin1String(SHLIB_VERSION_NUMBER));
     if (libcrypto->load() && libssl->load()) {
         // libssl.so.<SHLIB_VERSION_NUMBER> and libcrypto.so.<SHLIB_VERSION_NUMBER> found
         return pair;
@@ -629,8 +629,8 @@ static QPair<QLibrary*, QLibrary*> loadO
     //  OS X's /usr/lib/libssl.dylib, /usr/lib/libcrypto.dylib will be picked up in the third
     //    attempt, _after_ <bundle>/Contents/Frameworks has been searched.
     //  iOS does not ship a system libssl.dylib, libcrypto.dylib in the first place.
-    libssl->setFileNameAndVersion(QLatin1String("ssl"), -1);
-    libcrypto->setFileNameAndVersion(QLatin1String("crypto"), -1);
+    libssl->setFileNameAndVersion(QLatin1String("/usr/local/lib/libssl"), -1);
+    libcrypto->setFileNameAndVersion(QLatin1String("/usr/local/lib/libcrypto"), -1);
     if (libcrypto->load() && libssl->load()) {
         // libssl.so.0 and libcrypto.so.0 found
         return pair;
