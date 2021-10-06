#include<stdio.h>
#include<math.h>
//Edip Kemal Sardoðan 240201026

typedef struct {
	float x;
	float y;
}point;

float differenceCalculator(point p1, point p2);
float perimeterCalculator(point p1, point p2, point p3);

int main(){
	point p1,p2;
	int numOfPoints;
	printf("Please enter the number of points :\n");
	scanf("%d",&numOfPoints);
	
	if(!(numOfPoints==2 | numOfPoints==3)){
		printf("It can be 2 or 3, try again!");
	}
	printf("Enter x and y values of the first point :\n"); //first point
	scanf("%f %*c %f",&p1.x,&p1.y);
	
	printf("Enter x and y values of the second point :\n"); //second point
	scanf("%f %*c %f",&p2.x,&p2.y);
		
	if(numOfPoints==3){
		point p3;
		printf("Enter x and y values of the third point :\n"); //third point, if we have
		scanf("%f %*c %f",&p3.x,&p3.y);
		
		printf("Calculating perimeter of the triangle . . .\nResult is %.2f",perimeterCalculator(p1,p2,p3));
		return 0;
	}
	printf("Calculating length of the line . . .\nResult is %.2f",differenceCalculator(p1,p2));
	
	return 0;
}

float differenceCalculator(point p1, point p2){
	float diffx,diffy,diff; //differences between points
	diffx=p1.x-p2.x;
	diffy=p1.y-p2.y;
	
	if(diffx<0){ 
		diffx=diffx*(-1); //to avoid negative result
	}
	if(diffy<0){
		diffy=diffy*(-1);
	}

	diff=sqrt(pow(diffx,2)+pow(diffy,2));
	return diff;
}

float perimeterCalculator(point p1, point p2, point p3){
	float edge1,edge2,edge3;
	edge1=differenceCalculator(p1,p2);
	edge2=differenceCalculator(p1,p3);
	edge3=differenceCalculator(p2,p3);
	return edge1+edge2+edge3; //perimeter of the triangle
}
