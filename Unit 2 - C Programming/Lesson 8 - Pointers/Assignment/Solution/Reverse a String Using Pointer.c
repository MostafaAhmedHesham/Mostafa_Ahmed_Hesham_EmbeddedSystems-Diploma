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
	char string[50],temp,length=0;
	char *start = string;
	char *end = string;

	printf("Please Enter a String: ");
	clear;
	gets(string);
	while (*end != 0)
	{
		length++;
		end++;
	}
	end--;

	for (char i = 0 ; i <length/2 ; i++)
	{
		temp = *end;
		*end = *start;
		*start = temp;
		end--;
		start++;
	}

	printf("Reversed String is : %s",string);

	return 0;
}






