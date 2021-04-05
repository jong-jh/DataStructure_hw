/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4


typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if(cQ->front==cQ->rear){		//front 와 rear 의 값이 같으면 -> front 공간이 맨 앞단에 닿았단 뜻이므로 -> 현재 공간은 비었다는 뜻이다.
		printf("\nCircular Queue is empty!\n\n");	//상태가 empty 임을 출력
		return 0;}
	else
		return 1;
}

/* complete the function */
int isFull(QueueType *cQ)
{
   if(cQ->front==(cQ->rear+1)%MAX_QUEUE_SIZE){			//rear 와 front의 값이 같을 시 -> rear가 front공간 즉 끝 부분에 닿은 격이고, -> 큐가 full 인 상태이다.
		printf("\nCircular Queue is full!\n\n");	//상태가 full 임을 출력
		return 0;}
	else
    return 1;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)==1){		//Full 상태가 아니면 실행
	cQ->rear=(cQ->rear+1)%(MAX_QUEUE_SIZE);//rear 값 증가	//full이 아닌게 확정되서야 증가를 해주어야한다.
	cQ->queue[cQ->rear]=item;	//새로운 값을 대입한다.
	}
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
    if(isEmpty(cQ)==1){	//empty 상태가 아니면 실행
		cQ->front=(cQ->front+1)%(MAX_QUEUE_SIZE);	//front 값 증가
		*item='\0';		//값을 지워준다.
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

