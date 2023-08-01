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
	int size, searched;

	printf("Enter the number of Elements: ");
	clear;
	scanf("%d",&size);

	int arr[size+1];
	for (int i = 0 ; i < size ; i++)
		scanf("%d",&arr[i]);

	printf("\nEnter Element to be Searched: ");
	clear;
	scanf("%d",&searched);

	for (int i = 0 ; i < size ; i++)
	{
		if (arr[i] == searched)
			{
				printf("Number found at Location = %d",i+1);
				break;
			}
		else if (i == (size-1))
			printf("Not Found!!");
	}

	return 0;
}
