--- src/plugins/fts-lucene/SnowballFilter.h.orig	2020-08-12 12:20:41 UTC
+++ src/plugins/fts-lucene/SnowballFilter.h
@@ -8,7 +8,7 @@
 #define _lucene_analysis_snowball_filter_
 
 #include "CLucene/analysis/AnalysisHeader.h"
-#include "libstemmer.h"
+#include "CLucene/snowball/libstemmer.h"
 
 CL_NS_DEF2(analysis,snowball)
 
