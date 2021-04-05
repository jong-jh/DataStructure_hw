/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack �댁뿉��? �곗꽑�?��?��, lparen = 0 媛��� ��?�� */
typedef enum{
	lparen = 0,  /* ( �쇱?�� ?��꾪샇 */
	rparen = 9,  /* ) �ㅻ?��履� ?��꾪샇*/
	times = 7,   /* * ??�깆??? */
	divide = 6,  /* / �섎?���� */
	plus = 5,    /* + �㏃??? */
	minus = 4,   /* - 類꾩??? */
	operand = 1 /* �쇱뿰�곗옄 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� ���ν븯�� 諛곗�? */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix濡� 蹂�寃쎈�? ?��몄옄�댁?�� ���ν븯�� 諛곗�? */
char postfixStack[MAX_STACK_SIZE];	/* postfix濡� 蹂��섏?�� �꾪�? �꾩?���� �ㅽ�? */
int evalStack[MAX_STACK_SIZE];		/* ??�꾩궛��? �꾪�? �꾩?���� �ㅽ�? */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ??�꾩�? 寃곌?��?���? ���� */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression�� �낅?��諛쏅?����.
 * infixExp�먮?�� �낅?���� 媛�?�쓣 ���ν븳��.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * ?��몄옄�섎굹瑜�? �꾨?��諛쏆�?, postfixExp�� ?��붽�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� �����Ѵ�.
 */
void toPostfix()
{
	/* infixExp �� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* ���� �ϳ��� �ӽ÷� �����ϱ� ���� ���� */
	int key=0; /*��ȣ�� ó���� ���� ����*/
	int i=0;
	/* exp�� �������Ѱ��鼭 ���ڸ� �а� postfix�� ���� */
	while(*(exp+i) != '\0')
	{	
		/* () ó�� �˰��� : ( �� ������ ������ push�� ���ص�, (�� ���ִ� stack�� top ���� key �ȿ� ��Ƶд�.
		//	�� �� ��������� ���� stack�� �����ڵ��� ���̰� �ǰ�, )�� ���� ��, top�� key�� ������ �� ���� stack���� ������ pop���� �� (�� ����ó�� ���ش�.
		*/
		if(getPriority(*(exp+i))==0){// lparen �� ���
			key=postfixStackTop;	// lparen �� ���� ���� top ���� ������ ��.
			postfixPush(*(exp+i));	// lparen �� push ���ش�.
		}
		else if(getPriority(*(exp+i))==1){	//operand�� ��� �ٷ� Output
			x=*(exp+i); 	
			charCat(&x); }	//x�� ����� operand�� �ٷ� ������ش�.
		
		else if(getPriority(*(exp+i))==9){// rparen �� ���
			postfixStack[key+1]='\0';	// lparen ����
			for(int j=0;postfixStackTop>key;j++){	//ǥ���ص� �������� stack�� �ִ� ������ pop
			x=postfixPop();
			charCat(&x);}
			
		/*��������� ����Ͽ� stack ���� ������ ���� �ڽ��� �켱������ ���� ��� �ٷ� ���, �ڽ��� �� Ŭ ��� stack�� push ���ش�.
		//	�켱������ ���� ���(������ �������� ���) push & pop �� ������ ���ش�.
		*/
		}
		else if(getPriority(*(exp+i))==getPriority(postfixStack[postfixStackTop])){//�켱������ ���� ����� ��
			postfixPush(*(exp+i));	//push & pop
			x=postfixPop(); 
			charCat(&x); 
		}
		else if(getPriority(*(exp+i)) > getPriority(postfixStack[postfixStackTop])){//�켱������ �� Ŭ ���
			postfixPush(*(exp+i));	//push ���ش�.
		}
		else if(getPriority(*(exp+i)) < getPriority(postfixStack[postfixStackTop])){//�켱������ �� ���� ���
			x=*(exp+i); 
			charCat(&x);
		}
		i++;	//i ���� �������� ���� ���ڸ� Ȯ���Ѵ�.
	}
	/*�ݺ����� �������� ��, stack �� �׿��ִ� token���� ��� pop �Ѵ�.*/
	for(;;){if(postfixStackTop==-1) break;	//top���� -1 �̸� Ż��
				else x=postfixPop(); charCat(&x);
			}

}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
	
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{	
	char *exp = postfixExp;
	int x=0,y=0; //���꿡 �ʿ��� �ǿ����ڸ� ���� ���� 
	int i=0;
	
	/* postfixExp, evalStack �� �̿��� ��� */
	while(*(exp+i) != '\0'){
		if(getPriority(*(exp+i))==1){	//operand�� ��� stack �� push
			evalPush(*(exp+i)-48);}		//ASCII �ڵ� ���� �ޱ� ������ -48�� ���־�� �Ѵ�.

		else if(*(exp+i)=='+'){		//+ �������� ���
			y=evalPop(evalStack[evalStackTop]);	//���꿡 �ʿ��� ������ pop ���ش�.
			x=evalPop(evalStack[evalStackTop-1]);
			evalPush(x+y);	//������ �� ���� push ���ش�.
		}
		else if(*(exp+i)=='-'){		//- �������� ���
			y=evalPop(evalStack[evalStackTop]);	//���꿡 �ʿ��� ������ pop ���־� ���� x,y�� ��´�.
			x=evalPop(evalStack[evalStackTop-1]);
			evalPush(x-y);		//������ ������ push ���ش�.
		}
		else if(*(exp+i)=='*'){		//* �������� ���
			y=evalPop(evalStack[evalStackTop]);
			x=evalPop(evalStack[evalStackTop-1]);
			printf("\nx*y= %d\n",x*y);
			evalPush(x*y);
		}
		else if(*(exp+i)=='/'){		// / �������� ���
			y=evalPop(evalStack[evalStackTop]);
			x=evalPop(evalStack[evalStackTop-1]);
			evalPush(x/y);
		}

		i++;	//i���� �������� ���� ���ڸ� Ȯ���Ѵ�.
	}
	evalResult=evalPop(evalStackTop);	//evalStack�� ����� ���� ���������Ƿ�, ������� pop ���ش�.

}
