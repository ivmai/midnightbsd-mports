--- src/3rdparty/chromium/third_party/perfetto/include/perfetto/base/build_config.h.orig	2022-09-26 10:05:50 UTC
+++ src/3rdparty/chromium/third_party/perfetto/include/perfetto/base/build_config.h
@@ -27,6 +27,7 @@
 #if defined(__ANDROID__)
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_ANDROID() 1
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_LINUX() 0
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_BSD() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_WIN() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_APPLE() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_MAC() 0
@@ -38,6 +39,7 @@
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_ANDROID() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_APPLE() 1
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_LINUX() 0
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_BSD() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_WIN() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_WASM() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_FUCHSIA() 0
@@ -51,9 +53,10 @@
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_MAC() 1
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_IOS() 0
 #endif
-#elif defined(__linux__)
+#elif defined(__linux__) || defined(__OpenBSD__) || defined(__FreeBSD__)
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_ANDROID() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_LINUX() 1
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_BSD() 1
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_WIN() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_APPLE() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_MAC() 0
@@ -64,6 +67,8 @@
 #elif defined(_WIN32)
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_ANDROID() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_LINUX() 0
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_BSD() 0
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_FREEBSD() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_WIN() 1
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_APPLE() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_MAC() 0
@@ -74,6 +79,8 @@
 #elif defined(__EMSCRIPTEN__)
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_ANDROID() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_LINUX() 0
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_BSD() 0
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_FREEBSD() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_WIN() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_APPLE() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_MAC() 0
@@ -87,6 +94,8 @@
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_MAC() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_IOS() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_LINUX() 0
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_BSD() 0
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_FREEBSD() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_WIN() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_WASM() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_FUCHSIA() 1
@@ -94,6 +103,8 @@
 #elif defined(__native_client__)
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_ANDROID() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_LINUX() 0
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_BSD() 0
+#define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_FREEBSD() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_WIN() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_APPLE() 0
 #define PERFETTO_BUILDFLAG_DEFINE_PERFETTO_OS_MAC() 0
