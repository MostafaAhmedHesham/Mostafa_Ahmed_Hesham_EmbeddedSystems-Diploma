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
	float num1,num2;
	char operator;
	printf("Enter an operator + or - or * or /: ");
	clear;
	scanf("%c",&operator);
	printf("Enter 1st operand: ");
	clear;
	scanf("%f",&num1);
	printf("Enter 2nd operand: ");
	clear;
	scanf("%f",&num2);

	switch (operator)
	{
		case '+':
			printf("The Result is:%f",num1+num2);
			break;
		case '-':
			printf("The Result is:%f",num1-num2);
			break;
		case '*':
			printf("The Result is:%f",num1*num2);
			break;
		case '/':
			printf("The Result is: %f",num1/num2);
			break;
	}
	return 0;
}
