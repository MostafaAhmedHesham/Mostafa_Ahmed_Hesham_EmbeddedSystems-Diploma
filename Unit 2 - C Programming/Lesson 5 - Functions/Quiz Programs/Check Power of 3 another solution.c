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
	int num,reminder = 0,i,status;
	printf("Please Enter a number: ");
	clear;
	scanf("%d",&num);

	for (i = num ; i > 1 ; i/=3)
	{
		reminder = i%3;
		if (reminder != 0)
			break;
	}
	if (i > 1)
	{
		status = 1;
		printf("%d ==> %d It's not power of 3",num,status);
	}
	else if (i == 1)
	{
		status = 0;
		printf("%d ==> %d",num,status);
	}

	return 0;
}


