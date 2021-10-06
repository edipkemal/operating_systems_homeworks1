#include<stdio.h>
#include<stdlib.h>
#define SIZE 5
//Edip Kemal Sardoðan 240201026

int getLen(const char* str);

int main(){
	int i,j, userSize, srcSize;
	char *pStr, *pSrch, userStr[100], search[3]; 
	
	pStr=(char*)malloc(SIZE*sizeof(char));
	
	printf("Please enter a sentence: \n");
	scanf("%[^\n]s",&userStr);
	
	userSize=getLen(userStr);
	
	if(userSize>SIZE){ //twice the length
		userSize*=2;
 	}

	pStr = realloc(pStr,userSize); //reallocation
	pStr=&userStr[0];
	
	do{
		printf("Please enter a search phrase: (up to 3 characters)\n");
		scanf("%s",&search);	
	}while(getLen(search)>3);
	
	pSrch=(char*)malloc(3*sizeof(char));
	pSrch=&search[0]; //pointer of search key
	
	for(i=0; i<userSize; i++){
		if(*(pStr+i)==*pSrch){ // found search key's first letter
			for(j=0; j<getLen(search); j++){
				if(*(pStr+j+i)!=*(pSrch+j)){ //checks for other letters of key
					continue; //skip if the next letters unequal
				}
				printf("'%s' exists in the given string.",search); //substring found
				exit(1);	
			}
		}
	}
	printf("'%s'does not exist in the given string.",search);
	
	free(pStr);
	free(pSrch);
	return 0;
}

int getLen(const char* str){
	int i=0;
	while(str[i] != '\0'){
		i++;
	}
	return i;
}
