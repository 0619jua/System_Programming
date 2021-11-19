#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
	char answer[20]="apple";
	char correct[20]="_____";
	char ch;
	int i;
	bool check;

	for(i=0; i<7; i++){
		printf("guess: %s\n", correct);
		printf("guess character: ");
		scanf("%c", &ch);
		getchar();
		check=false;
		if(check==false){
			for(int j = 0; answer[j] != '\0'; j++){
				if(answer[j]==ch){
					correct[j]=ch;
					check=true;
				}
			}
			if(check==true){
				i--;
			}
		}			

		if(strcmp(answer, correct) == 0){
			printf("answer is %s\n", answer);
			printf("WIN!\n");
			break;
		}
	}
	if(i==7){
		printf("LOSE!\n");
		printf("answer is %s\n", answer);
	}
	return 0;
}
