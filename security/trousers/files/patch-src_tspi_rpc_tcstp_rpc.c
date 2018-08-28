--- src/tspi/rpc/tcstp/rpc.c.orig	2016-06-20 15:21:26 UTC
+++ src/tspi/rpc/tcstp/rpc.c
@@ -304,7 +304,7 @@ recv_from_socket(int sock, void *buffer,
 		errno = 0;
 		if ((recv_size = recv(sock, buffer+recv_total, size-recv_total, 0)) <= 0) {
 			if (recv_size < 0) {
-				if (errno == EINTR)
+				if (errno == EINTR || errno == EAGAIN)
 					continue;
 				LogError("Socket receive connection error: %s.", strerror(errno));
 			} else {
