/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)


int  main ()
{
	int arr[15],size;
	int *ptr = arr;
	printf("Enter number of elements (Max15): ");
	clear;
	scanf("%d",&size);

	printf("Input %d number of elements in the array :\n",size);
	for (int i = 0 ; i < size  ; i++)
	{
		printf("Enter element number %d: ",i+1);
		clear;
		scanf("%d",&arr[i]);
		ptr++;
	}
	//ptr--;
	printf("The elements of array in reverse order are :\n");
	for (int i = size ; i > 0 ; i--)
	{
		ptr--;
		printf("Element number %d: %d\n",i,*ptr);
		//ptr--;
	}

	return 0;
}






