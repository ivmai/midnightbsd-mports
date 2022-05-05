Obtained from:	https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=508133#15

--- layer12.c.orig	2004-02-05 09:02:39 UTC
+++ layer12.c
@@ -134,6 +134,12 @@ int mad_layer_I(struct mad_stream *strea
   for (sb = 0; sb < bound; ++sb) {
     for (ch = 0; ch < nch; ++ch) {
       nb = mad_bit_read(&stream->ptr, 4);
+	if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+	{
+		stream->error = MAD_ERROR_LOSTSYNC;
+		stream->sync = 0;
+		return -1;
+	}
 
       if (nb == 15) {
 	stream->error = MAD_ERROR_BADBITALLOC;
@@ -146,6 +152,12 @@ int mad_layer_I(struct mad_stream *strea
 
   for (sb = bound; sb < 32; ++sb) {
     nb = mad_bit_read(&stream->ptr, 4);
+	if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+	{
+		stream->error = MAD_ERROR_LOSTSYNC;
+		stream->sync = 0;
+		return -1;
+	}
 
     if (nb == 15) {
       stream->error = MAD_ERROR_BADBITALLOC;
@@ -162,6 +174,12 @@ int mad_layer_I(struct mad_stream *strea
     for (ch = 0; ch < nch; ++ch) {
       if (allocation[ch][sb]) {
 	scalefactor[ch][sb] = mad_bit_read(&stream->ptr, 6);
+	if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+	{
+		stream->error = MAD_ERROR_LOSTSYNC;
+		stream->sync = 0;
+		return -1;
+	}
 
 # if defined(OPT_STRICT)
 	/*
@@ -187,6 +205,12 @@ int mad_layer_I(struct mad_stream *strea
 	frame->sbsample[ch][s][sb] = nb ?
 	  mad_f_mul(I_sample(&stream->ptr, nb),
 		    sf_table[scalefactor[ch][sb]]) : 0;
+	if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+	{
+		stream->error = MAD_ERROR_LOSTSYNC;
+		stream->sync = 0;
+		return -1;
+	}
       }
     }
 
@@ -195,6 +219,12 @@ int mad_layer_I(struct mad_stream *strea
 	mad_fixed_t sample;
 
 	sample = I_sample(&stream->ptr, nb);
+	if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+	{
+		stream->error = MAD_ERROR_LOSTSYNC;
+		stream->sync = 0;
+		return -1;
+	}
 
 	for (ch = 0; ch < nch; ++ch) {
 	  frame->sbsample[ch][s][sb] =
@@ -403,7 +433,15 @@ int mad_layer_II(struct mad_stream *stre
     nbal = bitalloc_table[offsets[sb]].nbal;
 
     for (ch = 0; ch < nch; ++ch)
+    {
       allocation[ch][sb] = mad_bit_read(&stream->ptr, nbal);
+	if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+	{
+		stream->error = MAD_ERROR_LOSTSYNC;
+		stream->sync = 0;
+		return -1;
+	}
+    }
   }
 
   for (sb = bound; sb < sblimit; ++sb) {
@@ -411,6 +449,13 @@ int mad_layer_II(struct mad_stream *stre
 
     allocation[0][sb] =
     allocation[1][sb] = mad_bit_read(&stream->ptr, nbal);
+
+	if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+	{
+		stream->error = MAD_ERROR_LOSTSYNC;
+		stream->sync = 0;
+		return -1;
+	}
   }
 
   /* decode scalefactor selection info */
@@ -419,6 +464,12 @@ int mad_layer_II(struct mad_stream *stre
     for (ch = 0; ch < nch; ++ch) {
       if (allocation[ch][sb])
 	scfsi[ch][sb] = mad_bit_read(&stream->ptr, 2);
+	if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+	{
+		stream->error = MAD_ERROR_LOSTSYNC;
+		stream->sync = 0;
+		return -1;
+	}
     }
   }
 
@@ -442,6 +493,12 @@ int mad_layer_II(struct mad_stream *stre
     for (ch = 0; ch < nch; ++ch) {
       if (allocation[ch][sb]) {
 	scalefactor[ch][sb][0] = mad_bit_read(&stream->ptr, 6);
+	if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+	{
+		stream->error = MAD_ERROR_LOSTSYNC;
+		stream->sync = 0;
+		return -1;
+	}
 
 	switch (scfsi[ch][sb]) {
 	case 2:
@@ -452,11 +509,23 @@ int mad_layer_II(struct mad_stream *stre
 
 	case 0:
 	  scalefactor[ch][sb][1] = mad_bit_read(&stream->ptr, 6);
+		if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+		{
+			stream->error = MAD_ERROR_LOSTSYNC;
+			stream->sync = 0;
+			return -1;
+		}
 	  /* fall through */
 
 	case 1:
 	case 3:
 	  scalefactor[ch][sb][2] = mad_bit_read(&stream->ptr, 6);
+		if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+		{
+			stream->error = MAD_ERROR_LOSTSYNC;
+			stream->sync = 0;
+			return -1;
+		}
 	}
 
 	if (scfsi[ch][sb] & 1)
@@ -488,6 +557,12 @@ int mad_layer_II(struct mad_stream *stre
 	  index = offset_table[bitalloc_table[offsets[sb]].offset][index - 1];
 
 	  II_samples(&stream->ptr, &qc_table[index], samples);
+		if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+		{
+			stream->error = MAD_ERROR_LOSTSYNC;
+			stream->sync = 0;
+			return -1;
+		}
 
 	  for (s = 0; s < 3; ++s) {
 	    frame->sbsample[ch][3 * gr + s][sb] =
@@ -506,6 +581,12 @@ int mad_layer_II(struct mad_stream *stre
 	index = offset_table[bitalloc_table[offsets[sb]].offset][index - 1];
 
 	II_samples(&stream->ptr, &qc_table[index], samples);
+	if (mad_bit_nextbyte(&stream->ptr) > stream->next_frame)
+	{
+		stream->error = MAD_ERROR_LOSTSYNC;
+		stream->sync = 0;
+		return -1;
+	}
 
 	for (ch = 0; ch < nch; ++ch) {
 	  for (s = 0; s < 3; ++s) {
