#include<stdio.h>
#include "data_read.h"

/*
* Comments: 读取初始标识M0和赋时时间Delay
* Param int place_num :  库所数量
* Param int M0[] :  初始标识
* Param  int Delay[] : 赋时时间
* @Return void 
*/
void data_read(int place_num, int M0[], int Delay[])
{
	int i;
	FILE *fp;
	fp = fopen(M0_path, "r"); //读取初始标识 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	for (i = 0; i <place_num; i++)
	{
		fscanf(fp, "%d", &M0[i]);
	}
	fclose(fp);

	printf("初始标识：\n"); //输出初始 
	for (i = 0; i < place_num; i++)
	{
		printf("%3d", M0[i]);
	}
	printf("\n");

	fp = fopen(Delay_path, "r"); //读取库所上赋时时间 
	if (fp == NULL)
	{
		printf("cannot open file\n");
	}
	for (i = 0; i < place_num; i++)
	{
		fscanf(fp, "%d", &Delay[i]);
	}
	fclose(fp);

	printf("库所赋时时间：\n"); //输出赋时时间 
	for (i = 0; i < place_num; i++)
	{
		printf("%3d", Delay[i]);
	}
	printf("\n");
}