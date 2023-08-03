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

void swap_array(int size1,int size2, int *arr1, int *arr2)
{
	int sizetemp = size1>size2 ? size1:size2;
	int arrtemp[sizetemp];
	/*
	if (size1>size2)
	{
		diff = size1-size2;
		arr2 = (int*)realloc(arr2,diff*sizeof(int));
	}
	else
	{
		diff = size2-size1;
		arr1 = (int*)realloc(arr1,diff*sizeof(int));
	}
	*/
	//Saving Array 1 elements to temporary array
	for (int i = 0 ; i < sizetemp ; i++)
		arrtemp[i] = arr1[i];
	//Swapping Array 1 and Array 2
	for (int i = 0 ; i < size2 ; i++)
		arr1[i] = arr2[i];
	for (int i = 0 ; i < size1 ; i++)
		arr2[i] = arrtemp[i];


}

int main ()
{
	int size1,size2;
	printf("Enter Array 1 Size: ");
	clear;
	scanf("%d",&size1);
	printf("Enter Array 2 Size: ");
	clear;
	scanf("%d",&size2);

	//declared by dynamic memory allocation to allow changing in size
	int *arr1 = (int*)malloc(size1*sizeof(int));
	int *arr2 = (int*)malloc(size2*sizeof(int));

	printf("Enter Array 1 Elements:\n");
	clear;
	for (int i = 0 ; i < size1 ; i++)
		scanf("%d",&arr1[i]);

	printf("Enter Array 2 Elements:\n");
	clear;
	for (int i = 0 ; i < size2 ; i++)
		scanf("%d",&arr2[i]);

	swap_array(size1,size2,arr1,arr2);

	printf("Array 1 After Swapping:\n");
	for (int i = 0 ; i < size2 ; i++)
		printf("%d ",arr1[i]);

	printf("\nArray 2 After Swapping:\n");
	for (int i = 0 ; i < size1 ; i++)
		printf("%d ",arr2[i]);

	return 0;
}
