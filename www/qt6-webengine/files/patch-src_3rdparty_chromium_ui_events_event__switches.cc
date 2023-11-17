--- src/3rdparty/chromium/ui/events/event_switches.cc.orig	2023-03-28 19:45:02 UTC
+++ src/3rdparty/chromium/ui/events/event_switches.cc
@@ -21,7 +21,7 @@ const char kTouchSlopDistance[] = "touch-slop-distance
 // value is a floating point number that is interpreted as a distance in pixels.
 const char kTouchSlopDistance[] = "touch-slop-distance";
 
-#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
+#if BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS) || BUILDFLAG(IS_BSD)
 // Tells chrome to interpret events from these devices as touch events. Only
 // available with XInput 2 (i.e. X server 1.8 or above). The id's of the
 // devices can be retrieved from 'xinput list'.
