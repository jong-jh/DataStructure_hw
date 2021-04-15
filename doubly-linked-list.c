/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;


typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	*h=temp;
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* p;
	p=h->first;
	listNode* temp = (listNode*)malloc(sizeof(listNode));	//노드 생성
	temp->key=key;

	if(h->first==NULL){//list가 비어있다면
		temp->llink=NULL;	//첫 번째 노드 이므로 가리키는 노드가 없다.
		temp->rlink=NULL;
		h->first=temp;
		return 0;
	}
	while(1){
		if(p->rlink==NULL){	//p->rlink 가 가리키는 노드가 없다면 마지막 위치이므로
			temp->rlink=NULL;	//temp의 rlink NULL
			temp->llink=p;		//temp의 llink p를 가리킨다.
			p->rlink=temp;		//p의rlink 는 새로운 값 temp를 가리킨다.
			break;
		}
		else p=p->rlink;	//다음 순서로 이동
	}
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode *p=h->first;

	if(h->first==NULL){	//h가 비어있다면 다음을 출력.
		printf("list is empty. \n");
		return 0;
	}

	if(p->rlink==NULL){ //리스트에 노드가 하나만 있다면.
		h->first=NULL;
		free(p);
		return 0;
	}

	while(1){
		if(p->rlink->rlink==NULL){	//p->link 가 가리키는 게 없다면 마지막이므로
			free(p->rlink);
			p->rlink=NULL;
			break;
		}
		else{
			p=p->rlink;	//다음 순서로 이동
		}
	}

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	
	listNode* temp = (listNode*)malloc(sizeof(listNode));	//노드 생성
	temp->key=key;

	if(h->first==NULL){//list가 비어있다면
		temp->llink=NULL;	//첫 번째 노드 이므로 가리키는 노드가 없다.
		temp->rlink=NULL;
		h->first=temp;
		return 0;}
	
	else{
		temp->rlink=h->first;
		temp->llink=NULL;
		h->first->llink=temp;

		h->first=temp;
	return 0;}
	
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* p = h->first;

	if(h->first==NULL){	//h가 비어있다면 다음을 출력.
		printf("list is empty. \n");
		return 0;
	}
	else {
		h->first=h->first->rlink;	//헤더노드가 가리키는 값을 헤더노드 링크의 값으로 교체.(이동)
	}
	free(p);	//p가 가리키고 있는 공간 동적할당 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 * 이중 연결리스트의 특성을 이용하여 재배치 하였다.
 * 처음 재배치를 하게되면, 오른쪽 왼쪽 개념을 상실하는 대신
 * rlink는 다음노드를, llink는 이전노드를 의미하게 된다.
 */
int invertList(headNode* h) {
	listNode* lead = h->first;
	listNode* trail=NULL;
	while(lead){
		
		trail=lead->llink;			//trail에 llink의 값을 저장
		lead->llink=lead->rlink;	//llink값을 rlink값으로 바꿈
		lead->rlink=trail;			//rlink 값을 llink값으로 바꿈 -> 순서가 바뀜 

		lead=lead->llink;			//다음 노드로 이동(llink가 다음노드를 가리킨다)
	}
	h->first=trail->llink;			//맨 앞의 노드를 h->first가 가리키게 둔다.

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 1;
}


