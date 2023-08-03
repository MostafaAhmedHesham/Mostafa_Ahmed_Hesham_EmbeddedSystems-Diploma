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

	char arr[100]; // assumed buffer size
	int length = 0;
	char temp;
	printf("Enter String:");
	clear;
	gets(arr);

	while (arr[length] != 0)
		length++;

	for (int i = 0 ; i < length/2 ; i ++)
	{
		temp = arr[i];
		arr[i] = arr[length-i-1];
		arr[length-i-1] = temp;
	}
	printf("Reversed String is : %s",arr);
	return 0;
}
