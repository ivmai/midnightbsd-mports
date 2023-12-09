--- src/p_spec.cpp.orig	2021-03-05 01:22:24 UTC
+++ src/p_spec.cpp
@@ -1269,7 +1269,7 @@ void P_InitSectorSpecial(sector_t *sector, int special
 		if (sector->special >= Scroll_North_Slow &&
 			sector->special <= Scroll_SouthWest_Fast)
 		{ // Hexen scroll special
-			static const char hexenScrollies[24][2] =
+			static const signed char hexenScrollies[24][2] =
 			{
 				{  0,  1 }, {  0,  2 }, {  0,  4 },
 				{ -1,  0 }, { -2,  0 }, { -4,  0 },
@@ -1826,7 +1826,7 @@ static void P_SpawnScrollers(void)
 
 		switch (special)
 		{
-			register int s;
+			int s;
 
 		case Scroll_Ceiling:
 		{
@@ -2357,7 +2357,7 @@ static void P_SpawnPushers ()
 {
 	int i;
 	line_t *l = lines;
-	register int s;
+	int s;
 
 	for (i = 0; i < numlines; i++, l++)
 	{
