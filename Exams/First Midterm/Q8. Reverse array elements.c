/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define clear fflush(stdin); fflush(stdout)

void reverse (int arr[],int size)
{
	int temp;
	printf("Reversed Array: ");
	for (int i = 0; i < size/2 ; i++)
	{
		temp = arr[size-i-1];
		arr[size-1-i] = arr[i];
		arr[i] = temp;
	}
}

int main ()
{
	int size;
	printf ("Please Enter the Size: ");
	clear;
	scanf("%d",&size);
	int arr[size];
	for (int i = 0 ; i < size  ; i++)
	{
		printf ("Please Element no.%d: ",i+1);
		clear;
		scanf("%d",&arr[i]);
	}
	reverse(arr,size);

	printf("Reversed Array: ");
	for (int i = 0 ; i < size  ; i++)
	{
		printf("%d ",arr[i]);
	}
	return 0;
}
