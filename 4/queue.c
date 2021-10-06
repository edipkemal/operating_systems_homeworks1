#include <string.h>
#include <stdio.h>

//Edip Kemal Sardoðan 240201026

#define CAPACITY 20



// I used this reference code for my enqueue-dequeue operations in my homework

/* Title: Simple C implementation of queue.
Author: Arnon Eilat
Date: 2017
Availability: https://gist.github.com/ArnonEilat/4471278#file-queue-c */



typedef struct {
    int id;
    int bursttime;
    char *state;
} DATA;

typedef struct Process_t {
    DATA data;
    struct Process_t *prev;
} Process;

typedef struct Queue {
	char *name;
    Process *head;
    Process *tail;
    int size;
    int limit;
} Queue;


Queue *ConstructQueue(int limit, char *name); //constructs a queue with given limit and name of queue
void DestructQueue(Queue *queue);
int Enqueue(Queue *pQueue, Process *item);
Process *Dequeue(Queue *pQueue);
int isEmpty(Queue* pQueue);
Queue *cpuExecution(Queue *queue, int time); //cpu execution on processes and burst time calculations
void queueTransfer(Queue *fromQueue, Queue *toQueue); //transfers the processes from a queue to another

int processValues[CAPACITY][2]={{1,7},{2,27},{3,44},{4,32},{5,31},{6,28},{7,16},{8,8},{9,23},{10,49},{11,8},{12,11},{13,9},{14,27},{15,21},{16,38},{17,42},{18,50},{19,4},{20,19}};

int main(){
	printf("Simulation Started!\n\n");
	
	Queue *rrQ8=ConstructQueue(CAPACITY,"1st RR"); //round robin with quantum 8ms
	Queue *rrQ16=ConstructQueue(CAPACITY,"2nd RR"); //round robin with quantum 16ms
	Queue *fcfs=ConstructQueue(CAPACITY,"FCFS");  //first come first serve
    Queue *newQueue = ConstructQueue(CAPACITY,"created"); //the queue for store the created processes
    
	Process *process;
	int i;
    for (i = 0; i < CAPACITY; i++) { //creates processes with id and burst time data in the processValues array 
        process = (Process*) malloc(sizeof (Process));
        process->data.id = processValues[i][0];
        process->data.bursttime = processValues[i][1];
        process->data.state="NEW";
        printf("Process %d created with a burst time of %dms. Its state is assigned to %s.\n",process->data.id,process->data.bursttime,process->data.state);
        Enqueue(newQueue, process);
    }
	printf("\n");
    
    queueTransfer(newQueue,rrQ8); //processes is transfered to 1st RR Queue
    
    rrQ8=cpuExecution(rrQ8,8);
	
	queueTransfer(rrQ8,rrQ16); //processes is transfered to 2nd RR Queue
	
	rrQ16=cpuExecution(rrQ16,16);

	queueTransfer(rrQ16,fcfs); //processes is transfered to FCFS Queue
	
	fcfs=cpuExecution(fcfs,0);
	
	
	printf("\nSimulation Completed...\n");
	return 0;
}
void queueTransfer(Queue *fromQueue, Queue *toQueue){//transfers the processes from a queue to another
	Process *process = (Process*) malloc(sizeof (Process));
	while (!isEmpty(fromQueue)) {
        process = Dequeue(fromQueue);
        if(process->data.state=="TERMINATED"){ // if the process terminated it won't transfer to next queue
        	continue;
		}
        process->data.state="READY";
        Enqueue(toQueue,process);
        printf("Process %d moved to %s Queue with a burst time of %dms. Its state is updated to %s.\n",process->data.id,toQueue->name,process->data.bursttime,process->data.state);
    }
    printf("\n");

}

Queue *cpuExecution(Queue *queue, int time){ //cpu execution on processes and burst time calculations
	Queue *tempQueue = ConstructQueue(CAPACITY, queue->name);
	Process *process ;
	while (!isEmpty(queue)) {
		process = Dequeue(queue);
		process->data.state="RUNNING";
		printf("Process %d moved from %s Queue to CPU with a burst time of %dms. Its state is updated to %s.\n",process->data.id,queue->name,process->data.bursttime,process->data.state);
		if(process->data.bursttime<=time || time==0){ //time 0 means fcfs 
			process->data.bursttime=0;
			process->data.state="TERMINATED";
			printf("Process %d removed from CPU for completing its execution. Its state is updated to %s.\n",process->data.id,process->data.state);
		}else{
	        process->data.bursttime-=time;
	        process->data.state="BLOCKED";	
	        printf("Process %d removed from CPU with a remaining burst time of %dms. Its state is updated to %s.\n",process->data.id,process->data.bursttime,process->data.state);
		}
        Enqueue(tempQueue,process);
    }
	printf("\n");
    return tempQueue;
	
}

Queue *ConstructQueue(int limit, char *name) { //constructs a queue with given limit and name of queue
    Queue *queue = (Queue*) malloc(sizeof (Queue));
    if (queue == NULL) {
        return NULL;
    }
    queue->name = name;
    queue->limit = limit;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

int Enqueue(Queue *pQueue, Process *process) {
    /* Bad parameter */
    if ((pQueue == NULL) || (process == NULL)) {
        return 0;
    }
    // if(pQueue->limit != 0)
    if (pQueue->size >= pQueue->limit) {
        return 0;
    }
    /*the queue is empty*/
    process->prev = NULL;
    if (pQueue->size == 0) {
        pQueue->head = process;
        pQueue->tail = process;

    } else {
        /*adding process to the end of the queue*/
        pQueue->tail->prev = process;
        pQueue->tail = process;
    }
    pQueue->size++;
    return 1;
}
Process * Dequeue(Queue *pQueue) {
    /*the queue is empty or bad param*/
    if (isEmpty(pQueue))
        return NULL;
        
    Process *process;   
    process = pQueue->head;
    pQueue->head = (pQueue->head)->prev;
    pQueue->size--;
    return process;
    
}
int isEmpty(Queue* pQueue) {
    if (pQueue == NULL) {
        return 0;
    }
    if (pQueue->size == 0) {
        return 1;
    } else {
        return 0;
    }
}
