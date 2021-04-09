/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	
	listNode* p;
	p=h->first;
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key=key;


	if(h->first==NULL){	//h가 비어있다면 첫 번째 입력
		temp->link=NULL;
		h->first=temp;
		return 0;
	}
	while(h->first){// 값이 있을 때
	
		if(key<=h->first->key){	//temp가 맨 앞 쪽에 와야할 때 
			temp->link=h->first;
			h->first=temp;
			break;
		}
		
		if(key>p->key){	//temp 의 값이 가리키고 있는 값 보다 클 때
			if(p->link==NULL){ //다음 값이 비어있다면
				temp->link=NULL;
				p->link=temp;
				break;
			}
			else if(key<=p->link->key){//temp의 값이 사이에 있다면
				temp->link=p->link;
				p->link=temp;
				break;
			}
			else if(key>p->link->key){//temp의 값이 다음 값 보다 더 크다면
				p=p->link;
			}
		}

	}
	
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* p;
	p=h->first;
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key=key;

	if(h->first==NULL){	//h가 비어있다면 바로 추가.
		temp->link=NULL;
		h->first=temp;
		return 0;
	}

	while(1){
		if(p->link==NULL){	//p->link 가 가리키는 게 없다면 마지막이므로
			temp->link=NULL;
			p->link=temp;
			break;
		}
		else{
			p=p->link;	//다음 순서로 이동
		}
	}
	return 0;
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
		h->first=h->first->link;
	}
	free(p);	//p가 가리키고 있는 공간 동적할당 해제

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* p = h->first;
	listNode* c; 		//동적해제 할 위치를 저장해주는 포인터
	
	if(h->first==NULL){	//h가 비어있다면 다음을 출력.
		printf("list is empty. \n");
		return 0;
	}
	
	if(h->first->key==key){//첫번째 노드와 일치한다면
		h->first=h->first->link;
		free(p);
		return 0;
	}

	while(1){
		if(p->link==NULL){//다 찾아보았는데 값이 없으면
			printf("key is not in list\n");
			break;
		}
		else {
			if(p->link->key==key){	//값을 찾았을 때
				if(p->link->link==NULL){
					free(p->link);
					p->link=NULL;
				}
				else{
					c=p->link;
					p=p->link;
					free(c);
					break;
				}
			}
			else
				p=p->link; //다음 노드로 이동
		}
	}

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	
	listNode* p=h->first;
	
	if(h->first==NULL){	//h가 비어있다면 다음을 출력.
		printf("list is empty. \n");
		return 0;
	}
	
	if(p->link==NULL){
		h->first=h->first->link;
		return 0;
	}

	while(1){
		if(p->link->link==NULL){	//p->link 가 가리키는 게 없다면 마지막이므로
			free(p->link);
			p->link=NULL;
			break;
		}
		else{
			p=p->link;	//다음 순서로 이동
		}
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {	//역순으로 만드는 연산
	/*연결이 끊기지 않기 위해 3개의 변수가 필요하다.*/
	listNode* trail=NULL;
	listNode* middle = NULL;
	listNode* lead = h->first;
	
	while(lead){//lead 가 0이면 체인의 끝에 도달한 것이다.
		
		trail=middle;		//trail을 middle로 이동한다.
		middle=lead;		//middle을 lead로 이동한다.
		lead=lead->link;	//middle이 있기 때문에 다음 노드로 이동이 가능하다.
		middle->link=trail;	//middle의 링크를 역순으로 바꾸어 준다.
	}
	h->first=middle;		//연산이 끝나면 맨 앞의 노드는 middle이 위치하고 있는 자리이다.
	

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
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

