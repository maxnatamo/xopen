#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>

#include "config.h"
   
int main(int argc, char const *argv[]) 
{ 
	if(argc <= 1) {
		printf("error: No commands has been provided.\n");
		return 1;
	}

	const char *cmd = argv[1];
	struct sockaddr_in serv_addr; 
        int sock = 0;
	
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("error: Socket couldn't be created.\n"); 
		return -1; 
	} 
	
	memset( &serv_addr, '0', sizeof(serv_addr) );
	
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	   
	if( inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{ 
		printf("error: Invalid address or address not supported.\n"); 
		return -1; 
	} 
	
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("error: Connection failed.\n"); 
		return -1; 
	} 
	
	send( sock, cmd, strlen(cmd), 0 );
	
	return 0; 
} 
