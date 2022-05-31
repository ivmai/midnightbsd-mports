--- client/mysql.cc.orig	2017-04-01 14:33:18 UTC
+++ client/mysql.cc
@@ -1903,11 +1903,11 @@ static void usage(int version)
 #endif
 
 #ifdef HAVE_READLINE
-  printf("%s  Ver %s Distrib %s, for %s (%s) using %s %s\n",
+  printf("%s  Ver %s Distrib %s Percona, for %s (%s) using %s %s\n",
 	 my_progname, VER, MYSQL_SERVER_VERSION, SYSTEM_TYPE, MACHINE_TYPE,
          readline, rl_library_version);
 #else
-  printf("%s  Ver %s Distrib %s, for %s (%s)\n", my_progname, VER,
+  printf("%s  Ver %s Distrib %s Percona, for %s (%s)\n", my_progname, VER,
 	MYSQL_SERVER_VERSION, SYSTEM_TYPE, MACHINE_TYPE);
 #endif
 
y@@ -2858,15 +2858,18 @@ static void initialize_readline (char *name)
 
   /* Tell the completer that we want a crack first. */
 #if defined(USE_NEW_XLINE_INTERFACE)
-  rl_attempted_completion_function= &new_mysql_completion;
-  rl_completion_entry_function= &no_completion;
-
+  rl_attempted_completion_function= (rl_completion_func_t*)&new_mysql_completion;
+  rl_completion_entry_function= (rl_compentry_func_t*)&no_completion;
+/*
   rl_add_defun("magic-space", &fake_magic_space, -1);
+*/
 #elif defined(USE_LIBEDIT_INTERFACE)
   setlocale(LC_ALL,""); /* so as libedit use isprint */
-  rl_attempted_completion_function= &new_mysql_completion;
-  rl_completion_entry_function= &no_completion;
+  rl_attempted_completion_function= (rl_completion_func_t*)&new_mysql_completion;
+  rl_completion_entry_function= (rl_compentry_func_t*)&no_completion;
+/*
   rl_add_defun("magic-space", &fake_magic_space, -1);
+*/
 #else
   rl_attempted_completion_function= (CPPFunction*)&new_mysql_completion;
   rl_completion_entry_function= &no_completion;
