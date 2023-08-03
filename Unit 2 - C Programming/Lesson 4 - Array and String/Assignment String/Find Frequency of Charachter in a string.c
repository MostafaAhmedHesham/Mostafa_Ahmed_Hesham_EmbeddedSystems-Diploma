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

	char arr[100],c; // assumed buffer size
	int counter = 0;
	printf("Enter String:");
	clear;
	gets(arr);
	int size = strlen(arr);
	printf("Enter character to find frequency:");
	clear;
	scanf("%c",&c);

	for(int i = 0 ; i < size ; i++)
	{
		if (arr[i]== c)
			counter++;
	}
	printf("Frequency of %c = %d",c,counter);

	return 0;
}
