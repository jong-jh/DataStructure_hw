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
	printf("---2018038051 정종현---\n\n");
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



void inorderTraversal(Node* ptr)
{
	if(ptr){
		inorderTraversal(ptr->left);
		printf("[%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr){
		printf("[%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

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
	Node *temp = (Node *)malloc(sizeof(Node)); //새로 삽입할 노드 생성
	temp->key = key; temp->left=temp->right=NULL;
	
	if(head->left==NULL){//tree가 빈 트리라면 헤더노드의 left에 temp 삽입
		head->left=temp;
		return 0;
	}

	while (1)
	{
		if (key < p->key)
		{
			if(p->left==NULL)	{p->left=temp; break;}
			else 	p=p->left;
		}
		else if (key > p->key)
		{
			if(p->right==NULL)	{p->right=temp; break;}
			else 	p = p->right;
		}
	}
	return 0;
}


int deleteLeafNode(Node* head, int key)
{

}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr) return NULL;	//tree 의 끝에 닿았을 경우
	if(key==ptr->key) return ptr;	//key값을 만족하는 주소를 찾았을 경우
	if(key<ptr->key)		//key가 원소의 key보다 작을 경우
		return searchRecursive(ptr->left,key);	//왼쪽 서브트리로 이동한다
	else
		return searchRecursive(ptr->right,key);	//오른쪽 서브트리로 이동한다.
}

Node* searchIterative(Node* head, int key)
{
	Node* p=head->left;
	while(p){//p가 NULL이 될 때 까지 반복 -> 원소를 끝까지 추적하였을 때
		if(key==p->key) return p;	//key와 일치하는 원소를 찾으면 해당되는 주소를 바환
		if(key<p->key)	//key 값이 원소의 값보다 작으면
			p=p->left;	//왼쪽 서브트리로 이동
		else
			p=p->right;	//key가 원소의 값보다 크면 오른쪽 서브트리로 이동
	}
	return NULL; //반복문 안에서 해당되는 값을 찾지 못 했으므로 NULL 반환
}


int freeBST(Node* head)
{

}





