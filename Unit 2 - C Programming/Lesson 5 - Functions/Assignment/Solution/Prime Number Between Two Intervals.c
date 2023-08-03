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


int prime_calc(int num1 , int num2)
{
	int division = 0, reminder = 0;
	for (int var = num1 ; var <= num2 ; var++)
	{
		for (int j = 2 ; j <= var ; j++)
		{
			reminder = var%j;
			division = var/j;
			if (reminder == 0 && j != var)
				break;
			else if (reminder == 0 && division == 1 && j == var)
				printf("%d ",var);
		}
		reminder = 0;
		division = 0;
	}
	return 0;
}

int main ()
{
	int num1 = 0 ,num2 = 30;
	printf("Enter The 1st Number: ");
	clear;
	scanf("%d",&num1);
	printf("Enter The 2nd Number: ");
	clear;
	scanf("%d",&num2);
	printf("The Prime Numbers between %d and %d is: ",num1,num2);
	prime_calc(num1 ,num2);
	return 0;
}
