/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define clear fflush(stdin); fflush(stdout)


int convert(int size,char arr[size])
{
	unsigned int result = 0;
	for (int i = 0 ; i < size-1 ; i++)
	{
		arr[i]-='0';
		result = result * 10 + arr[i];
	}
	return result;
}



int main ()
{
	char arr[] = "1353";
	unsigned int result;
	result = convert(sizeof(arr),arr);
	printf("%d",result);
	return 0;
}
