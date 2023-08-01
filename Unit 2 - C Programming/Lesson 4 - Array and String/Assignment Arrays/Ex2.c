/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

int main ()
{
	int size;
	float sum = 0;
	printf("Enter the number of data: ");
	clear;
	scanf("%d",&size);
	float arr[size];

	for (int i = 0 ; i < size ; i++)
	{
		printf("Enter number: ");
		clear;
		scanf("%f",&arr[i]);
	}

	for (int i = 0 ; i < size ; i++)
		sum += arr[i];
	printf("Average = %.3f",sum/size);

	return 0;
}
