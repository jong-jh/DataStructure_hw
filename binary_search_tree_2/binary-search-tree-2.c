/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

Node* searchIterative(Node* head, int key);		//�ش�Ǵ� key�� ���� ����� �ּҸ� ��ȯ�ϴ� �Լ�
void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	top=-1;	//top ��ġ �ʱ�ȭ
	for(;;){	//stack �� ������ �� ���� �ݺ�
		for(;node;node = node->left)	push(node);	//stack�� push

		node=pop();	//temp�� pop

		if(!node) break;	//temp�� NULL �̸� �ݺ� ����

		printf(" [%d] ", node->key);
		node=node->right;	//temp->right �� �̵�(��µ� ����� ���������� �̵�)
	}

}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	front=rear=-1;
	if(!ptr) return;	//����Ʈ���̸� return;
	enQueue(ptr);		//ptr �� queue �� add

	for(;;){
		ptr=deQueue();	//ptr�� dequeue 

		if(ptr){	//ptr�� �����ϸ� ��� �� �ڽ� ��带 enqueue
			printf(" [%d] ",ptr->key);
			if(ptr->left)	enQueue(ptr->left);
			if(ptr->right)	enQueue(ptr->right);
		}
		else break;	//queue�� ���̻� ���� ������ �ݺ��� ����
	}
	
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* delete=searchIterative(head,key);	//�����Ϸ��� ���� ��ġ Ȯ��
	
/*i �����Ϸ��� ���� tree�� ���� ��*/
	if(!delete){	
		printf("key is not in tree\n");
		return 0;
	}
	Node* p=head->left;		
	
	// /*tree�� ��尡 �ϳ��ۿ� ���ٸ� �������� left�� NULL�� �ϰ� ������ ����� �޸� ���� ���ش�.*/
	// if(p==delete){head->left=NULL; free(delete); return 0;}	

/*ii �����ϰ��� �ϴ� ��尡 �ܸ���� �� ��*/
	if(delete->left == NULL&&delete->right==NULL){//leaf ��� �� ���
		
		/*tree�� ��尡 �ϳ��ۿ� ���ٸ� �������� left�� NULL�� �ϰ� ������ ����� �޸� ���� ���ش�.*/
		if(p==delete){head->left=NULL; free(delete); return 0;}	
		
		while(1){
		/*�θ����� link�� NULL�� ���ְ�, ������ ����� �޸𸮸� �����Ѵ�.*/
		if(p->left==delete){	
			p->left=NULL; free(delete); return 0;}
		if(p->right==delete){
			p->right=NULL; free(delete); return 0;}

		if(key<p->key)	//key ���� ������ ������ ������
			p=p->left;	//���� ����Ʈ���� �̵�
		else
			p=p->right;	//key�� ������ ������ ũ�� ������ ����Ʈ���� �̵�
		}
	}

/*iii �����ϰ��� �ϴ� ��尡 �ϳ��� �ڽĸ��� ���� ��*/
	if(delete->left==NULL){	//������ �ڽĳ�常�� ���� ��
		if(p==delete){head->left=delete->right; free(delete); return 0;}//ù ��° ��尡 ������ ����� �� �����尡 ������ ����� �ڽĳ�带 ����Ų��.

		while(1){	//������ �� ���� �ݺ�
			if(p->left==delete){	//p->left �� ������ �׸��� �ִٸ�
				p->left=delete->right;	//p �� ������ �׸��� right�� �ڽĳ��� ������ �ȴ�.
				free(delete);
				return 0;
			}
			if(p->right==delete){	//p->right�� ������ �׸��� �ִٸ�
				p->right=delete->right;	//p�� ������ �׸��� right�� �ڽĳ��� ������ �ȴ�.
				free(delete);
				return 0;
			}/*Ʈ�� �̵�*/
			if(key<p->key)	p=p->left;
			else	p=p->right;
		}
	}
	/*���� �ڽĳ�常�� ���� ��. �ռ� ������ �ڽĳ�常�� ���� ���� ������ �׸��� left�� �ڽĳ���
	������ �� �ܿ� �����ϴ�.*/
	if(delete->right==NULL){	//���� �ڽĳ�常�� ���� ��
		if(p==delete){head->left=delete->left; free(delete); return 0;}	//ù ��° ��尡 ������ ����� �� �����尡 ������ ����� �ڽĳ�带 ����Ų��.

		while(1){
			if(p->left==delete){
				p->left=delete->left;
				free(delete);
				return 0;
			}
			if(p->right==delete){
				p->right=delete->left;
				free(delete);
				return 0;
			}
			if(key<p->key)	p=p->left;
			else	p=p->right;
		}
	}
	
/*iv �����ϰ��� �ϴ� ��尡 �� ���� �ڽ��� ���� �� (������ ����Ʈ������ ���� ���� ������ ��ü)*/
	Node* ptr=NULL;	//������ ��带 ��ü�� ��带 ����ų ������
	p=head;
	while(1){
		
		if(p->left==delete){//p -> left �� ������ �׸��� ���
			
			ptr=delete->right; //������ �׸��� ������ ����Ʈ���� �̵�
			
			if(ptr->left==NULL){	//������ �׸��� ������ ��尡 ���� ���� ���̶��
				
				ptr->left=delete->left;
				p->left=ptr;
				free(delete);
				return 0;
			}

			ptr=ptr->left;	
			delete=delete->right;	//ptr�� ���� ��忡 ��ġ
			
			for(;;){	//������ �׸��� ������ ����Ʈ�� �� ���� ���� �� ã��
				if(ptr->left==NULL) break;

				ptr=ptr->left;
				delete=delete->left;
			}
			/*ptr: ���� ���� ��� (������ �׸��� ��ü ���)
			, delete: ���� ���� ����� �θ� ���, p: ������ �׸��� �θ���*/
			ptr->left=p->left->left;	//ptr�� ������ ������ left ���� ����
			delete->left=ptr->right;	//ptr�� �θ����� left �� ptr->right �� ����
			ptr->right=p->left->right;	//ptr�� ������ ������ right ���� ����
			
			free(p->left);		// ��� ����
			
			p->left=ptr;				//������ ������ �θ���� ptr ����
			return 0;
		}
		if(p->right==delete){//p -> right �� ������ �׸��� ���
			
			ptr=delete->right; //������ �׸��� ������ ����Ʈ���� �̵�
			
			if(ptr->left==NULL){	//������ �׸��� ������ ��尡 ���� ���� ���̶��
				
				ptr->left=delete->left;
				p->right=ptr;
				free(delete);
				return 0;
			}

			ptr=ptr->left;	
			delete=delete->right;	//ptr�� ���� ��忡 ��ġ
			
			for(;;){	//������ �׸��� ������ ����Ʈ�� �� ���� ���� �� ã��
				if(ptr->left==NULL) break;

				ptr=ptr->left;
				delete=delete->left;
			}

			/*ptr: ���� ���� ��� (������ �׸��� ��ü ���)
			, delete: ���� ���� ����� �θ� ���, p: ������ �׸��� �θ���*/
			ptr->left=p->right->left;	//ptr�� ������ ������ left ���� ����
			delete->left=ptr->right;	//ptr�� �θ����� left �� ptr->right �� ����
			ptr->right=p->right->right;	//ptr�� ������ ������ right ���� ����
			
			free(p->right);		// ��� ����
			
			p->right=ptr;				//������ ������ �θ���� ptr ����
			return 0;
		}

		/*������ ��带 ã�� �̵�*/
		if(p->key==-9999) p=p->left;	//p�� ��ġ�� �������� ��� ���� ����� p->left�� �̵�
		else if(key<p->key)	p=p->left;
		else	p=p->right;
	}


}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()	//stack pop
{
	if(top==-1)	return NULL;	//stack �� ����ִٸ� NULL �� return 
	else return stack[top--]; 	//stack �� value�� �����ϰ� top-=1
}

void push(Node* aNode)	//stack push 
{	if(top==MAX_STACK_SIZE-1) printf("stack is full\n");	//stack�� �� �� �ִٸ� ������ ���
	else stack[++top]=aNode;	//stack�� top�� +1 �ϰ�,  Node�� �ּҸ� �����Ѵ�.
}



Node* deQueue()	//deQueue
{
	if(front==rear)	return 0;	//Queue�� ����ִٸ� return 0
	else return queue[++front];	//front+=1, front�� ����Ű�� �� return 
}

void enQueue(Node* aNode)	//enQueue
{
	if(rear==MAX_QUEUE_SIZE-1)	printf("queue is full\n");	//Queue�� �� ���ִٸ� ������ ���
	else queue[++rear]=aNode;	// rear+=1, aNode�� �ּҸ� Queue�� ����
}

void printStack(){

}


Node* searchIterative(Node* head, int key)
{
	Node* p=head->left;
	while(p){//p�� NULL�� �� �� ���� �ݺ� -> ���Ҹ� ������ �����Ͽ��� ��
		if(key==p->key) return p;	//key�� ��ġ�ϴ� ���Ҹ� ã���� �ش�Ǵ� �ּҸ� ��ȯ
		if(key<p->key)	//key ���� ������ ������ ������
			p=p->left;	//���� ����Ʈ���� �̵�
		else
			p=p->right;	//key�� ������ ������ ũ�� ������ ����Ʈ���� �̵�
	}
	return NULL; //�ݺ��� �ȿ��� �ش�Ǵ� ���� ã�� �� �����Ƿ� NULL ��ȯ
}