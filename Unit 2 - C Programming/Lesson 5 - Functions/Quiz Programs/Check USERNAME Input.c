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
	char arr[]="USERNAME";
	char buff[100];
	int i;

	printf("Please Enter a String: ");
	clear;
	gets(buff);

	for (i = 0 ; i < sizeof(arr) ; i++)
	{
		if (buff[i] != arr[i])
			break;
	}
	if (i < sizeof(arr))
		printf("Wrong Input");
	else
		printf("Successful");
	return 0;
}


