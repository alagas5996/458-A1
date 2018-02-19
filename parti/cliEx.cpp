#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv){
        int sockfd, n; 
        char recvline[100];
        struct sockaddr_in servaddr;

	if(argc!=3){
		printf("Usage : gettime <IP address>\n");
		exit(1); 
	}

        /* Create a TCP socket */
	if((sockfd=socket(AF_INET,SOCK_STREAM, 0)) < 0){
		perror("Socket error\n"); exit(2);
	}
	    
        /* Specify server’s IP address and port */
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons((unsigned short) strtoul(argv[2], NULL, 0)); /* daytime server port */

        if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
		perror("INET_PTON Error\n"); exit(3);
        }

	/* Connect to the server */
	if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
		perror("Connection error\n");
		exit(4);
	}


        /* Read the date/time from socket */
        while((n = read(sockfd, recvline, 100)) > 0){
		recvline[n] = '\0';        /* null terminate */
		printf("%s", recvline); 
	}               
        
	if(n < 0){
		perror("Read error\n");
		exit(5);
	}

        close(sockfd);
} 

