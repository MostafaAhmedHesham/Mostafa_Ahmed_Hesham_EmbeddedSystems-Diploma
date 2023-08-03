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

int scan(int size,int arr[size])
{
	int index = 0;
	for (int i = 0 ; i < size ; i++)
	{
		for (int j = i + 1 ; j < size ; j++)
		{
			if (arr[i] == arr[j])
				index = j;
		}
	}
	return index;
}

int main ()
{
	int size,index;
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
	index = scan(size,arr);
	printf("The Number is %d ==> result = %d",arr[index],index);

	return 0;
}
