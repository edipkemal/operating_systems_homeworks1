#include <pthread.h>
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

float random_number_array[ARRAYSIZE]; //random numbers' array
operation opr1, opr2, opr3, opr4, opr5;

void* square_sum(void *prm);
void* minValue(void* prm);
void* maxValue(void* prm);
void* most_frequent(void* prm);
void* standard_deviation(void* prm);
void read_from_file(float array[], char file_name[]);


int main(){
	char file_path[]="random_numbers.txt";
	
	read_from_file(random_number_array,file_path);
	
	pthread_t t_1,t_2,t_3,t_4,t_5;
	
	clock_t start = clock();

	t_1=pthread_create(&t_1,NULL, square_sum,NULL);
	t_2=pthread_create(&t_2,NULL, minValue,NULL);
	t_3=pthread_create(&t_3,NULL, maxValue,NULL);
	t_4=pthread_create(&t_4,NULL, most_frequent,NULL);
	t_5=pthread_create(&t_5,NULL, standard_deviation,NULL);
	
	printf("\n--- Results ---\n\n");
	
	pthread_join(t_1,NULL);
	pthread_join(t_2,NULL);
	pthread_join(t_3,NULL);
	pthread_join(t_4,NULL);
	pthread_join(t_5,NULL);

	printf("Operation 1:\nSquare of the sum of values of the list: %f \n\n",opr1.result_1);
	printf("Operation 2:\nMinimum Value of the List: %f \nThis is the %dth element of the list.\n\n",opr2.result_1,(int)opr2.result_2);
	printf("Operation 3:\nMaximum Value of the List: %f \nThis is the %dth element of the list.\n\n",opr3.result_1,(int)opr3.result_2);
	printf("Operation 4:\nMost Frequently Occurred Value of the List: %f \nThe Occurrence Count of the Value (%f): %d times\n\n",opr4.result_1,opr4.result_1,(int)opr4.result_2);
	printf("Operation 5:\nMean of the List Elements: %.2f \nStandard Deviation of the List Elements: %.2f\n\n",opr5.result_1,opr5.result_2);
	clock_t stop = clock();
	
	double passed_time= (double)(stop-start)/ CLOCKS_PER_SEC;
	printf("Total execution time: : %f ms\n", passed_time*1000); //multiplied by 1000 since convert from s to ms



	FILE * file;
	file=fopen("Comparison.txt","a+");
	fprintf(file,"Runtime of the Multi Thread Program for the Given List:%fms\n",passed_time*1000);
	fprintf(file,"My opinion on the cause of difference in runtimes of parts:\nWe can clearly see that multi thread program much more faster than single thread program.\nIn single thread program, 5 operations executed with a single thread but in multi thread program, every operation executed with different threads.\nSo processor could do all operations in same time, that is why multi thread program is faster.");
	
	fclose(file);
	pthread_exit(NULL);
}

void* square_sum(void *prm){ //operation 1

	printf("Thread with ID %i is created for Operation 1!\n",(int)pthread_self());
	float summ, result;
	int i;
	for(i=0; i<ARRAYSIZE; i++){
		summ+=random_number_array[i];
	}
	result=summ*summ;
	opr1.result_1=result;
	pthread_exit(NULL);
}

void* minValue(void* prm){ // operation 2
	printf("Thread with ID %i is created for Operation 2!\n",(int)pthread_self());
	int i, index;
	float min;
	min=random_number_array[0];
	for(i=1; i<ARRAYSIZE;i++){
		if(random_number_array[i]<min){
			min=random_number_array[i];
			index=i;
		}
	}
	opr2.result_1=min;
	opr2.result_2=(float)index;
	pthread_exit(NULL);
}


void* maxValue(void* prm){ //operation 3 
	printf("Thread with ID %i is created for Operation 3!\n",(int)pthread_self());
	int i, index;
	float max;
	max=random_number_array[0];
	for(i=1; i<ARRAYSIZE;i++){
		if(random_number_array[i]>max){
			max=random_number_array[i];
			index=i;
		}
	}
	opr3.result_1=max;
	opr3.result_2=(float)index;
	pthread_exit(NULL);
}

void* most_frequent(void* prm){ //operation 4
	printf("Thread with ID %i is created for Operation 4!\n",(int)pthread_self());
	int i,j,occurance,temp_occur;
	float number,temp_number;
	occurance=0;
	for(i=0;i<ARRAYSIZE;i++){
		temp_occur=0;
		for(j=0;j<ARRAYSIZE;j++){
			if(random_number_array[i]==random_number_array[j]){
				temp_occur++;
				temp_number=random_number_array[i];
			}
		}
		if(temp_occur>occurance){
			occurance=temp_occur;
			number=temp_number;
		}
	}

	opr4.result_1=number;
	opr4.result_2=(float)occurance;
	pthread_exit(NULL);
}

void* standard_deviation(void* prm){ //operation 5
	printf("Thread with ID %i is created for Operation 5!\n",(int)pthread_self());
	float summ, mean, standard_deviation;
	int i;
	for(i=0;i<ARRAYSIZE;i++){
		summ+=random_number_array[i];
	}
	mean=summ/ARRAYSIZE;
	summ=0;
	for(i=0;i<ARRAYSIZE;i++){
		summ+=(random_number_array[i]-mean)*(random_number_array[i]-mean);
	}
	summ=summ/(ARRAYSIZE-1);
	standard_deviation=sqrt(summ);
	
	opr5.result_1=mean;
	opr5.result_2=standard_deviation;
	pthread_exit(NULL);
}

void read_from_file(float array[], char file_name[]){
	int i;
	float number;
	FILE *file;
	file=fopen(file_name,"r+");
	for(i=0;i<ARRAYSIZE;i++){
		fscanf(file,"%f",&number);
		array[i]=number;
		
	}
	fclose(file);
}

