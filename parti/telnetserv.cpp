#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

int getCommand(char* command);

int main(int argc, char **argv){
	int listenfd, connfd;
	socklen_t clilen;
	struct sockaddr_in servaddr, cliaddr;
	char buff[100];

	if(argc != 2){
		perror("Usage: ./serv <port number>\n");
		exit(1);
	}

	/* Create a TCP socket */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	//Initialize server's address automatically and port from command arguments/
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	//Bind server’s address and port to the socket
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));       
	//Convert socket to a listening socket – max 100 pending clients
	listen(listenfd, 100);

	bool serverLive = true;

	//Wait for client connections and accept them
	while(serverLive){
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

		//Write to socket
		snprintf(buff, sizeof(buff), "telnet >");
		ssize_t writeRet = write(connfd, buff, strlen(buff));
		if(writeRet < 0){
			perror("Write error\n");
		}

		int n = read(connfd, buff, 100);
		buff[n] = '\0';//Null terminate
		int command = getCommand(buff);

		if(n < 0){
			perror("Read error\n");
		}

		printf("%d\n", command);

		switch(command){
			case 1:
				//ls();
				break;
			case 2:
				//mkdir();
				break;
			case 3:
				//rmdir();
				break;
			case 4:
				//cd();
				break;
			case 5:
				//pwd();
				break;
			case 6:
				//exit();
				break;
			case -1:
				snprintf(buff, sizeof(buff), "Error: Command not accepted. Please try again.\ntelnet >");
				ssize_t writeRet = write(connfd, buff, strlen(buff));
				if(writeRet < 0){
					perror("Write error\n");
				}
		}

		//Close the connection
		close(connfd);
	}
}

int getCommand(char* command){
	if(!strcmp(command, "pwd")){
		return 1;
	}
	else if(!strcmp(command, "mkdir")){
		return 2;
	}
	else if(!strcmp(command, "rmdir")){
		return 3;
	}
	else if(!strcmp(command, "cd")){
		return 4;
	}
	else if(!strcmp(command, "pwd")){
		return 5;
	}
	else if(!strcmp(command, "exit")){
		return 6;
	}
	else{
		return -1;
	}
}

