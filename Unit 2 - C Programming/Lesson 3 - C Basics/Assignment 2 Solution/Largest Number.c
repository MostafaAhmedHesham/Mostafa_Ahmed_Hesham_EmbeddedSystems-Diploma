/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

int main ()
{
	float num1,num2,num3;
	printf("Enter First Number: ");
	clear;
	scanf("%f",&num1);
	printf("Enter Second Number: ");
	clear;
	scanf("%f",&num2);
	printf("Enter Third Number: ");
	clear;
	scanf("%f",&num3);

	if (num1 > num2 && num1 > num3)
		printf("%f largest number is: ",num1);
	else if (num2 > num1 && num2 > num3)
		printf("largest number is: %f",num2);
	else
		printf("largest number is: %f",num3);
	return 0;
}
