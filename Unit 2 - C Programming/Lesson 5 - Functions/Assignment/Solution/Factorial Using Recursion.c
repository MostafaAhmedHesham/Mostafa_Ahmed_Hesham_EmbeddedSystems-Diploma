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


int fact_calc(int num)
{
	if (num == 1)
		return 1;
	return num*fact_calc(num-1);
}

int main ()
{
	int num, fact;
	printf("Enter a Positive Integer: ");
	clear;
	scanf("%d",&num);
	fact = fact_calc(num);
	printf("Factorial of %d = %d",num,fact);
	return 0;
}
