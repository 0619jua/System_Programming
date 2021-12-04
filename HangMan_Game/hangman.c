#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int main(){
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

        printf("==========Hangman Game==========\n");
        printf("If you know answer, then press *\n");
        printf("You have only 3 chances to try.\n");
	
	        for(i=0; i<7; i++){
                printf("guess: %s\n", correct);
                printf("guess character: ");
                scanf("%c", &ch);
                getchar();
                if(ch==42){
                        printf("answer is ");
                        scanf("%s", answer);

                        if(strcmp(answer, words[random])==0){
                                        printf("WIN!\n");
                                        break;
                        }
                        i--;
                        continue;
                }
                check=false;
                if(check==false){
                        for(int j = 0; words[random][j] != '\0'; j++){
                                if(words[random][j]==ch){
                                        correct[j]=ch;
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
                        break;
                }
        }
        if(i==7){
                printf("LOSE!\n");
                printf("answer is %s\n", words[random]);
        }

        return 0;
}
