--- src/3rdparty/chromium/media/webrtc/webrtc_features.cc.orig	2023-03-28 19:45:02 UTC
+++ src/3rdparty/chromium/media/webrtc/webrtc_features.cc
@@ -9,7 +9,7 @@ namespace {
 
 namespace features {
 namespace {
-#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX)
+#if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)
 constexpr base::FeatureState kWebRtcHybridAgcState =
     base::FEATURE_ENABLED_BY_DEFAULT;
 #else
@@ -19,7 +19,7 @@ constexpr base::FeatureState kWebRtcHybridAgcState =
 }  // namespace
 
 #if BUILDFLAG(IS_WIN) || BUILDFLAG(IS_MAC) || BUILDFLAG(IS_LINUX) || \
-    BUILDFLAG(IS_CHROMEOS)
+    BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_BSD)
 constexpr base::FeatureState kWebRtcAnalogAgcClippingControlState =
     base::FEATURE_ENABLED_BY_DEFAULT;
 #else
