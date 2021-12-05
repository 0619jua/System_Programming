/*s2*/
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define SOCKET_NAME "hs2"
#define PORT 9051
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


   //hangman
   char words[20][6]={"apple","koala", "smart", "phone", "check",
                     "mouse", "chair", "basic", "catch", "brain",
                     "paper", "flush", "fresh", "dress", "clock",
                     "crown","train", "skill", "trust", "click"};
         
   char correct[20]="_____";
   int random=0;
   srand(time(NULL));
   random=rand()%20;
   char ch;
   int i;
   bool check;
   char answer[10];





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
                  printf("[C2] : %s\n", buf2);
//                  send(s1, buf2, strlen(buf2)+1, 0);
               }
                  
               if(send(s1, buf2, strlen(buf2)+1, 0) == -1){
                       perror("send");
                         exit(1);
                 }
   
               memset(buf, 0x00, sizeof(buf));
               if(recv(s1, buf, sizeof(buf), 0) > 0){
                  printf("[C1] : %s\n", buf);
               }
   
               if(strncmp(buf2, QUITMSG, strlen(QUITMSG)) == 0){
                  exit(1);
               }
            }   
         
            break;
         case 2 : //game
            
            printf("==========Hangman Game==========\n");
            if(send(s4, "==========Hangman Game==========\n", 256, 0) == -1){
               perror("send");
               exit(1);
            }

            printf("If you know answer, then press *\n");
            printf("You have only 3 chances to try.\n");
   
            for(i=0; i<7; i++){
               printf("guess: %s\n", correct);

               if(recv(s4, buf2, sizeof(buf2), 0) > 0 ){
                  printf("character : %s\n", buf2);
               }


               if(strcmp(buf2, "*")==0){
                  printf("answer is ");
                  memset(buf2, 0x00, sizeof(buf2));
                  if(recv(s4, buf2, sizeof(buf2), 0) > 0 ){
                     printf("%s\n", buf2);
                  }


                  if(strcmp(buf2, words[random])==0){
                     printf("WIN!\n");
                     break;
                  }
                  i--;
                  //continue;
               }

               check=false;
               if(check==false){
                  for(int j = 0; words[random][j] != '\0'; j++){
                     if(words[random][j]==buf2[0]){
                        correct[j]=buf2[0];
                        check=true;
                     }
                  }

                  if(check==true){
                     i--;
                  }
               }

               if(strcmp(words[random], correct) == 0){
                  printf("answer is %s\n", words[random]);
                  printf("WIN!\n");
                  exit(1);
//                  break;
               }
            }

            if(i==7){
               printf("LOSE!\n");
               printf("answer is %s\n", words[random]);
               exit(1);
            }


            break;
         
   
      }//switch

   }//while


   close(s1);
   close(s3);
   close(s4);
   return 0;
}
