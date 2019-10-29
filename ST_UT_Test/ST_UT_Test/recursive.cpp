#pragma warning(disable: 4996)
#include<stdio.h>
#include<stdlib.h>
#include <string>

#define TITLE "�ċA�I�v�Z�c�[��"
#define SEPARATOR "--------------------------------------------"
#define DATA_CNT 5
#define DATA_MAX_LENGTH 12

typedef struct 
{
	char value[DATA_CNT][DATA_MAX_LENGTH];
	char number[DATA_MAX_LENGTH];
}VALUE_LIST;

int getData(VALUE_LIST*);
bool isNumber(const char*);
bool execProcess(const VALUE_LIST*);
int recursiveA(const char[][DATA_MAX_LENGTH], int cnt);
int recursiveB(const char[][DATA_MAX_LENGTH], int cnt);
int (*fun[])(const char [][DATA_MAX_LENGTH], int cnt) = {recursiveA,recursiveB};

int main_recursive()
{
	VALUE_LIST vll;
	while(true)
	{
		if(getData(&vll) == -1)
		{
			printf(SEPARATOR"\n");
			printf("�s���ȓ��͂ł��B �I�����܂��B\n");
			
			break;
		}
		
		if(execProcess(&vll) == false)
		{
			printf(SEPARATOR"\n");
			printf("�I�����܂��B\n");
			break;
		}
	}
	
	
	system("pause");
	
	return 0;
}

int getData(VALUE_LIST* vll)
{
	printf(TITLE"\n");
	printf(SEPARATOR"\n");
		for (int i = 0; i < 5 ; i++)
		{
			printf("%d�ڂ̐��l����͂��Ă��������B\n>", i + 1);
			scanf("%s", &vll->value[i]);
			if(isNumber(vll->value[i]) == false)
			{
				return -1;
			}

		}
		do 
		{
			printf(SEPARATOR"\n");
			printf("1 : ���a\n");
			printf("2 : ����\n");
			printf(SEPARATOR"\n");
			printf("�����ԍ�����͂��Ă��������B\n>");
			scanf("%s", &vll->number);

			if (isNumber(vll->number) == false)
			{

				return -1;
			}
			
		}
		while (1 > atoi(vll->number) || atoi(vll->number) > 2);

		return 0;
}
 
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

int recursiveA(const char num[][DATA_MAX_LENGTH], int cnt)
{
	int sum = 0;
	if (cnt == 1)
	{
		sum = atoi(num[0]);
	}
	else
	{
		sum = atoi(num[cnt - 1]) + recursiveA(num, cnt - 1); 
	}

	return sum;
}

int recursiveB(const char num[][DATA_MAX_LENGTH], int cnt)
{
	int sum = 1;
	if (cnt == 1)
	{
		sum = atoi(num[0]);
	}
	else
	{
		sum = atoi(num[cnt - 1]) * recursiveB(num, cnt - 1); 
	}

	return sum;
}

bool execProcess(const VALUE_LIST* vll)
{
	char check[5]={0};
	int (*fun[])(const char [][DATA_MAX_LENGTH], int cnt) = {recursiveA,recursiveB};
	
		switch (atoi(vll->number))
	{
	case 1:
		printf("���͂����T�̐��l�̑��a��  %d�ł��B\n", (*fun[0])(vll->value, DATA_CNT));
		break;
	case 2:
		printf("���͂����T�̐��l�̑����  %d�ł��B\n", (*fun[1])(vll->value, DATA_CNT));
		break;
	
	}
	do
	{
		printf("������x�v�Z���܂����H(y/n)\n");
		scanf(" %s", &check);
		if(strcmp(check,"n") == 0 || strcmp(check,"N") == 0)
		{
			return false;
		}
		if(strcmp(check,"y") == 0 || strcmp(check,"Y") == 0 )
			return true;
	}while (true);
	
	return true;
}