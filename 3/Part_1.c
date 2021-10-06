#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ARRAYSIZE 1000
#define RANGE 100 //range of random numbers

typedef struct { // to take two results from operations i.e. mean and standard deviation
	float result_1;
	float result_2; 
}operation;

operation square_sum(float array[]);
operation minValue(float array[]);
operation maxValue(float array[]);
operation most_frequent(float array[]);
operation standard_deviation(float array[]);
void write_to_file(float array[], char file_name[]);


int main(){
	char file_path[]="random_numbers.txt";
	int i;
	operation opr1, opr2, opr3, opr4, opr5;
	float random_number_array[ARRAYSIZE]; //random numbers' array
	srand(time(NULL));
	for (i=0; i<ARRAYSIZE; i++){
		random_number_array[i]=((float)rand()/(float)(RAND_MAX)*RANGE);  //random float number between 0 and RANGE
		//printf("%f\n",random_number_array[i]);
	}
	
	
	clock_t start = clock();
	printf("Operations have started and are in progress !\n\n")	;
	printf("--- Results ---\n\n");
	
	opr1=square_sum(random_number_array);
	opr2=minValue(random_number_array);
	opr3=maxValue(random_number_array);
	opr4=most_frequent(random_number_array);
	opr5=standard_deviation(random_number_array);

		
	printf("Operation 1:\nSquare of the sum of values of the list: %f \n\n",opr1.result_1);
	printf("Operation 2:\nMinimum Value of the List: %f \nThis is the %dth element of the list.\n\n",opr2.result_1,(int)opr2.result_2);
	printf("Operation 3:\nMaximum Value of the List: %f \nThis is the %dth element of the list.\n\n",opr3.result_1,(int)opr3.result_2);
	printf("Operation 4:\nMost Frequently Occurred Value of the List: %f \nThe Occurrence Count of the Value (%f): %d times\n\n",opr4.result_1,opr4.result_1,(int)opr4.result_2);
	printf("Operation 5:\nMean of the List Elements: %.2f \nStandard Deviation of the List Elements: %.2f\n\n",opr5.result_1,opr5.result_2);
	clock_t stop = clock();
	
	double passed_time= (double)(stop-start)/ CLOCKS_PER_SEC;
	printf("Total execution time: : %f ms\n", passed_time*1000); //multiplied by 1000 since convert from s to ms
	write_to_file(random_number_array,file_path);
	
	FILE* file;
	file=fopen("Comparison.txt","w");
	fprintf(file,"Runtime of the Single Thread Program for the Given List:%fms\n",passed_time*1000);
	fclose(file);
	return 0;
}

operation square_sum(float array[]){ //operation 1
	operation opr;
	float summ, result;
	int i;
	for(i=0; i<ARRAYSIZE; i++){
		summ+=array[i];
	}
	result=summ*summ;
	opr.result_1=result;
	return opr;
}

operation minValue(float array[]){ // operation 2
	int i, index;
	float min;
	operation opr;
	min=array[0];
	for(i=1; i<ARRAYSIZE;i++){
		if(array[i]<min){
			min=array[i];
			index=i;
		}
	}
	opr.result_1=min;
	opr.result_2=index;
	return opr;
}
operation maxValue(float array[]){ //operation 3 
	int i, index;
	float max;
	operation opr;
	max=array[0];
	for(i=1; i<ARRAYSIZE;i++){
		if(array[i]>max){
			max=array[i];
			index=i;
		}
	}
	opr.result_1=max;
	opr.result_2=index;
	return opr;
}

operation most_frequent(float array[]){ //operation 4
	int i,j,occurance,temp_occur;
	float number,temp_number;
	operation opr;
	occurance=0;
	for(i=0;i<ARRAYSIZE;i++){
		temp_occur=0;
		for(j=0;j<ARRAYSIZE;j++){
			if(array[i]==array[j]){
				temp_occur++;
				temp_number=array[i];
			}
		}
		if(temp_occur>occurance){
			occurance=temp_occur;
			number=temp_number;
		}
	}
	opr.result_1=number;
	opr.result_2=(float)occurance;
	
	
	return opr;
}

operation standard_deviation(float array[]){ //operation 5
	operation opr;
	float summ, mean, standard_deviation;
	int i;
	for(i=0;i<ARRAYSIZE;i++){
		summ+=array[i];
	}
	mean=summ/ARRAYSIZE;
	summ=0;
	for(i=0;i<ARRAYSIZE;i++){
		summ+=(array[i]-mean)*(array[i]-mean);
	}
	summ=summ/(ARRAYSIZE-1);
	standard_deviation=sqrt(summ);
	opr.result_1=mean;
	opr.result_2=standard_deviation;
	return opr;
}

void write_to_file(float array[], char file_name[]){
	int i;
	float number;
	FILE *file;
	file = fopen(file_name, "w");
	for(i=0;i<ARRAYSIZE;i++){
		number = array[i];
		fprintf(file,"%f\n",number);
	}
	fclose(file);
}

