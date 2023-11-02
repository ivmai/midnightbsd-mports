--- src/3rdparty/chromium/media/capture/video/create_video_capture_device_factory.cc.orig	2021-12-15 16:12:54 UTC
+++ src/3rdparty/chromium/media/capture/video/create_video_capture_device_factory.cc
@@ -10,7 +10,7 @@
 #include "media/capture/video/fake_video_capture_device_factory.h"
 #include "media/capture/video/file_video_capture_device_factory.h"
 
-#if defined(OS_LINUX) && !defined(OS_CHROMEOS)
+#if (defined(OS_LINUX) && !defined(OS_CHROMEOS)) || defined(OS_BSD)
 #include "media/capture/video/linux/video_capture_device_factory_linux.h"
 #elif defined(OS_CHROMEOS)
 #include "media/capture/video/chromeos/camera_app_device_bridge_impl.h"
@@ -82,7 +82,7 @@ CreatePlatformSpecificVideoCaptureDeviceFactory(
 std::unique_ptr<VideoCaptureDeviceFactory>
 CreatePlatformSpecificVideoCaptureDeviceFactory(
     scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner) {
-#if defined(OS_LINUX) && !defined(OS_CHROMEOS)
+#if (defined(OS_LINUX) && !defined(OS_CHROMEOS)) || defined(OS_BSD)
   return std::make_unique<VideoCaptureDeviceFactoryLinux>(ui_task_runner);
 #elif defined(OS_CHROMEOS)
   return CreateChromeOSVideoCaptureDeviceFactory(ui_task_runner, {});
