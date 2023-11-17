--- src/3rdparty/chromium/content/utility/speech/speech_recognition_sandbox_hook_linux.cc.orig	2022-09-26 10:05:50 UTC
+++ src/3rdparty/chromium/content/utility/speech/speech_recognition_sandbox_hook_linux.cc
@@ -12,11 +12,14 @@
 #include "sandbox/linux/syscall_broker/broker_command.h"
 #include "sandbox/linux/syscall_broker/broker_file_permission.h"
 
+#if !defined(OS_BSD)
 using sandbox::syscall_broker::BrokerFilePermission;
 using sandbox::syscall_broker::MakeBrokerCommandSet;
+#endif
 
 namespace speech {
 
+#if !defined(OS_BSD)
 namespace {
 
 // Gets the file permissions required by the Speech On-Device API (SODA).
@@ -50,9 +53,11 @@ std::vector<BrokerFilePermission> GetSodaFilePermissio
 }
 
 }  // namespace
+#endif
 
 bool SpeechRecognitionPreSandboxHook(
     sandbox::policy::SandboxLinux::Options options) {
+#if !defined(OS_BSD)
 #if BUILDFLAG(ENABLE_SODA)
   base::FilePath test_binary_path = GetSodaTestBinaryPath();
   DVLOG(0) << "SODA test binary path: " << test_binary_path.value().c_str();
@@ -77,6 +82,7 @@ bool SpeechRecognitionPreSandboxHook(
                                sandbox::policy::SandboxLinux::PreSandboxHook(),
                                options);
   instance->EngageNamespaceSandboxIfPossible();
+#endif
 
   return true;
 }
