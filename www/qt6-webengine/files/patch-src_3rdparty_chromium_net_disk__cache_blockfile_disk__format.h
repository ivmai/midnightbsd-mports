--- src/3rdparty/chromium/net/disk_cache/blockfile/disk_format.h.orig	2023-03-28 19:45:02 UTC
+++ src/3rdparty/chromium/net/disk_cache/blockfile/disk_format.h
@@ -153,7 +153,9 @@ struct RankingsNode {
 };
 #pragma pack(pop)
 
+#if !defined(OS_BSD)
 static_assert(sizeof(RankingsNode) == 36, "bad RankingsNode");
+#endif
 
 }  // namespace disk_cache
 
