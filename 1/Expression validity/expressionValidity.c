#include <stdio.h>
#include <string.h>
//Edip Kemal Sardoðan
//240201026

int main(){
	char expression[10];
	int i, open, close;
	
	open=0;
	close=0;
	i=0;
	printf("Enter an expression : \n");
	scanf("%s",expression);

	while(expression[i]!='\0'){ //checks end of the string
		if(expression[i]=='('){
			open++;
		}else if(expression[i]==')'){
			close++;
		}
		if(close>open){ //   if there is a ')' before a '('
			printf("Invalid Expression!");
			return 0;
		}
		i++;
	}
	if(open!=close){
		printf("Invalid Expression!");
	}else{
		printf("Valid Expression!");
	}
	return 0;
}
