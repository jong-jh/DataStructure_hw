/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	printf("----2018038051 ������----\n\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){
	listNode* p = h->rlink;
	listNode* prev = NULL;
	
	while(p != h) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
	listNode* p=h->rlink;
	listNode* temp=(listNode*)malloc(sizeof(listNode));	//��� ����
	temp->key=key;

	if(p==h){//list�� ����ִٸ�
		temp->rlink=h;
		temp->llink=h;
		h->rlink=temp;
		h->llink=temp;
		return 1;
	}
	while(1){
		if(p->rlink==h){//list�� �������̶��
			temp->llink=p;
			temp->rlink=h;

			p->rlink=temp;
			h->llink=temp;
			break;
		}
		else p=p->rlink;
	}

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
	listNode *p=h->rlink;
	
	if(p==h){//list �� ����ִٸ� ������ ���
		printf("list is empty now. \n");
		return 0;
	}
	
	while(1){
		if(p->rlink==h){
			p->rlink->llink=p->llink;
			p->llink->rlink=p->rlink;//�������̱� ������ h�� ����Ŵ. (p->llink->rlink=h)
			free(p);
			break;
		}
		else p=p->rlink;
	}

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {
	listNode* temp=(listNode*)malloc(sizeof(listNode));	//��� ����
	temp->key=key;

	if(h->rlink==h){//list�� ����ִٸ�
		temp->rlink=h;
		temp->llink=h;
		h->rlink=temp;
		h->llink=temp;
		return 1;
	}

	temp->llink=h;
	temp->rlink=h->rlink;
	h->rlink=temp;
	temp->rlink->llink=temp;	//temp�� ����Ű�� ����� llink�� temp�� ����Ų��.

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {
	listNode *p=h->rlink;
	
	if(p==h){//list �� ����ִٸ� ������ ���
		printf("list is empty now. \n");
		return 0;
	}

	p->llink->rlink=p->rlink;
	p->rlink->llink=p->llink;
	free(p);

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
	listNode *lead=h->rlink;
	listNode *trail=NULL;

	while(lead!=h){
		trail=lead->llink;		//trail�� lead��llink���� ����
		lead->llink=lead->rlink;//llink���� rlink������ �ٲ�
		lead->rlink=trail;		///rlink ���� llink������ �ٲ� -> ������ �ٲ�

		lead=lead->llink;	//�������� �̵�
	}

	h->llink=h->rlink;
	h->rlink=trail->llink;

	return 1;
}



/**
 *  ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� 
 **/
int insertNode(listNode* h, int key) {
	listNode *p=h->rlink;
	listNode* temp=(listNode*)malloc(sizeof(listNode));	//��� ����
	temp->key=key;

	if(h->rlink==h){//list�� ����ִٸ�
		temp->rlink=h;
		temp->llink=h;
		h->rlink=temp;
		h->llink=temp;
		return 1;
	}
	while(1){
		if(key<=h->rlink->key){		//temp�� �� �� �ʿ� �;��� ��
			temp->rlink=h->rlink;	//temp rlink �� �����尡 ����Ű�� ���� ����
			temp->llink=h;			//llink�� h�� ���� (ù �� ° �̹Ƿ�)
			h->rlink->llink=temp;	//�и� ����� llink�� temp�� ����
			h->rlink=temp;			//��� ��� ��ü
			break;
		}

		if(p->rlink==h){	//temp�� key���� ���� �������� �� �� (���� Ŭ ��)
			temp->rlink=h;
			temp->llink=p;
			p->rlink=temp;
			h->llink=temp;
			break;
		}
		else if(key<=p->rlink->key){//temp�� list�� ��� ���̿� ���� ��
			temp->llink=p;	//temp�� list�� ����
			temp->rlink=p->rlink;
			
			p->rlink->llink=temp;	//������ �� �� ������ temp�� ����
			p->rlink=temp;
			break;
		}
		else if(key>p->rlink->key)	p=p->rlink;	//temp ��key�� ���� �� ���� �� ũ�� �̵�
	}

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	listNode *p=h->rlink;
	
	if(p==h){//list �� ����ִٸ� ������ ���
		printf("list is empty now. \n");
		return 0;
	}
	
	while(1){
		if(p->key==key){//���� ã�� ���
			p->rlink->llink=p->llink;	//�ش� ��带 ����
			p->llink->rlink=p->rlink;
			free(p);
			break;
		}
		else{ p=p->rlink;	//���� ���� �̵�
			if(p==h) {printf("Key is not in list!\n"); break;}//���� ���ٸ� ������ ���
			}
	}

	return 0;
}


