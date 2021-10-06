#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Edip Kemal Sardoðan
//240201026

int randomNumberGenerator(int min, int max){ //generates random number
	int a;
	a = rand() % max + min;
	return a;
}

int main(){
	srand ( time(NULL) );
	int rn1, rn2, op, ans, correct, wrong, total,rate;  //random numbers, operator, answers and results
	char userAns[3];
	correct=0;
	wrong=0;
	
	while(1){
		rn1=randomNumberGenerator(1,20); //random number 1
		rn2=randomNumberGenerator(1,20); //random number 2
		
		op=randomNumberGenerator(1,3); // 1=+  2=-  3=*
		
		if (op==1){ //addition
			ans=rn1+rn2;
			printf("%d + %d = ?\n",rn1,rn2);
		}else if (op==2){ //subtraction
			if (rn1<rn2){
				ans=rn2-rn1; // to avoid negative result
				printf("%d - %d = ?\n",rn2,rn1);
			}else{
				ans=rn1-rn2;
				printf("%d - %d = ?\n",rn1,rn2);
			}
		}else{//muktiplication
			ans=rn1*rn2;
			printf("%d * %d = ?\n",rn1,rn2);
		}
		scanf("%s", &userAns);
		
		if(!strcmp(userAns,"x")){  //show results
			total=wrong+correct;
			rate=((double)correct/total*100);
			printf("%d questions : %d correct, %d wrong answers. \nSuccess rate is %d%c .\n", total, correct, wrong, rate, 37);
			return 0;
		}
		int userAnswer;
		userAnswer = atoi(userAns); //type casting: char to int
		
		if(ans==userAnswer){  	//Correct
			printf("Correct!\n");
			correct++;
		}else{				//Wrong
			printf("Wrong! Correct answer is %d.\n",ans);
			wrong++;
		}
	}
	return 0;
}

