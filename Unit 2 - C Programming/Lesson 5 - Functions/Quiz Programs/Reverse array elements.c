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
	int size;
	printf("Input Array Size: ");
	clear;
	scanf("%d",&size);
	int arr[size];

	printf("Input Array: ");
	for (int i = 0 ; i < size ; i++)
	{
		clear;
		scanf("%d",&arr[i]);
	}

	printf("Output Array: ");
	for (int i = size - 1; i >= 0  ; i--)
	{
		printf("%d ",arr[i]);
	}


	return 0;
}
