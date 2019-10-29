#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include <string>

#define TITLE "再帰的計算ツール (双方向リスト版)"
#define SEPARATOR "--------------------------------------------"
#define DATA_CNT 5
#define DATA_MAX_LENGTH 12
#define PRINT_COUNT(cnt) printf("%dつ目の数値を入力してください。\n", cnt)
#define PRINT_NEW_ELEMENT(index, value) printf("リストに要素%dのメモリ領域を確保　値： %s\n", index, value)
#define PRINT_FREE_ELEMENT(index, value) printf("リストから要素%dのメモリ領域を解放　値： %s\n", index, value)
#define PRINT_CALC_RESULT(cnt, type, result) printf("入力した%dつの数値の%sは %d です。\n", cnt, type, result)
#define EXISTS_ELEMENT(elem) (elem != NULL ? true : false)
#define FREE(p){free(p); p = NULL;}

typedef struct LIST  
{
	int index;
	char value[DATA_MAX_LENGTH];
	struct LIST* prev;
	struct LIST* next;

}LINKED_LIST;

typedef struct 
{
	LINKED_LIST* elem;
	char number[DATA_MAX_LENGTH];
}VALUE_LIST;

typedef enum 
{
	ENUM_HEAD_POS,
	ENUM_TAIL_POS
};

int getData(VALUE_LIST*);
bool isNumber(const char*);
bool execProcess(VALUE_LIST*);
int recursiveA(LINKED_LIST*);
int recursiveB(LINKED_LIST*);
LINKED_LIST* addEelement(LINKED_LIST*, const char*);
LINKED_LIST* selectElement(LINKED_LIST*, int);
void freeElement(VALUE_LIST*);
int (*fun[])(LINKED_LIST*) = {recursiveA,recursiveB};

//-----------------------------------------
int main()
{
	LINKED_LIST lkl;
	VALUE_LIST  vll = {0};
	while(true)
	{
		if(getData(&vll) == -1)
		{
			printf(SEPARATOR"\n");
			printf("不正な入力です。 終了します。\n");
			
			break;
		}
		
		if(execProcess(&vll) == false)
		{
			printf(SEPARATOR"\n");
			printf("終了します。\n");
			break;
		}
		freeElement(&vll);
	}
	
	freeElement(&vll);
	
	system("pause");
	
	return 0;
}

int getData(VALUE_LIST* vll)
{ 
	LINKED_LIST * lkl = (LINKED_LIST*)malloc(sizeof(LINKED_LIST));
	
	char temp[5] = {0};
	printf("\n");
	printf(TITLE"\n");
	printf(SEPARATOR"\n");
	//--------------------------------------
		for (int i = 0; i < DATA_CNT ; i++)
		{
			PRINT_COUNT(i + 1);
			scanf("%s", temp);
			
			if(isNumber(temp) == false)
			{
				
				return -1;
			}
			
			vll->elem = addEelement(vll->elem, temp);

			PRINT_NEW_ELEMENT(i + 1, temp); 

		}
	
	//------------------------------------
		do 
		{
			//printf(TITLE"\n");
			printf(SEPARATOR"\n");
			printf("1 : 総和\n");
			printf("2 : 総乗\n");
			//printf(TITLE"\n\n");
			printf(SEPARATOR"\n");
			printf("処理番号を入力してください。\n>");
			scanf("%s", &vll->number);

			if (isNumber(vll->number) == false)
			{	
				return -1;
			}
			
		}while (1 > atoi(vll->number) || atoi(vll->number) > 2);

		return 0;
}

//----------------------------------------- 
bool isNumber(const char* answer)
{
	int i = 1;	

		if (answer[0] != '-' &&  !('0' <= answer[0] && answer[0] <= '9'))
		{
			return false;
		}
		while (answer[i] != '\0' )
		{
			if(!('0' <= answer[i] && answer[i] <= '9'))
			{
				return false;
			}
			
			i++;
		}
		return true;	
}

//-----------------------------------------------------------
LINKED_LIST* addEelement(LINKED_LIST* p, const char* answer)
{
	LINKED_LIST* lkl = (LINKED_LIST*)malloc(sizeof(LINKED_LIST));
	LINKED_LIST* list = p;
	if(p == NULL)	{
			lkl->index = 1;
			lkl->prev = NULL;
			lkl->next = NULL;
				
			strcpy(lkl->value,answer);
			p = lkl;
	}else{
		while (list->next != NULL)
		{
			list = list->next;
		}
	
		lkl->index = list->index + 1;
		strcpy(lkl->value,answer);
		lkl->prev = list;
		lkl->next = NULL;
		list->next = lkl;
				
	}

	return p;
}

//-----------------------------------------
LINKED_LIST* selectElement(LINKED_LIST* lkl, int no)
{
	if(no == ENUM_TAIL_POS)
	{
		while (lkl->next != NULL)
		{
			lkl = lkl->next;
		}
	}
	if(no == ENUM_HEAD_POS)
	{
		while (lkl->prev != NULL)
		{
			lkl = lkl->prev;
		}
	}

	return lkl;
}

//-----------------------------------------
void freeElement(VALUE_LIST* lkl)
{
	LINKED_LIST *temp = NULL;
	if(EXISTS_ELEMENT(lkl) == false)
	{
		return;
	}
	lkl->elem = selectElement(lkl->elem, ENUM_HEAD_POS);
	while (lkl->elem != NULL)
	{
		temp = lkl->elem->next;
		PRINT_FREE_ELEMENT(lkl->elem->index,lkl->elem->value);
		FREE(lkl->elem->prev);
		lkl->elem = temp;
	}
	*lkl->number = NULL;
}

//-----------------------------------------
int recursiveA(LINKED_LIST*lkl)
{
	int sum = 0;

	if (lkl->prev == NULL)
	{
		sum = atoi(lkl->value);
	}
	else
	{
		sum = atoi(lkl->value) + recursiveA(lkl->prev);
	}

	return sum;
}

//-----------------------------------------
int recursiveB(LINKED_LIST*lkl)
{
	int sum = 1;

	if (lkl->prev == NULL)
	{
		sum = atoi(lkl->value);
	}
	else
	{
		sum = atoi(lkl->value) * recursiveB(lkl->prev); 
	}

	return sum;
}

//-----------------------------------------
bool execProcess(VALUE_LIST* vll)
{
	int (*fun[])(LINKED_LIST*) = {recursiveA,recursiveB};
	vll->elem = selectElement(vll->elem,1);
	PRINT_CALC_RESULT(DATA_CNT,atoi(vll->number) == 1 ? "総和" : "総乗",(*fun[atoi(vll->number) - 1])(vll->elem));	
	char check[5] = {0};

	do
	{
		printf("もう一度計算しますか？(y/n)\n");
		scanf(" %s", &check);
		printf("\n");
		if(strcmp(check,"n") == 0 || strcmp(check,"N") == 0)
		{
			return false;
		}
		if(strcmp(check,"y") == 0 || strcmp(check,"Y") == 0 )
			return true;
	}while (true);

	return true;
}