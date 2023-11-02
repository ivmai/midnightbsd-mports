--- src/3rdparty/chromium/media/capture/video/video_capture_device_client.cc.orig	2021-12-15 16:12:54 UTC
+++ src/3rdparty/chromium/media/capture/video/video_capture_device_client.cc
@@ -318,7 +318,7 @@ void VideoCaptureDeviceClient::OnIncomingCapturedData(
 // see http://linuxtv.org/downloads/v4l-dvb-apis/packed-rgb.html.
 // Windows RGB24 defines blue at lowest byte,
 // see https://msdn.microsoft.com/en-us/library/windows/desktop/dd407253
-#if defined(OS_LINUX) || defined(OS_CHROMEOS)
+#if defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_BSD)
       fourcc_format = libyuv::FOURCC_RAW;
 #elif defined(OS_WIN)
       fourcc_format = libyuv::FOURCC_24BG;
