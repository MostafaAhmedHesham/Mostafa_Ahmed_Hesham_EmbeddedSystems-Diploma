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

void sum_digits (int num)
{
	int sum = 0, reminder = 0;
	while (num > 0)
	{
		reminder = num%10;
		sum += reminder;
		num = num/10;
	}
	printf("The Sum of Digits is: %d",sum);
}

int main() {
	int num;
	printf ("Please Enter the Number: ");
	clear;
	scanf("%d",&num);
	sum_digits(num);
    return 0;
}






