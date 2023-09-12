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
	int size, inserted, index;
	int temp1,temp2;

	printf("Enter the number of Elements: ");
	clear;
	scanf("%d",&size);

	int arr[size+1];
	for (int i = 0 ; i < size ; i++)
		arr[i] = i+1;

	for (int i = 0 ; i < size ; i++)
		printf("%d ",arr[i]);

	printf("\nEnter Element to be inserted: ");
	clear;
	scanf("%d",&inserted);
	printf("Enter it's index: ");
	clear;
	scanf("%d",&index);

	temp1 = arr[index - 1];
	temp2 = arr[index];

	for (int i = index-1 ; i < size ; i++)
	{
		arr[i+1] = temp1;
		temp1 = temp2;
		temp2 = arr[i+2];
	}
	
	/* 
	Creative way is to poll array from it's end
    for (int i = size ; i >= index-1 ; i--)
	    arr[i] = arr[i-1];
	*/

	arr[index-1] = inserted;
	for (int i = 0 ; i <= size ; i++)
		printf("%d ",arr[i]);
	return 0;
}
