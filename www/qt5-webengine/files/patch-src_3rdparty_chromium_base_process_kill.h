--- src/3rdparty/chromium/base/process/kill.h.orig	2021-12-15 16:12:54 UTC
+++ src/3rdparty/chromium/base/process/kill.h
@@ -113,11 +113,11 @@ BASE_EXPORT TerminationStatus GetKnownDeadTerminationS
 BASE_EXPORT TerminationStatus GetKnownDeadTerminationStatus(
     ProcessHandle handle, int* exit_code);
 
-#if defined(OS_LINUX) || defined(OS_CHROMEOS)
+#if defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_BSD)
 // Spawns a thread to wait asynchronously for the child |process| to exit
 // and then reaps it.
 BASE_EXPORT void EnsureProcessGetsReaped(Process process);
-#endif  // defined(OS_LINUX) || defined(OS_CHROMEOS)
+#endif  // defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_BSD)
 #endif  // defined(OS_POSIX)
 
 // Registers |process| to be asynchronously monitored for termination, forcibly
