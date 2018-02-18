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
	int listenfd, connfd;
	socklen_t clilen;
	struct sockaddr_in servaddr, cliaddr;
	char buff[100];
	time_t ticks;

	/* Create a TCP socket */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	/* Initialize server's address and well-known port */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(10000);   /* daytime server */

	/* Bind server’s address and port to the socket */
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));       
	/* Convert socket to a listening socket – max 100 pending clients*/
	listen(listenfd, 100); 
   

	
	/* Wait for client connections and accept them */
	for( ; ; ){
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

		//printf("hello1\n");

		/* Retrieve system time */
		ticks = time(NULL);
      
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		printf("%s\r\n", ctime(&ticks));
		//printf("hello\n");

		/* Write to socket */
		ssize_t writeRet = write(connfd, buff, strlen(buff));
		
		if(writeRet < 0){
			perror("Write error\n");
		}

		//fprintf(stdout, "hello");

		/* Close the connection */
		close(connfd);
	}
}

