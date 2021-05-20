/*
 * graph-search.c
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>


/* for graph */
typedef struct graph {
	int vertex;
	struct graph *link;	//��������Ʈ�� ������ link
} Graph;

/* for stack */
#define MAX_STACK_SIZE		10	//max vertex size = 10
Graph* stack[MAX_STACK_SIZE];
int top = -1;

Graph* pop();
void push(Graph* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		10 //max vertex size = 10
Graph* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Graph* deQueue();
void enQueue(Graph* aNode);

/* functions that you have to implement */
int initializeGraph(Graph** h);
int freeGraph(Graph* h);
int InsertVertex(Graph* h,int);
int InsertEdge(Graph* h,int, int);
void DFS(Graph* h, int);
void BFS(Graph* h, int);
void PrintGraph(Graph* h);
void freeVertex(Graph *ptr);


int main()
{
	char command;
	int v1,v2;
    Graph* head=NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph search                           \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                     \n");
		printf(" Insert Vertex          = v      Insert Edge                = e \n");
		printf(" Depth First Search     = d      Breath First Search        = b \n");
		printf(" Print Graph            = p      Quit                       = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeGraph(&head);
			break;

        case 'q': case 'Q':
			freeGraph(head);
			break;
        
        case 'v': case 'V':
            printf("Your Key = ");
            scanf("%d",&v1);
			InsertVertex(head,v1);
			break;

        case 'e': case 'E':
            printf("Your Key (v1) = ");
            scanf("%d",&v1);
            printf("Your Key (v2) = ");
            scanf("%d",&v2);
			InsertEdge(head,v1,v2);
			break;

        case 'd': case 'D':
			printf("Your Key = ");
            scanf("%d",&v1);
			DFS(head, v1);
			break;

        case 'b': case 'B':
			printf("Your Key = ");
            scanf("%d",&v1);
			BFS(head, v1);
			break;

        case 'p': case 'P':
			PrintGraph(head);
			break;
		
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;
}

int initializeGraph(Graph** h){	
    if(*h!=NULL)	//�� �׷����� �ƴ϶�� �޸� ����
        freeGraph(*h);

    *h=(Graph*)malloc(sizeof(Graph)*10);	//10���� �����带 ��Ÿ�� �迭 ����
    for(int i=0;i<10;i++){
        (*h+i)->link=NULL;
        (*h+i)->vertex=-1;	//�� �������� vertex�� -1���� �ʱ�ȭ
    }

    top=-1;
    front = rear = -1;

    return 1;
}

void freeVertex(Graph *ptr){	//link�� �̵��ϸ鼭 �޸� ����
    if(ptr){
        freeVertex(ptr->link);
        free(ptr);
    }
}

int freeGraph(Graph* h){
    for(int i=0;i<10;i++){
        if((h+i)->link){	//�����忡 link�� �����Ѵٸ� ����� ��� �޸� ����
           freeVertex((h+i)->link);
        }
    }

    free(h);	//������ �����Ҵ� �迭 �޸� ����
    return 0;
}

int InsertVertex(Graph* h,int v1){	//������ vertex ���� �ش� vertex ������ �ʱ�ȭ
   if((h+v1)->vertex==v1){	//�ش� vertex�� �̹� �����Ѵٸ� ������ ��� �� ����
	   printf("\n key is already in graph\n");
	   return 0;
   }
   (h+v1)->vertex = v1;

   return 1;
}

int InsertEdge(Graph* h,int v1, int v2){
	if((h+v1)->vertex==-1||(h+v2)->vertex==-1){	//�ش� vertex�� �������� �ʴ´ٸ� ������ ���
		printf("\n key is not in graph \n");
		return 0;
	}


	Graph* temp1 =(Graph*)malloc(sizeof(Graph));		//���ο� ���� �� ���� ����
	Graph* temp2 =(Graph*)malloc(sizeof(Graph));		//���ο� ���� �� ���� ����
	Graph* p=(h+v1);	//������� �ش�Ǵ� �ε����� ����.

	temp1->vertex=v1;
	temp1->link=NULL;
	temp2->vertex=v2;
	temp2->link=NULL;
/*p �� v1 vertax�� �ش��ϴ� �����忡 ��ġ�ϰ� �ִ�. v1 �����忡 v2 vertex�� �����ؾ��Ѵ�.
�̹� v2 vertex���� v1����� ����Ǿ� �ִ� ���, �Լ��� �����Ѵ�. p�� link�� Ÿ�� �̵� �� �� ū vertax�� �̹� ����Ǿ��ִٸ� v2�� �� ������ ����, ���� ��尡 ���ٸ� v2�� ����
*/
	while(1){
		if(p->vertex==v2){// �̹� ����Ǿ��ִٸ�
			printf("\n Edge already exist \n");
			return 0;
		}

		if(!p->link){	//����Ű�� ��尡 ���ٸ� ����
			p->link=temp2;	//v1 �� v2 �� ����Ŵ
			break;
		}

		if(p->link->vertex > v2){	//��������Ʈ�� vertex ũ�� ������ ����
			temp2->link=p->link;
			p->link=temp2;
			break;
		}

		else p=p->link;		// ���� ��尡 �����Ѵٸ� �̵�
	}
/*p �� v2 vertex�� �ش��ϴ� �����忡 ��ġ. v2 �����忡 v1 vertex�� �����Ѵ�.
��������Ʈ vertex �� ũ�� ������ �����ؾ� BFS, DFS �� �����ϱ� ������ ũ������� vertex�� �������ش�.
*/
	p=(h+v2);
	while(1){
		if(!p->link){ 
			p->link=temp1;	//v2 �� v1�� ����Ŵ
			break;
		}
		if(p->link->vertex > v1){ //��������Ʈ�� vertex ũ�� ������ ����
			temp1->link=p->link;
			p->link=temp1;
			break;
		}
		else p=p->link;
	}

	return 0;
}

/*Depth First Search (iteratvie)
������������ ���ĵ� ��������Ʈ�� �̿��� DFS �� �Ѵ�. ������ �Ǵ� v�� ����ڿ��Լ� �Է¹޴´�.
visited[10] �迭�� �̿��� visit flag �� ǥ�����ش�. �湮�� ���� ���� vertex�� �湮�ϰ� �Ǹ� ����� �� ��, stack�� push�� ���ش�.
���̻� �̵��� link�� ���� ���, pop()�� ���� ��, �ش� ��ġ�� vertex�� ���� ������� �̵��Ѵ�.
stack �� ���� ������ �� ���� (top==-1) ������ �ݺ��Ѵ�.
*/

void DFS(Graph* h,int v){
	if((h+v)->vertex==-1){
		printf("\n key is not in graph \n");
		return ;
	}
	Graph* p = h+v;	//�׷����� ����Ű�� ������
	Graph* ptr = NULL;	//stack �� pop�� ���� ptr

	int visited[10]; for(int i=0;i<10;i++){visited[i]=0;}	//visit flag  0���� �ʱ�ȭ
	top = -1;	//stack top �ʱ�ȭ

	//visited[v]=1;	//�湮 ��� 1 ǥ��
	//push(h+v);

	while(1){
		
		v=p->vertex;	//�������� vertex�� �޴´�.

		if(!visited[v]){	//�ش� vertex�� �湮���� �ʾҴٸ�
			printf("  [%d]  ",v);	//���� ���
			visited[v]=1;			//�湮 flag
			push(h+v);				//stack �� push
			p=h+v;					//�ش� ���� ���� ������� �̵�
		}
		else {			//�ش� vertex�� �湮�� �ߴٸ�
			if(p->link==NULL){	//���� ��尡 �������� �ʴ´ٸ�
				ptr=pop();		//stack �� pop ���ش�.
				//printf(" [%d] ", ptr->vertex);
				p=h+(p->vertex);	//������ �̵�
			}
			p=p->link;	//��� �̵�
		}

		if(top==-1)	break;	//stack�� ������� �ݺ��� Ż��
	}

}
/*Breath First Search
DSF�� �����ϰ� ������������ ���ĵ� ��������Ʈ�� visited[10] flag �� ����Ͽ�, �̹湮 vertex �� ��� ��� �� enqueue, 
�ش� vertex�� �����带 �̵��ϸ鼭 ���� ������ �ݺ����ش�. ���� ���̻� �̵��� link�� ���ٸ� p=dequeue�� ����
���ο� �����忡 ���� �� ���� ������ �ݺ��Ѵ�. Queue �� ������� BFS�� �����Ѵ�. 
*/
void BFS(Graph* h, int v){
	Graph* p=h+v;		//�׷����� ����ų ������
	
	if((h+v)->vertex==-1){
		printf("\n key is not in graph \n");
		return ;
	}

	int visited[10]; for(int i=0;i<10;i++){visited[i]=0;}	//visit flag  0���� �ʱ�ȭ
	rear=front=-1;

	printf("  [%d]  ",v);
	visited[v]=1;
	enQueue(p);

	while(1){
		p=deQueue();
		for(p;p;p=p->link){
			v=p->vertex;
			if(!visited[v]){
				printf("  [%d]  ",p->vertex);
				enQueue(h+v);
				visited[v]=1;
			}
		}
		if(rear==front) break;
	}
}
/*Graph �� ������ִ� �Լ�. Graph ����� ���ð� ���� ����, ��������Ʈ�� ���������� �ľ��� �� �ְ� �Լ��� �����Ͽ���.*/
void PrintGraph(Graph* h){
	Graph* p=h;

	for(int i=0;i<10;i++){
		p=h+i;
		for(int j=0;j<10;j++){	//link�� ���� �̵��ϸ鼭 �����ϴ� vertex�� ���, link�� ���ٸ� ���� ������� �̵�
			if(p->vertex!=-1){	//p->vertex�� -1 �̶�� �����忡 vertex�� insert ���� ���� �����̹Ƿ� ������� �ʴ´�.
				printf(" [%d] ",(p->vertex));
			}
			if(p->link){
				p=p->link;
			}
			else
				break;
		}
		printf("\n");
	}
}

Graph* pop()	//stack pop
{
	if(top==-1)	return NULL;	
	else return stack[top--];
}

void push(Graph* aNode)	//stack push 
{	if(top==MAX_STACK_SIZE-1) printf("stack is full\n");	
	else stack[++top]=aNode;	
}



Graph* deQueue()	//deQueue
{
	if(front==rear)	return 0;	
	else return queue[++front];	
}

void enQueue(Graph* aNode)	//enQueue
{
	if(rear==MAX_QUEUE_SIZE-1)	printf("queue is full\n");	
	else queue[++rear]=aNode;
}