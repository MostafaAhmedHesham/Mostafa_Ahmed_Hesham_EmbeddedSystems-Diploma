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


void unique (int arr[],int size)
{
	int unique_num = arr[0];
	// XOR all elements make duplicates cancel each other
	for (int i = 1 ; i < size ; i++)
		unique_num = unique_num ^ arr[i];
	printf("%d",unique_num);
}



int main() {
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
	unique(arr,size);

    return 0;
}
