#include "server.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void host_server(unsigned int port) {
	printf("Server listening on port: %d\n", port);
}
