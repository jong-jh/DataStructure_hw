/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function���� ���� */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
	printf("------------2018038051    ������-------------");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

/*selection Sort
index�� ���� min �� ���� ������ min���� minindex�� �ش� index�� ��ü�Ѵ�.
�ּҰ��� �����ѵ�, �迭�� �� ĭ �̵��ϰ�, �ּҰ��� ã�� �����ϴ� ������ �ݺ��Ѵ�.
*/
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];		//�ּҰ� ��ü
				minindex = j;	//�ּҰ� �ڸ� ��ü
			}
		}
		a[minindex] = a[i];		//ã�� min �� i �� swap
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* insertionSort
���Ե� ���ο� ���� ���� ������ ��, ������ �����Ѵ�. ���Ե� ������ ���� ũ�ٸ� ���������� �� ĭ �̵��ϰ� �ǰ�,
���Ե� ������ ���ų� ���� ���� ���� �� ���� Ȥ�� �� ���ʿ� �ٴٸ� �� ���� �ݺ��Ѵ�. �ݺ��� ��ġ�� ���� �����Ѵ�.
*/
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];	//���Ե� ��
		j = i;		//�̹� ���ĵ� �κ� ��ŵ
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];	//�� ĭ �ڷ� �̵�
			j--;
		}
		a[j] = t;	//���ο� ���� ����
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}
/*bubble Sort
�迭�� �� ĭ�� �̵��ϸ� ������ �����Ѵ�. �迭�� ���ʿ� �ִ� ���� �ڽ��� ������ ũ�ٸ� swap�� �� ������������ �����Ѵ�.
*/
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])	//ū ���� �����ʿ� �ִٸ� swap
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}
/*shell Sort 
���������� ������ ������ �����̴�. ���������� �� ĭ�� �񱳸� �ߴٸ� shell sort�� MAX_ARRY_SIZE/2 �� ��ŭ�� ����ŭ ������ ���� �񱳸� �Ѵ�.
����� �� ���� h���� ������ ���ҽ�Ű�鼭 1�� �� �� ���� �ݺ��� �Ѵ�.
*/
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //h �� 1�� �� �� ���� �ݺ�
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)	//h��ŭ�� ������ ������ �������� ����
			{
				v = a[j];	//���Ե� ��
				k = j;
				while (k > h-1 && a[k-h] > v)	//������ �ʿ��ϴٸ�
				{
					a[k] = a[k-h];	//���� h��ŭ ������ �� ���� �̵�
					k -= h;
				}
				a[k] = v;	//����
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}
/*quick Sort
���ذ��� �߽����� ���� �κ����հ� ������ �κ��������� �����Ͽ� ���� ���� �Լ����� ���������Ҹ� �������� �������� �����Ѵ�.
���� �κ��� ���ذ����� ū ���� ã�� �� ����, ������ �κ��� ���ذ����� ���� ���� ã�� �� ���� �̵��� ����, �� ���ҵ��� ���ʰ� ������ �κп� �״�� �ִٸ�
�� �� ������ ��ġ�� swap �Ѵ�. ���ʰ� ������ �κ��� �������� ���� �� ���� �ݺ��� ���� ��, ���ذ��� ���ĵ� ��ġ�� �̵���Ų��.
recursive�ϰ� ���� �κ����հ� ������ �κ����տ� ���ؼ� ������ quicksort �� ���ָ�, ������ ������ �� �κ������� ������ ���Ұ� �ȴ�.
*/
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];	//���� v, ������ ���Ҹ� �����Ѵ�.
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;	//i �� j ���� Ŭ ��, break, //ū ���� ���� �ִٸ� swap �Ѵ�.
			t = a[i];		
			a[i] = a[j];
			a[j] = t;
		}
		//������ ���� �� ���ذ��� ���ĵ� ��ġ�� �̵���Ų��.
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);	//���� �κ������� quicksort ����
		quickSort(a+i+1, n-i-1);	//������ �κ������� ,quicksort
	}


	return 0;
}

/*hastcode �� ��ȯ���ִ� �Լ�
divisino �� Ȱ���� MAX_HASH_TABLE_SIZE�� ���� �������� ��Ŷ���� ����Ѵ�.
*/
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}
/*
hashing function
�����÷� ó���� ���� Linear Probing �� ����Ͽ� ������ ���� �ؽ� ���̺� ��Ŷ�� �˻��Ѵ�.
13���� ��Ŷ�� �ϳ��� ������ hasing table�� �����̴�.
*/
int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	} else {
		hashtable = *ht;	/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)	//����ִ� hashtable �� ��� -1 �� �ʱ�ȭ �Ѵ�.
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];	//
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)	//hashtable �� �ش��ϴ� �ε��� ���� ����ִٸ� ���� ����
		{
			hashtable[hashcode] = key;
		} else 	{	//�浿�� �ִٸ�

			index = hashcode;	//������ hashcode �� ���ο� ������ �ű��

			while(hashtable[index] != -1)	//����ִ� �ڸ��� ���� �� ����
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;	//�ε����� �� ĭ�� �ű��.
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;	//����ִ� �ڸ��� key ���� �����Ѵ�.
		}
	}

	return 0;
}
/*hashing table�� ����� ���� �ּҸ� ��ȯ���ִ� �Լ�*/
int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)	//�ش� �ּҿ� hashcode�� ��Ÿ���� ���� ���ٸ� ��ȯ�Ѵ�.
		return index;

	while(ht[++index] != key)	//ã������ ���� ���� �� ���� index �� 1 ������Ų��.
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



