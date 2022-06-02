--- third_party/rust/cc/src/lib.rs.orig	2020-10-14 09:34:53 UTC
+++ third_party/rust/cc/src/lib.rs
@@ -2344,28 +2344,7 @@ impl Tool {
     }
 
     fn with_features(path: PathBuf, clang_driver: Option<&str>, cuda: bool) -> Self {
-        // Try to detect family of the tool from its name, falling back to Gnu.
-        let family = if let Some(fname) = path.file_name().and_then(|p| p.to_str()) {
-            if fname.contains("clang-cl") {
-                ToolFamily::Msvc { clang_cl: true }
-            } else if fname.contains("cl")
-                && !fname.contains("cloudabi")
-                && !fname.contains("uclibc")
-                && !fname.contains("clang")
-            {
-                ToolFamily::Msvc { clang_cl: false }
-            } else if fname.contains("clang") {
-                match clang_driver {
-                    Some("cl") => ToolFamily::Msvc { clang_cl: true },
-                    _ => ToolFamily::Clang,
-                }
-            } else {
-                ToolFamily::Gnu
-            }
-        } else {
-            ToolFamily::Gnu
-        };
-
+        let family = ToolFamily::Gnu;
         Tool {
             path: path,
             cc_wrapper_path: None,
