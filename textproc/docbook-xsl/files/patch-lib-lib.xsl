Description: use EXSLT "replace" function when available
 A recursive implementation  of string.subst is problematic,
 long strings with many matches will cause stack overflows.
Author: Peter De Wachter <pdewacht@gmail.com>
Bug-Debian: https://bugs.debian.org/750593

--- lib/lib.xsl.orig	2013-09-04 18:09:43 UTC
+++ lib/lib.xsl
@@ -10,7 +10,10 @@
      This module implements DTD-independent functions
 
      ******************************************************************** -->
-<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
+<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
+                xmlns:str="http://exslt.org/strings"
+                exclude-result-prefixes="str"
+                version="1.0">
 
 <xsl:template name="dot.count">
   <!-- Returns the number of "." characters in a string -->
@@ -56,6 +59,9 @@
   <xsl:param name="replacement"/>
 
   <xsl:choose>
+    <xsl:when test="function-available('str:replace')">
+      <xsl:value-of select="str:replace($string, string($target), string($replacement))"/>
+    </xsl:when>
     <xsl:when test="contains($string, $target)">
       <xsl:variable name="rest">
         <xsl:call-template name="string.subst">
