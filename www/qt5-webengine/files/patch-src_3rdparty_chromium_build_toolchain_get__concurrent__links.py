--- src/3rdparty/chromium/build/toolchain/get_concurrent_links.py.orig	2021-12-15 16:12:54 UTC
+++ src/3rdparty/chromium/build/toolchain/get_concurrent_links.py
@@ -53,6 +53,14 @@ def _GetTotalMemoryInBytes():
       return int(subprocess.check_output(['sysctl', '-n', 'hw.memsize']))
     except Exception:
       return 0
+  elif sys.platform.startswith('freebsd'):
+    try:
+      avail_bytes = int(subprocess.check_output(['sysctl', '-n', 'hw.physmem']))
+      # With -fuse-lld it doesn't take a lot of ram, feel free to change that
+      # 1 * ... to needed amount
+      return max(1, avail_bytes / (1 * (2 ** 30)))  # total / 4GB
+    except Exception:
+      return 1
   # TODO(scottmg): Implement this for other platforms.
   return 0
 
