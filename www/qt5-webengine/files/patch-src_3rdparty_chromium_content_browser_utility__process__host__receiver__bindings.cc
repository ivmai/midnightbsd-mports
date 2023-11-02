--- src/3rdparty/chromium/content/browser/utility_process_host_receiver_bindings.cc.orig	2021-12-15 16:12:54 UTC
+++ src/3rdparty/chromium/content/browser/utility_process_host_receiver_bindings.cc
@@ -10,7 +10,7 @@
 #include "content/public/browser/content_browser_client.h"
 #include "content/public/common/content_client.h"
 
-#if defined(OS_LINUX) || defined(OS_CHROMEOS)
+#if defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_BSD)
 #include "components/services/font/public/mojom/font_service.mojom.h"  // nogncheck
 #include "content/browser/font_service.h"  // nogncheck
 #endif
@@ -19,7 +19,7 @@ void UtilityProcessHost::BindHostReceiver(
 
 void UtilityProcessHost::BindHostReceiver(
     mojo::GenericPendingReceiver receiver) {
-#if defined(OS_LINUX) || defined(OS_CHROMEOS)
+#if defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_BSD)
   if (auto font_receiver = receiver.As<font_service::mojom::FontService>()) {
     ConnectToFontService(std::move(font_receiver));
     return;
