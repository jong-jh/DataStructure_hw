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

/* stack ï¿½ëŒë¿‰ï¿½ï¿? ï¿½ê³—ê½‘ï¿½?’–?ž, lparen = 0 åª›ï¿½ï¿½ï¿½ ï¿½ï¿½?“¬ */
typedef enum{
	lparen = 0,  /* ( ï¿½ì‡±? ?„¿ê¾ªìƒ‡ */
	rparen = 9,  /* ) ï¿½ã…»?…¨ï§Ÿï¿½ ?„¿ê¾ªìƒ‡*/
	times = 7,   /* * ??¨ê¹†??? */
	divide = 6,  /* / ï¿½ì„Ž?‹“ï¿½ï¿½ */
	plus = 5,    /* + ï¿½ãƒ??? */
	minus = 4,   /* - ï§ê¾©??? */
	operand = 1 /* ï¿½ì‡±ë¿°ï¿½ê³—ì˜„ */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expressionï¿½ï¿½ ï¿½ï¿½ï¿½Î½ë¸¯ï¿½ï¿½ è«›ê³—ë¿? */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfixæ¿¡ï¿½ è¹‚ï¿½å¯ƒìŽˆë§? ?‡¾ëª„ì˜„ï¿½ëŒ?“£ ï¿½ï¿½ï¿½Î½ë¸¯ï¿½ï¿½ è«›ê³—ë¿? */
char postfixStack[MAX_STACK_SIZE];	/* postfixæ¿¡ï¿½ è¹‚ï¿½ï¿½ì„?“£ ï¿½ê¾ªë¹? ï¿½ê¾©?Š‚ï¿½ï¿½ ï¿½ã…½ê¹? */
int evalStack[MAX_STACK_SIZE];		/* ??¨ê¾©ê¶›ï¿½ï¿? ï¿½ê¾ªë¹? ï¿½ê¾©?Š‚ï¿½ï¿½ ï¿½ã…½ê¹? */

int postfixStackTop = -1;  /* postfixStackï¿½ï¿½ top */
int evalStackTop = -1;	   /* evalStackï¿½ï¿½ top */

int evalResult = 0;	   /* ??¨ê¾©ê¶? å¯ƒê³Œ?‚µ?‘œï¿? ï¿½ï¿½ï¿½ï¿½ */

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
 * infix expressionï¿½ï¿½ ï¿½ë‚…? °è«›ì…?’—ï¿½ï¿½.
 * infixExpï¿½ë¨®?’— ï¿½ë‚…? °ï¿½ï¿½ åª›ë?ªì“£ ï¿½ï¿½ï¿½Î½ë¸³ï¿½ï¿½.
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
 * ?‡¾ëª„ì˜„ï¿½ì„Žêµ¹ç‘œï¿? ï¿½ê¾¨?––è«›ì†ë¸?, postfixExpï¿½ï¿½ ?•°ë¶½ï¿½
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExpÀÇ ¹®ÀÚ¸¦ ÇÏ³ª¾¿ ÀÐ¾î°¡¸é¼­ stackÀ» ÀÌ¿ëÇÏ¿© postfix·Î º¯°æÇÑ´Ù.
 * º¯°æµÈ postfix´Â postFixExp¿¡ ÀúÀåÇÑ´Ù.
 */
void toPostfix()
{
	/* infixExp ÀÇ ¹®ÀÚ ÇÏ³ª¾¿À» ÀÐ±âÀ§ÇÑ Æ÷ÀÎÅÍ */
	char *exp = infixExp;
	char x; /* ¹®ÀÚ ÇÏ³ª¸¦ ÀÓ½Ã·Î ÀúÀåÇÏ±â À§ÇÑ º¯¼ö */
	int key=0; /*°ýÈ£°ª Ã³¸®¸¦ À§ÇÑ º¯¼ö*/
	int i=0;
	/* exp¸¦ Áõ°¡½ÃÄÑ°¡¸é¼­ ¹®ÀÚ¸¦ ÀÐ°í postfix·Î º¯°æ */
	while(*(exp+i) != '\0')
	{	
		/* () Ã³¸® ¾Ë°í¸®Áò : ( ¸¦ ¸¸³ª¸é ¹«Á¶°Ç push¸¦ ÇØÁØµÚ, (°¡ µé¾î°¡ÀÖ´Â stackÀÇ top °ªÀ» key ¾È¿¡ ´ã¾ÆµÐ´Ù.
		//	±× µÚ ¿¬»ê¼øÀ§¿¡ ÀÇÇØ stack¿¡ ¿¬»êÀÚµéÀÌ ½×ÀÌ°Ô µÇ°í, )¸¦ ¸¸³¯ ¶§, topÀÌ key¿¡ µµ´ÞÇÒ ¶§ ±îÁö stack¾ÈÀÇ °ªµéÀ» popÇØÁØ µÚ (´Â °ø¹éÃ³¸® ÇØÁØ´Ù.
		*/
		if(getPriority(*(exp+i))==0){// lparen ÀÏ °æ¿ì
			key=postfixStackTop;	// lparen ÀÌ µé¾î¿Ã ¶§ÀÇ top °ªÀ» ÀúÀåÇØ µÒ.
			postfixPush(*(exp+i));	// lparen À» push ÇØÁØ´Ù.
		}
		else if(getPriority(*(exp+i))==1){	//operandÀÏ °æ¿ì ¹Ù·Î Output
			x=*(exp+i); 	
			charCat(&x); }	//x¿¡ ´ã°ÜÁø operand¸¦ ¹Ù·Î Ãâ·ÂÇØÁØ´Ù.
		
		else if(getPriority(*(exp+i))==9){// rparen ÀÏ °æ¿ì
			postfixStack[key+1]='\0';	// lparen »èÁ¦
			for(int j=0;postfixStackTop>key;j++){	//Ç¥½ÃÇØµÐ ÁöÁ¡±îÁö stack¿¡ ÀÖ´Â °ªµéÀ» pop
			x=postfixPop();
			charCat(&x);}
			
		/*¿¬»ê¼øÀ§¸¦ °í·ÁÇÏ¿© stack ¾ÈÀÇ ¿¬»êÀÚ º¸´Ù ÀÚ½ÅÀÇ ¿ì¼±¼øÀ§°¡ ÀÛÀ» °æ¿ì ¹Ù·Î Ãâ·Â, ÀÚ½ÅÀÌ ´õ Å¬ °æ¿ì stack¿¡ push ÇØÁØ´Ù.
		//	¿ì¼±¼øÀ§°¡ °°À» °æ¿ì(µ¿ÀÏÇÑ ¿¬»êÀÚÀÏ °æ¿ì) push & pop À» µ¿½ÃÇØ ÇØÁØ´Ù.
		*/
		}
		else if(getPriority(*(exp+i))==getPriority(postfixStack[postfixStackTop])){//¿ì¼±¼øÀ§°¡ °°Àº °æ¿ìÀÏ ¶§
			postfixPush(*(exp+i));	//push & pop
			x=postfixPop(); 
			charCat(&x); 
		}
		else if(getPriority(*(exp+i)) > getPriority(postfixStack[postfixStackTop])){//¿ì¼±¼øÀ§°¡ ´õ Å¬ °æ¿ì
			postfixPush(*(exp+i));	//push ÇØÁØ´Ù.
		}
		else if(getPriority(*(exp+i)) < getPriority(postfixStack[postfixStackTop])){//¿ì¼±¼øÀ§°¡ ´õ ÀÛÀ» °æ¿ì
			x=*(exp+i); 
			charCat(&x);
		}
		i++;	//i °ªÀ» Áõ°¡½ÃÄÑ ´ÙÀ½ ¹®ÀÚ¸¦ È®ÀÎÇÑ´Ù.
	}
	/*¹Ýº¹¹®À» ºüÁ®³ª°£ µÚ, stack ¿¡ ½×¿©ÀÖ´Â tokenµéÀ» ¸ðµÎ pop ÇÑ´Ù.*/
	for(;;){if(postfixStackTop==-1) break;	//top°ªÀÌ -1 ÀÌ¸é Å»Ãâ
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
	int x=0,y=0; //¿¬»ê¿¡ ÇÊ¿äÇÑ ÇÇ¿¬»çÀÚ¸¦ ¹ÞÀ» º¯¼ö 
	int i=0;
	
	/* postfixExp, evalStack À» ÀÌ¿ëÇÑ °è»ê */
	while(*(exp+i) != '\0'){
		if(getPriority(*(exp+i))==1){	//operandÀÏ °æ¿ì stack ¿¡ push
			evalPush(*(exp+i)-48);}		//ASCII ÄÚµå °ªÀ» ¹Þ±â ¶§¹®¿¡ -48À» ÇØÁÖ¾î¾ß ÇÑ´Ù.

		else if(*(exp+i)=='+'){		//+ ¿¬»êÀÚÀÏ °æ¿ì
			y=evalPop(evalStack[evalStackTop]);	//¿¬»ê¿¡ ÇÊ¿äÇÑ °ªµéÀ» pop ÇØÁØ´Ù.
			x=evalPop(evalStack[evalStackTop-1]);
			evalPush(x+y);	//¿¬»êÀ» ÇÑ °ªÀ» push ÇØÁØ´Ù.
		}
		else if(*(exp+i)=='-'){		//- ¿¬»êÀÚÀÏ °æ¿ì
			y=evalPop(evalStack[evalStackTop]);	//¿¬»ê¿¡ ÇÊ¿äÇÑ °ªµéÀ» pop ÇØÁÖ¾î º¯¼ö x,y¿¡ ´ã´Â´Ù.
			x=evalPop(evalStack[evalStackTop-1]);
			evalPush(x-y);		//¿¬»êÇÑ °ªµéÀ» push ÇØÁØ´Ù.
		}
		else if(*(exp+i)=='*'){		//* ¿¬»êÀÚÀÏ °æ¿ì
			y=evalPop(evalStack[evalStackTop]);
			x=evalPop(evalStack[evalStackTop-1]);
			printf("\nx*y= %d\n",x*y);
			evalPush(x*y);
		}
		else if(*(exp+i)=='/'){		// / ¿¬»êÀÚÀÏ °æ¿ì
			y=evalPop(evalStack[evalStackTop]);
			x=evalPop(evalStack[evalStackTop-1]);
			evalPush(x/y);
		}

		i++;	//i°ªÀ» Áõ°¡½ÃÄÑ ´ÙÀ½ ¹®ÀÚ¸¦ È®ÀÎÇÑ´Ù.
	}
	evalResult=evalPop(evalStackTop);	//evalStack¿¡ ¿¬»êµÈ °ªÀÌ ³²¾ÆÀÖÀ¸¹Ç·Î, °á°ú°ªÀ» pop ÇØÁØ´Ù.

}
