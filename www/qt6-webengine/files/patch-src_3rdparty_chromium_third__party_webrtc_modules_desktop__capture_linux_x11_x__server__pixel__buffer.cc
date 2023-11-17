--- src/3rdparty/chromium/third_party/webrtc/modules/desktop_capture/linux/x11/x_server_pixel_buffer.cc.orig	2022-09-26 10:05:50 UTC
+++ src/3rdparty/chromium/third_party/webrtc/modules/desktop_capture/linux/x11/x_server_pixel_buffer.cc
@@ -212,6 +212,12 @@ void XServerPixelBuffer::InitShm(const XWindowAttribut
 void XServerPixelBuffer::InitShm(const XWindowAttributes& attributes) {
   Visual* default_visual = attributes.visual;
   int default_depth = attributes.depth;
+#if defined(__OpenBSD__)
+// pledge(2)
+  RTC_LOG(LS_WARNING) << "Unable to use shmget(2) while using pledge(2). "
+                         "Performance may be degraded.";
+  return;
+#endif
 
   int major, minor;
   Bool have_pixmaps;
