--- ext/pcre/pcre2lib/sljit/sljitConfigInternal.h.orig	2023-03-14 19:50:20 UTC
+++ ext/pcre/pcre2lib/sljit/sljitConfigInternal.h
@@ -319,7 +319,7 @@ extern "C" {
 /* Instruction cache flush. */
 /****************************/
 
-#if (!defined SLJIT_CACHE_FLUSH && defined __has_builtin)
+#if (!defined SLJIT_CACHE_FLUSH && defined __has_builtin && !defined SLJIT_CONFIG_PPC_32)
 #if __has_builtin(__builtin___clear_cache)
 
 #define SLJIT_CACHE_FLUSH(from, to) \
