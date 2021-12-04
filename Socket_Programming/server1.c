/*s1*/
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SOCKET_NAME "hs1"
#define PORT 9001
#define QUITMSG "exit"
#define INFO "<Choose menu>\n1. ChatRoom\n2. HangMan Game\n3. Game Score"


int main(void){
	//INET
	char buf[256];
	struct sockaddr_in server;
	int s1;

	//UNIX
	char buf2[256];
	struct sockaddr_un server2, client2;
	int s3, s4, len, clen;


	//INET
	if((s1 = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	//UNIX
	if((s3 = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	//INET
	memset((char *)&server, '\0', sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//UNIX
	memset((char *)&server2, 0, sizeof(struct sockaddr_un));
	server2.sun_family = AF_UNIX;
	strcpy(server2.sun_path, SOCKET_NAME);
	len = sizeof(server2.sun_family) + strlen(server2.sun_path);


	//UNIX
	if(bind(s3, (struct sockaddr *)&server2, len)){
		perror("bind");
		exit(1);
	}

	if(listen(s3, 5) <0){
		perror("listen");
		exit(1);
	}


	while(1){
	
		if((s4 = accept(s3, (struct sockaddr *)&client2, &clen)) == -1){
			perror("accept");
			exit(1);
		}
	
		printf("New Client!\n");
	
		//INET
		if(connect(s1, (struct sockaddr *)&server, sizeof(server))){
			perror("connect");
			exit(1);
		}


		memset(buf, 0x00, sizeof(buf));
		if(send(s4, INFO, strlen(INFO)+1, 0) == -1 ){
			perror("send");
			exit(1);
		}	

		memset(buf2, 0x00, sizeof(buf2));
		if(recv(s4, buf2, sizeof(buf2), 0) == -1){
			perror("recv");
			exit(1);
		}

		switch(atoi(buf2)){
		case 1 : //chat room
				printf("\nWelcome to Chat Room!!\n");
				memset(buf2, 0x00, sizeof(buf2));
				if(send(s4, "--Welcome to Chat Room--", 256, 0) == -1){
					perror("send");
					exit(1);
				}
			
				while(1){
	
					memset(buf2, 0x00, sizeof(buf2));
					if(recv(s4, buf2, sizeof(buf2), 0)  > 0){
						printf("[C1] : %s\n", buf2);
//						send(s1, buf2, strlen(buf2)+1, 0);
					}
						
					if(send(s1, buf2, strlen(buf2)+1, 0) == -1){
  	                  perror("send");
  	  	               exit(1);
  	   	      }
	
					memset(buf, 0x00, sizeof(buf));
					if(recv(s1, buf, sizeof(buf), 0) > 0){
						printf("[C2] : %s\n", buf);
					}
	
					if(strncmp(buf2, QUITMSG, strlen(QUITMSG)) == 0){
						exit(1);
					}
				}	
			
				break;
			case 2 : //game
				
				break;
			
	
		}//switch

	}//while


	close(s1);
	close(s3);
	close(s4);
	return 0;
}
