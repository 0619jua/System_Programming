/*server1*/
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORT 8062
#define QUITMSG "exit"
#define INFO "<Choose menu>\n1. ChatRoom\n2. HangMan Game\n3. Game Score"

int main(void){
	char buf[256];
	struct sockaddr_in server, client;
	int s1, s2, clientlen = sizeof(client);

	if((s1 = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	memset((char *)&server, '\0', sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(s1, (struct sockaddr *)&server, sizeof(server))) {
		perror("bind");
		exit(1);
	}
	
	if(listen(s1, 5)){
		perror("listen");
		exit(1);
	}

	
		
	while(1){

		if((s2 = accept(s1, (struct sockaddr *)&client, &clientlen)) == -1){
			perror("accept");
			exit(1);
		}
		
		//send info(menu) 
		if(send(s2, INFO, strlen(INFO) +1, 0)==-1) {
			perror("send");
			exit(1);
		}
		
		//receive menu number 
		memset(buf, 0x00, sizeof(buf));
		if(recv(s2, buf, sizeof(buf), 0) >0 ) {
			printf("[RECV] : %s\n");	
		}


		//menu
		switch(atoi(buf)){
			case 1 :	//chat room
				strcpy(buf, "Welcome to Chat Room");
				if(send(s2, buf, strlen(buf)+1, 0) == -1){
					perror("send");
					exit(1);
				}

				while(recv(s2, buf, 256, 0) > 0){
					printf("[RECV] : %s\n", buf);
					send(s2, buf, 256, 0); 
					memset(buf, 0x00, sizeof(buf));
					
					if(strncmp(buf, QUITMSG, strlen(QUITMSG)) == 0) {
						printf("[Info] Client quit!\n");
						break;
					}
					memset(buf, 0x00, sizeof(buf));
				}

				break;


		}//switch
	}//while

	close(s1);
	close(s2);
	return 0;

}
