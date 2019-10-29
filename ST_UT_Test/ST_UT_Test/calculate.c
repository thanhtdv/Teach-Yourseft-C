//
//  main.c
//  統計処理ツール
//
//  Created by Nguyen Trong Khai on 8/26/1 R.
//  Copyright © 1 Reiwa ntkhai19961. All rights reserved.
//

#pragma warning(disable: 4996)
#include <stdio.h>
#include <sys/stat.h>

#define DATA_MAX_NUM 32

//---------------------------------------------------------------

typedef struct {
	int   data_num;
	float data_val[DATA_MAX_NUM];
}DATA_TYPE;

typedef struct {
	float total;
	float average;
	float sigma;
}RESULT_TYPE;

//---------------------------------------------------------------

float Total(DATA_TYPE dataType) {

	float total = 0;

	for (int i = 0; i <= dataType.data_num; i++) {
		total = total + dataType.data_val[i];
	}
	return total;
}

float Average(DATA_TYPE dataType) {

	float average = 0;
	average = Total(dataType) / dataType.data_num;

	return average;
}

float Sigma(DATA_TYPE dataType) {

	float sigma = 0;
	float sum = 0;

	DATA_TYPE dataTypeTemp = dataType;

	for (int i = 0; i < dataTypeTemp.data_num; i++) {
		dataTypeTemp.data_val[i] -= Average(dataType);
	}
	for (int i = 0; i < dataTypeTemp.data_num; i++) {
		dataTypeTemp.data_val[i] *= dataTypeTemp.data_val[i];
	}
	for (int i = 0; i < dataTypeTemp.data_num; i++) {
		sum += dataTypeTemp.data_val[i];
	}
	sigma = sum / (dataTypeTemp.data_num - 1);

	return sigma;
}

void Calculate(DATA_TYPE *dataType, RESULT_TYPE *resultType) {     //(4)

	//総和
	resultType->total = Total(*dataType);

	//平均
	resultType->average = Average(*dataType);

	//標準偏差
	resultType->sigma = Sigma(*dataType);
}


int ReadDataFilename(char dataFilePath[], DATA_TYPE *dataType) {      //(3)

	FILE *fp;
	int i1 = 1;
	int i2 = 2;
	int i3 = 3;
	float f1, f2, f3;

	fp = fopen(dataFilePath, "r");
	if (fp == NULL) {
		printf("%s File open e !\n", dataFilePath);
		return -1;
	}

	while (fscanf(fp, "%f,%f,%f", &f1, &f2, &f3) != EOF) {
		dataType->data_num += 3;
		dataType->data_val[i1] = f1;
		dataType->data_val[i2] = f2;
		dataType->data_val[i3] = f3;
		i1 += 3;
		i2 += 3;
		i3 += 3;
	}
	fclose(fp);
	return 0;
}

int isFileExistsAccess(char dataFilePath[]) {        //(2)

	struct stat buff;
	int res = stat(dataFilePath, &buff);
	if (res != -1)
		return 0;
	return -1;
}

void ShowResult(RESULT_TYPE *resultType) {

	printf("Total: %.1f\n\n", resultType->total);
	printf("Average: %.1f\n\n", resultType->average);
	printf("Sigma: %.1f\n\n", resultType->sigma);
}
/*
int main(int argc, char *argv[])
{
	char dataFilePath[100];
	//char dataFilePath[100] = "C:\Users\morabu\Downloads\ThanhDT\Test設計\データファイル.csv";
	DATA_TYPE   dataType = { 0 , 0 };
	RESULT_TYPE resultType = { 0 , 0 , 0 };

	printf("Enter source file path: ");
	scanf("%s", dataFilePath);

	//(2)
	if (isFileExistsAccess(dataFilePath) == 0)
		printf("File exists\n\n");
	else {
		printf("file does not exist\n\n");
		//return 0;
	}

	//(3)
	if (ReadDataFilename(dataFilePath, &dataType) == 0)
		printf("Read successfully\n\n");
	else {
		printf("Read Failed\n\n");
		//return 0;
	}

	//(4)
	Calculate(&dataType, &resultType);

	//(5)
	ShowResult(&resultType);

	getch();

	return 0;
}

*/