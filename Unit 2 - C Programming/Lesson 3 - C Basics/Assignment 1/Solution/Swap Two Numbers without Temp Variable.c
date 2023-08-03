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
	int num1 , num2;
	printf("Enter First Number: ");
	clear;
	scanf("%d",&num1);
	printf("Enter Second Number: ");
	clear;
	scanf("%d",&num2);

	//Swapping
	num1 = num1 + num2;
	num2 = num1 - num2;
	num1 = num1 - num2;

	printf("After swapping, First number = %d\n" ,num1);
	printf("After swapping, Second number = %d\n" ,num2);
	return 0;
}
