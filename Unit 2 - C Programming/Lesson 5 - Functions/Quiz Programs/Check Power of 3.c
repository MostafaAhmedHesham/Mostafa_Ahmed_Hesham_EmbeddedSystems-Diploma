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

int counter;
int check (int num)
{
	int reminder = 0;
	while (num > 1)
	{
		reminder = num%3;
		if (reminder != 0)
			break;
		else
		{
			num/=3;
			counter++;
		}
	}
	if (reminder != 0)
		return 1;
	else
		return 0;
}



int main ()
{
	int num,status;
	printf("Please Enter a number: ");
	clear;
	scanf("%d",&num);
	status  = check(num);

	if (status == 1)
		printf("%d ==> %d It's not power of 3",num,status);
	else if (status == 0)
		printf("%d ==> %d and it's 3^%d",num,status,counter);

	return 0;
}


