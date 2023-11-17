--- src/3rdparty/chromium/content/browser/utility_process_host_receiver_bindings.cc.orig	2022-09-26 10:05:50 UTC
+++ src/3rdparty/chromium/content/browser/utility_process_host_receiver_bindings.cc
@@ -10,7 +10,7 @@
 #include "content/public/browser/content_browser_client.h"
 #include "content/public/common/content_client.h"
 
-#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_BSD)
 #include "components/services/font/public/mojom/font_service.mojom.h"  // nogncheck
 #include "content/browser/font_service.h"  // nogncheck
 #endif
@@ -19,7 +19,7 @@ void UtilityProcessHost::BindHostReceiver(
 
 void UtilityProcessHost::BindHostReceiver(
     mojo::GenericPendingReceiver receiver) {
-#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_BSD)
   if (auto font_receiver = receiver.As<font_service::mojom::FontService>()) {
     ConnectToFontService(std::move(font_receiver));
     return;
