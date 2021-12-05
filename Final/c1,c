/*c1*/
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>

#define SOCKET_NAME "hs1"
#define QUITMSG "exit"

int main(void){
	char buf[256];
	struct sockaddr_un server, client;
	int s1, len;

	if((s1 = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}
	
	memset((char *)&server, 0, sizeof(struct sockaddr_un));
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, SOCKET_NAME);
	len = sizeof(server.sun_family) + strlen(server.sun_path);

	if(connect(s1, (struct sockaddr *)&server, len) <0){
		perror("connect");
		exit(1);
	}


	//menu recv
	if(recv(s1, buf, sizeof(buf), 0) > 0){
		printf("%s\n", buf);
	}

	printf("Choose the menu : ");
	gets(buf);
	if(send(s1, buf, strlen(buf)+1, 0) == -1){
		perror("send");
		exit(1);
	}	

	memset(buf, 0x00, sizeof(buf));
	if(recv(s1, buf, sizeof(buf)+1, 0) > 0 ){
		printf("%s\n", buf);
	}


	while(1){
		memset(buf, 0x00, sizeof(buf));

		printf("[SEND_C1] : ");
		gets(buf);
		strcat(buf, " [SEND_C1] ");

		if(send(s1, buf, strlen(buf) +1, 0) == -1){
			perror("send");
			exit(1);
		}
		
		if(strncmp(buf, QUITMSG, strlen(QUITMSG)) == 0){
			exit(1);
		}	

	}

	close(s1);
	return 0;
	
}
