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
	int i = 0;
	printf("Enter String:");
	clear;
	gets(arr);

	while (arr[i] != 0)
		i++;

	printf("Length of String = %d",i);
	return 0;
}
