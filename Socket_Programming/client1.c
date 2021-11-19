/*client1*/
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORT 8062
#define QUITMSG "exit"

int main(void){
	char buf[256];
	struct sockaddr_in server;
	int sd;

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	memset((char *)&server, '\0', sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(sd, (struct sockaddr *)&server, sizeof(server))){
		perror("connect");
		exit(1);
	}
//	char result = '';
	while(1){
		
		memset(buf, 0x00, sizeof(buf));
		if(recv(sd, buf, sizeof(buf), 0) >0){
			printf("[RECV] : %s\n", buf);
		}
 		
		memset(buf, 0x00, sizeof(buf));
		printf("[SEND_C1] : ");
		gets(buf);
		strcat("[SEND_C1]", buf);

		if(send(sd, buf, strlen(buf) +1, 0) == -1){
			perror("send");
			exit(1);
		}

		if(strncmp(buf, QUITMSG, strlen(QUITMSG)) == 0){
			exit(1);
		}
			
	}//while

	close(sd);
	return 0;
}
