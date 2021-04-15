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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;


typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
        - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	*h=temp;
	return 1;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* p;
	p=h->first;
	listNode* temp = (listNode*)malloc(sizeof(listNode));	//��� ����
	temp->key=key;

	if(h->first==NULL){//list�� ����ִٸ�
		temp->llink=NULL;	//ù ��° ��� �̹Ƿ� ����Ű�� ��尡 ����.
		temp->rlink=NULL;
		h->first=temp;
		return 0;
	}
	while(1){
		if(p->rlink==NULL){	//p->rlink �� ����Ű�� ��尡 ���ٸ� ������ ��ġ�̹Ƿ�
			temp->rlink=NULL;	//temp�� rlink NULL
			temp->llink=p;		//temp�� llink p�� ����Ų��.
			p->rlink=temp;		//p��rlink �� ���ο� �� temp�� ����Ų��.
			break;
		}
		else p=p->rlink;	//���� ������ �̵�
	}
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode *p=h->first;

	if(h->first==NULL){	//h�� ����ִٸ� ������ ���.
		printf("list is empty. \n");
		return 0;
	}

	if(p->rlink==NULL){ //����Ʈ�� ��尡 �ϳ��� �ִٸ�.
		h->first=NULL;
		free(p);
		return 0;
	}

	while(1){
		if(p->rlink->rlink==NULL){	//p->link �� ����Ű�� �� ���ٸ� �������̹Ƿ�
			free(p->rlink);
			p->rlink=NULL;
			break;
		}
		else{
			p=p->rlink;	//���� ������ �̵�
		}
	}

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	
	listNode* temp = (listNode*)malloc(sizeof(listNode));	//��� ����
	temp->key=key;

	if(h->first==NULL){//list�� ����ִٸ�
		temp->llink=NULL;	//ù ��° ��� �̹Ƿ� ����Ű�� ��尡 ����.
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
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* p = h->first;

	if(h->first==NULL){	//h�� ����ִٸ� ������ ���.
		printf("list is empty. \n");
		return 0;
	}
	else {
		h->first=h->first->rlink;	//�����尡 ����Ű�� ���� ������ ��ũ�� ������ ��ü.(�̵�)
	}
	free(p);	//p�� ����Ű�� �ִ� ���� �����Ҵ� ����

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 * ���� ���Ḯ��Ʈ�� Ư���� �̿��Ͽ� ���ġ �Ͽ���.
 * ó�� ���ġ�� �ϰԵǸ�, ������ ���� ������ ����ϴ� ���
 * rlink�� ������带, llink�� ������带 �ǹ��ϰ� �ȴ�.
 */
int invertList(headNode* h) {
	listNode* lead = h->first;
	listNode* trail=NULL;
	while(lead){
		
		trail=lead->llink;			//trail�� llink�� ���� ����
		lead->llink=lead->rlink;	//llink���� rlink������ �ٲ�
		lead->rlink=trail;			//rlink ���� llink������ �ٲ� -> ������ �ٲ� 

		lead=lead->llink;			//���� ���� �̵�(llink�� ������带 ����Ų��)
	}
	h->first=trail->llink;			//�� ���� ��带 h->first�� ����Ű�� �д�.

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	return 1;
}


