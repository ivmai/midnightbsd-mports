--- src/3rdparty/chromium/third_party/angle/src/gpu_info_util/SystemInfo_internal.h.orig	2022-09-26 10:05:50 UTC
+++ src/3rdparty/chromium/third_party/angle/src/gpu_info_util/SystemInfo_internal.h
@@ -14,6 +14,13 @@ namespace angle
 namespace angle
 {
 
+#if defined(__OpenBSD__) || defined(__FreeBSD__)
+bool CollectMesaCardInfo(std::vector<GPUDeviceInfo> *devices);                
+#if defined(__FreeBSD__)
+bool GetPCIDevicesFreeBSD(std::vector<GPUDeviceInfo> *devices);
+#endif
+#endif
+
 // Defined in SystemInfo_libpci when GPU_INFO_USE_LIBPCI is defined.
 bool GetPCIDevicesWithLibPCI(std::vector<GPUDeviceInfo> *devices);
 // Defined in SystemInfo_x11 when GPU_INFO_USE_X11 is defined.
