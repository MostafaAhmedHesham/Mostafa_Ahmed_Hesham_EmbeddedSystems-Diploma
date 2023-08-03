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

int main ()
{
	int num,reminder = 0;
	char arr[32]; // assume 32-bit size and char for memory optimization
	printf("Please Enter a number >= 8: ");
	clear;
	scanf("%d",&num);

	for (int i = 0 ; num > 0 ; i++)
	{
		reminder = num%2;
		arr[i] = reminder;
		num /= 2;
	}

	printf("%d",arr[3]);

	return 0;
}


