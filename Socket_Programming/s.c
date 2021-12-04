/*s*/
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORT1 9001
#define PORT2 9051
#define QUITMSG "exit"
#define INFO "<Choose menu>\n1. ChatRoom\n2. HangMan Game\n3. Game Score"

int main(void){
	char buf[256];
	struct sockaddr_in server, client;
	int s1, s2, clientlen = sizeof(client);

	char buf2[256];
	struct sockaddr_in server2, client2;
	int s3, s4, clientlen2 = sizeof(client2);

	if((s1 = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	if((s3 = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(1);
	}

	memset((char *)&server, '\0', sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT1);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	memset((char *)&server2, '\0', sizeof(server2));
	server2.sin_family = AF_INET;
	server2.sin_port = htons(PORT2);
	server2.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(s1, (struct sockaddr *)&server, sizeof(server))) {
		perror("bind");
		exit(1);
	}
	
	if(bind(s3, (struct sockaddr *)&server2, sizeof(server2))) {
		perror("bind");
		exit(1);
	}
	
	if(listen(s1, 5)){
		perror("listen");
		exit(1);
	}

	if(listen(s3, 5)){
		perror("listen");
		exit(1);
	}


		
	while(1){

		if((s2 = accept(s1, (struct sockaddr *)&client, &clientlen)) == -1){
			perror("accept");
			exit(1);
		}


		if((s4 = accept(s3, (struct sockaddr *)&client2, &clientlen2)) == -1){
			perror("accept");
			exit(1);
		}



//			strcpy(buf, "Welcome to Server");

//		if(send(s2, buf, strlen(buf)+1, 0) == -1){
//			perror("send");
//			exit(1);
//		}

		switch(fork()){
			case 0:
					close(s1);
					close(s3);
				while(1){
					memset(buf, 0x00, sizeof(buf));

					if(recv(s2, buf, 256, 0) >0){
						send(s4, buf, 256, 0); 
					}
					
					sleep(1);

					memset(buf2, 0x00, sizeof(buf2));
					if(recv(s4, buf2, 256, 0) >0){
						send(s2, buf2, 256, 0); 
					}

					sleep(1);
					
				}


				break;
		}
		close(s2);
		close(s4);
	}	


	return 0;

}

