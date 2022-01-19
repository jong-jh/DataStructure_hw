/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("---2018038051 ������---\n\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}

/*
������ȸ, ������ ���� �湮�� ��, ���ƿ� �� ���� ����ϰ� ���������� �̵��Ѵ�.
*/
void inorderTraversal(Node* ptr)
{
	if(ptr){
		inorderTraversal(ptr->left);		//���� ����Ʈ���� �̵�
		printf("[%d] ", ptr->key);			//���� ����Ʈ���� ������ visit
		inorderTraversal(ptr->right);		//������ ����Ʈ���� �̵� �� �ռ� ���� �ݺ�
	}
}
/*
������ȸ, �湮�ϰ� �Ǹ� ���� ���� ������ش�.
*/
void preorderTraversal(Node* ptr)
{
	if(ptr){
		printf("[%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}
/*
���� ��ȸ, ���� ������ ��带 �� �湮 �Ŀ� ���� ����Ѵ�.
*/
void postorderTraversal(Node* ptr)
{
	if(ptr){
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("[%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node *p = head->left;
	Node *temp = (Node *)malloc(sizeof(Node)); //���� ������ ��� ����
	temp->key = key; temp->left=temp->right=NULL;
	
	if(head->left==NULL){//tree�� �� Ʈ����� �������� left�� temp ����
		head->left=temp;
		return 0;
	}

	while (1)
	{
		if (key < p->key)	//key �� ������ ������ ������
		{
			if(p->left==NULL)	{p->left=temp; break;}	//���� ����Ʈ���� �̵� , ���� ����ִٸ� tree�� ����
			else 	p=p->left;
		}
		else if (key > p->key)	//key�� ������ ������ ũ�� ������ ����Ʈ���� �̵� �� ����ִٸ� tree�� ����
		{
			if(p->right==NULL)	{p->right=temp; break;}
			else 	p = p->right;
		}
	}
	return 0;
}


int deleteLeafNode(Node* head, int key)
{
	Node* deleteP=searchIterative(head,key);
	
	if(!deleteP){//�����Ϸ��� ���� tree�� ������
		printf("key is not in tree\n");
		return 0;
	}
	if(deleteP->left!=NULL||deleteP->right!=NULL){	//���� ������尡 �ƴ� ��쿡�� left �� right �� NULL�� �ƴϹǷ�
		printf("the node [%d] is not a leaf\n");	//������ ������ش�.
		return 0;
	}
	
	Node* p=head->left;		//���� �������� left�� ����� ��尡 ������ ����� �� tree�� ��尡 �ϳ��ۿ� ���ٸ�
	if(p==deleteP){head->left=NULL; free(deleteP); return 0;}	//�������� left�� NULL�� �ϰ� ������ ����� �޸� ���� ���ش�.

	while(1){
		if(p->left==deleteP){	
			p->left=NULL; free(deleteP); break;	//�θ����� link�� NULL�� ���ְ�, ������ ����� �޸𸮸� �����Ѵ�.
		}
		if(p->right==deleteP){
			p->right=NULL; free(deleteP); break;
		}
		if(key<p->key)	//key ���� ������ ������ ������
			p=p->left;	//���� ����Ʈ���� �̵�
		else
			p=p->right;	//key�� ������ ������ ũ�� ������ ����Ʈ���� �̵�
	}

	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr) return NULL;	//tree �� ���� ����� ���
	if(key==ptr->key) return ptr;	//key���� �����ϴ� �ּҸ� ã���� ���
	if(key<ptr->key)		//key�� ������ key���� ���� ���
		return searchRecursive(ptr->left,key);	//���� ����Ʈ���� �̵��Ѵ�
	else
		return searchRecursive(ptr->right,key);	//������ ����Ʈ���� �̵��Ѵ�.
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
/*
postorderTraversal �Լ��� ���� recursive�ϰ� tree�� �湮�ϸ鼭 
tree�� ���ҵ��� �޸� ���� ���ش�.
*/

int freeBST(Node* head)
{
	if(head){
		freeBST(head->left); 
		if(head->key==-9999) {/*printf("free head!");*/ free(head); return 0;}	//tree�� ��� �湮�� ���� �� head�� ���ƿ��� ��, head->right�� recursive�Ǹ�
		//�����ϰ� �Լ��� �ݺ��Ǳ� ������, head->left �ٷ� ������ head�� �޸� ���� �ؾ��Ѵ�.
		
		freeBST(head->right);
		free(head);	/*printf("free! memory\n")*/;	//�޸� ����
	}
}
