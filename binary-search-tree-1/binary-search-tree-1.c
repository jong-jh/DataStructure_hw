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
	printf("---2018038051 มคมพว๖---\n\n");
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
ม฿ภงผ๘ศธ, ฟ?ยสภป ธีภ๚ นๆนฎวั ตฺ, ตนพฦฟร ถง ฐชภป รโทยวฯฐํ ฟภธฅยสภธทฮ ภฬตฟวัดู.
*/
void inorderTraversal(Node* ptr)
{
	if(ptr){
		inorderTraversal(ptr->left);		//ฟ?ยส ผญบ๊ฦฎธฎทฮ ภฬตฟ
		printf("[%d] ", ptr->key);			//ฟ?ยส ผญบ๊ฦฎธฎธฆ ณชฟภธ้ visit
		inorderTraversal(ptr->right);		//ฟภธฅยส ผญบ๊ฦฎธฎทฮ ภฬตฟ ศฤ พีผฑ ณปฟ๋ น?บน
	}
}
/*
ภ?ภงผ๘ศธ, นๆนฎวฯฐิ ตวธ้ ฐชภป ธีภ๚ รโทยวุมุดู.
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
ศฤภง ผ๘ศธ, ฟ?ยส ฟภธฅยส ณ๋ตๅธฆ ดู นๆนฎ ศฤฟก ฐชภป รโทยวัดู.
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
	Node *temp = (Node *)malloc(sizeof(Node)); //ป๕ทฮ ป๐ภิวา ณ๋ตๅ ป?ผบ
	temp->key = key; temp->left=temp->right=NULL;
	
	if(head->left==NULL){//treeฐก บ๓ ฦฎธฎถ๓ธ้ ว์ด๕ณ๋ตๅภว leftฟก temp ป๐ภิ
		head->left=temp;
		return 0;
	}

	while (1)
	{
		if (key < p->key)	//key ฐก ฟ๘ผาภว ฐชบธดู ภ?ภธธ้
		{
			if(p->left==NULL)	{p->left=temp; break;}	//ฟ?ยส ผญบ๊ฦฎธฎทฮ ภฬตฟ , ธธพเ บ๑พ๎ภึดูธ้ treeฟก ป๐ภิ
			else 	p=p->left;
		}
		else if (key > p->key)	//keyฐก ฟ๘ผาภว ฐชบธดู ลฉธ้ ฟภธฅยส ผญบ๊ฦฎธฎทฮ ภฬตฟ ศฤ บ๑พ๎ภึดูธ้ treeฟก ป๐ภิ
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
	
	if(!deleteP){//ป่มฆวฯทมดย ฐชภฬ treeฟก พ๘ภธธ้
		printf("key is not in tree\n");
		return 0;
	}
	if(deleteP->left!=NULL||deleteP->right!=NULL){	//ธธพเ ธฎวมณ๋ตๅฐก พฦดา ฐๆฟ์ฟกดย left ฟอ right ฐก NULLภฬ พฦดฯนวทฮ
		printf("the node [%d] is not a leaf\n");	//ดูภฝภป รโทยวุมุดู.
		return 0;
	}
	
	Node* p=head->left;		//ธธพเ ว์ด๕ณ๋ตๅภว leftฟก ฟฌฐแตศ ณ๋ตๅฐก ป่มฆวา ณ๋ตๅถ๓ธ้ ม๏ treeฟก ณ๋ตๅฐก วฯณชน?ฟก พ๘ดูธ้
	if(p==deleteP){head->left=NULL; free(deleteP); return 0;}	//ว์ด๕ณ๋ตๅภว leftธฆ NULLทฮ วฯฐํ ป่มฆวา ณ๋ตๅภว ธ?ธ๐ธฎ วุมฆ วุมุดู.

	while(1){
		if(p->left==deleteP){	
			p->left=NULL; free(deleteP); break;	//บฮธ๐ณ๋ตๅภว linkธฆ NULLทฮ วุมึฐํ, ป่มฆวา ณ๋ตๅภว ธ?ธ๐ธฎธฆ วุมฆวัดู.
		}
		if(p->right==deleteP){
			p->right=NULL; free(deleteP); break;
		}
		if(key<p->key)	//key ฐชภฬ ฟ๘ผาภว ฐชบธดู ภ?ภธธ้
			p=p->left;	//ฟ?ยส ผญบ๊ฦฎธฎทฮ ภฬตฟ
		else
			p=p->right;	//keyฐก ฟ๘ผาภว ฐชบธดู ลฉธ้ ฟภธฅยส ผญบ๊ฦฎธฎทฮ ภฬตฟ
	}

	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr) return NULL;	//tree ภว ณกฟก ด๊พาภป ฐๆฟ์
	if(key==ptr->key) return ptr;	//keyฐชภป ธธมทวฯดย มึผาธฆ รฃพาภป ฐๆฟ์
	if(key<ptr->key)		//keyฐก ฟ๘ผาภว keyบธดู ภ?ภป ฐๆฟ์
		return searchRecursive(ptr->left,key);	//ฟ?ยส ผญบ๊ฦฎธฎทฮ ภฬตฟวัดู
	else
		return searchRecursive(ptr->right,key);	//ฟภธฅยส ผญบ๊ฦฎธฎทฮ ภฬตฟวัดู.
}

Node* searchIterative(Node* head, int key)
{
	Node* p=head->left;
	while(p){//pฐก NULLภฬ ตษ ถง ฑ๎ม๖ น?บน -> ฟ๘ผาธฆ ณกฑ๎ม๖ ร฿ภ๛วฯฟดภป ถง
		if(key==p->key) return p;	//keyฟอ ภฯฤกวฯดย ฟ๘ผาธฆ รฃภธธ้ วุด็ตวดย มึผาธฆ นูศฏ
		if(key<p->key)	//key ฐชภฬ ฟ๘ผาภว ฐชบธดู ภ?ภธธ้
			p=p->left;	//ฟ?ยส ผญบ๊ฦฎธฎทฮ ภฬตฟ
		else
			p=p->right;	//keyฐก ฟ๘ผาภว ฐชบธดู ลฉธ้ ฟภธฅยส ผญบ๊ฦฎธฎทฮ ภฬตฟ
	}
	return NULL; //น?บนนฎ พศฟกผญ วุด็ตวดย ฐชภป รฃม๖ ธ๘ ว฿ภธนวทฮ NULL น?ศฏ
}
/*
postorderTraversal วิผ๖ธฆ ล๋วุ recursiveวฯฐิ treeธฆ นๆนฎวฯธ้ผญ 
treeภว ฟ๘ผาต้ภป ธ?ธ๐ธฎ วุมฆ วุมุดู.
*/

int freeBST(Node* head)
{
	if(head){
		freeBST(head->left); 
		if(head->key==-9999) {/*printf("free head!");*/ free(head); return 0;}	//treeภว ธ๐ต็ นๆนฎภป ณกณฝ ตฺ headทฮ ตนพฦฟิภป ถง, head->rightฐก recursiveตวธ้
		//นซวัวฯฐิ วิผ๖ฐก น?บนตวฑโ ถงนฎฟก, head->left นูทฮ ดูภฝฟก headธฆ ธ?ธ๐ธฎ วุมฆ วุพ฿วัดู.
		
		freeBST(head->right);
		free(head);	/*printf("free! memory\n")*/;	//ธ?ธ๐ธฎ วุมฆ
	}
}
