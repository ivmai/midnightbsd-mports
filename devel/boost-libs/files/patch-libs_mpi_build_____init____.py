--- libs/mpi/build/__init__.py.orig	2022-12-08 01:02:45 UTC
+++ libs/mpi/build/__init__.py
@@ -1,10 +1,12 @@
+from __future__ import absolute_import
+
 import sys
 if sys.platform == 'linux2':
     import DLFCN as dl
     flags = sys.getdlopenflags()
     sys.setdlopenflags(dl.RTLD_NOW|dl.RTLD_GLOBAL)
-    import mpi
+    from . import mpi
     sys.setdlopenflags(flags)
 else:
-    import mpi
+    from . import mpi
 
