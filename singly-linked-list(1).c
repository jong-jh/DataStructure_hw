/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	
	listNode* p;
	p=h->first;
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key=key;


	if(h->first==NULL){	//h�� ����ִٸ� ù ��° �Է�
		temp->link=NULL;
		h->first=temp;
		return 0;
	}
	while(h->first){// ���� ���� ��
	
		if(key<=h->first->key){	//temp�� �� �� �ʿ� �;��� �� 
			temp->link=h->first;
			h->first=temp;
			break;
		}
		
		if(key>p->key){	//temp �� ���� ����Ű�� �ִ� �� ���� Ŭ ��
			if(p->link==NULL){ //���� ���� ����ִٸ�
				temp->link=NULL;
				p->link=temp;
				break;
			}
			else if(key<=p->link->key){//temp�� ���� ���̿� �ִٸ�
				temp->link=p->link;
				p->link=temp;
				break;
			}
			else if(key>p->link->key){//temp�� ���� ���� �� ���� �� ũ�ٸ�
				p=p->link;
			}
		}

	}
	
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* p;
	p=h->first;
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	temp->key=key;

	if(h->first==NULL){	//h�� ����ִٸ� �ٷ� �߰�.
		temp->link=NULL;
		h->first=temp;
		return 0;
	}

	while(1){
		if(p->link==NULL){	//p->link �� ����Ű�� �� ���ٸ� �������̹Ƿ�
			temp->link=NULL;
			p->link=temp;
			break;
		}
		else{
			p=p->link;	//���� ������ �̵�
		}
	}
	return 0;
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
		h->first=h->first->link;
	}
	free(p);	//p�� ����Ű�� �ִ� ���� �����Ҵ� ����

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode* p = h->first;
	listNode* c; 		//�������� �� ��ġ�� �������ִ� ������
	
	if(h->first==NULL){	//h�� ����ִٸ� ������ ���.
		printf("list is empty. \n");
		return 0;
	}
	
	if(h->first->key==key){//ù��° ���� ��ġ�Ѵٸ�
		h->first=h->first->link;
		free(p);
		return 0;
	}

	while(1){
		if(p->link==NULL){//�� ã�ƺ��Ҵµ� ���� ������
			printf("key is not in list\n");
			break;
		}
		else {
			if(p->link->key==key){	//���� ã���� ��
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
				p=p->link; //���� ���� �̵�
		}
	}

	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	
	listNode* p=h->first;
	
	if(h->first==NULL){	//h�� ����ִٸ� ������ ���.
		printf("list is empty. \n");
		return 0;
	}
	
	if(p->link==NULL){
		h->first=h->first->link;
		return 0;
	}

	while(1){
		if(p->link->link==NULL){	//p->link �� ����Ű�� �� ���ٸ� �������̹Ƿ�
			free(p->link);
			p->link=NULL;
			break;
		}
		else{
			p=p->link;	//���� ������ �̵�
		}
	}

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {	//�������� ����� ����
	/*������ ������ �ʱ� ���� 3���� ������ �ʿ��ϴ�.*/
	listNode* trail=NULL;
	listNode* middle = NULL;
	listNode* lead = h->first;
	
	while(lead){//lead �� 0�̸� ü���� ���� ������ ���̴�.
		
		trail=middle;		//trail�� middle�� �̵��Ѵ�.
		middle=lead;		//middle�� lead�� �̵��Ѵ�.
		lead=lead->link;	//middle�� �ֱ� ������ ���� ���� �̵��� �����ϴ�.
		middle->link=trail;	//middle�� ��ũ�� �������� �ٲپ� �ش�.
	}
	h->first=middle;		//������ ������ �� ���� ���� middle�� ��ġ�ϰ� �ִ� �ڸ��̴�.
	

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

