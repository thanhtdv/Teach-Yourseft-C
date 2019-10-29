#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

#define SEPARATOR "----------------------------------------"
#define TRIANGLE1 "��"
#define TRIANGLE2 "��"

int getInfo(char *, char *);
void execProcess(const char *, const char *);
int isNumber(const char *);
void functionA(const int);
void functionB(const int);

void (*func[])(const int) = {functionA, functionB};

int main_triangleart(void)
{
	char processno[16];
	char rows[16];
	int num;
	
	do{
		num = getInfo(processno, rows);
		switch(num){
			case 0:
				execProcess(processno, rows);
				break;
			case -1:
				puts("�s���ȓ��͂ł��B�I�����܂��B");
				return 0;
		}
	}while(num != 1);
	
	return 0;
}

int getInfo(char *processno, char *rows)
{
	int num;
	char *fig[] = {TRIANGLE1, TRIANGLE2};
	
	do{
		puts("TriangleArt");
		puts(SEPARATOR);
		puts("1 : �O�p�`");
		puts("2 : �t�O�p�`");
		puts("9 : �I��");
		puts(SEPARATOR);
		puts("�����ԍ�����͂��Ă��������B");
		putchar('>');
		gets(processno);
		
		if(!isNumber(processno)){
			return -1;
		}
		
		num = atoi(processno);
		
		if(num == 9){
			return 1;
		}
	}while(num < 1 || num > 2);
	
	while(1){
		printf("�u%s�v���o�͂���s������͂��Ă��������B\n", fig[num - 1]); 
		putchar('>');
		gets(rows);
		
		if(!isNumber(rows)){
			return -1;
		}
		
		if(atoi(rows)){
			break;
		}
		
		puts("�u1�v�ȏ�̒l����͂��Ă��������B");
	}
	
	return 0;
}

int isNumber(const char *p)
{
	while(*p){
		if(*p < '0' || *p > '9'){
			return 0;
		}
		p++;
	}
	
	return 1;
}

void execProcess(const char *processno, const char *rows)
{
	(*func[atoi(processno) - 1])(atoi(rows));
}

void functionA(const int n)
{
	int i;
	int j;
	
	for(i = 0; i < n; i++){
		for(j = 0; j < n - i - 1; j++){
			putchar(' ');
		}
		for(j = 0; j < i + 1; j++){
			printf(TRIANGLE1);
		}
		putchar('\n');
	}
}

void functionB(const int n)
{
	int i;
	int j;
	
	for(i = 0; i < n; i++){
		for(j = 0; j < i; j++){
			putchar(' ');
		}
		for(j = 0; j < n - i; j++){
			printf(TRIANGLE2);
		}
		putchar('\n');
	}
}
