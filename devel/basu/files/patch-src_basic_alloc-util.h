--- src/basic/alloc-util.h.orig	2021-01-06 13:56:51 UTC
+++ src/basic/alloc-util.h
@@ -38,7 +38,7 @@ static inline void *mfree(void *memory)
                 0;                              \
         })
 
-#if defined(__MidnightBSD__) || defined(__FreeBSD__)
+#ifdef __MidnightBSD__
 #define mempcpy __builtin_mempcpy
 #endif
 
