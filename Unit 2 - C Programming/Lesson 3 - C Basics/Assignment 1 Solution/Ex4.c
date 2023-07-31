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
	float x , y;
	printf("Enter First Number: ");
	clear;
	scanf("%f",&x);
	printf("Enter Second Number: ");
	clear;
	scanf("%f",&y);
	printf("Multiplication: %f",x*y);
	return 0;
}
