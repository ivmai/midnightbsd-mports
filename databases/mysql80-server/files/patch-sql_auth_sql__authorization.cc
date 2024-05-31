--- sql/auth/sql_authorization.cc.orig	2023-03-16 17:22:37 UTC
+++ sql/auth/sql_authorization.cc
@@ -7430,6 +7430,10 @@ bool operator==(const Role_id &a, const std::string &b
   return tmp == b;
 }
 
+bool operator==(const Role_id &a, const LEX_CSTRING &b) {
+  return a == to_string(b);
+}
+
 bool operator==(const std::pair<Role_id, bool> &a, const std::string &b) {
   return a.first == b;
 }
