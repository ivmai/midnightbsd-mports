--- main.c.old	2007-05-31 06:49:50.000000000 +0530
+++ main.c	2010-02-16 16:16:24.000000000 +0530
@@ -842,7 +842,9 @@
     mySignal(SIGPIPE, SigPipe);
 #endif
 
-    orig_GC_warn_proc = GC_set_warn_proc(wrap_GC_warn_proc);
+    orig_GC_warn_proc = GC_get_warn_proc();
+    GC_set_warn_proc(wrap_GC_warn_proc);
+
     err_msg = Strnew();
     if (load_argc == 0) {
 	/* no URL specified */
