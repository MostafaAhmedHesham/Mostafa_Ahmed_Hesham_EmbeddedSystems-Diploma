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


int power(int base, int pow)
{
	base = base*base;
	pow--;
	if (pow > 1)
		power(base,pow);
	return base;
}

int main ()
{
	int base , pow;
	printf("Enter Base Number: ");
	clear;
	scanf("%d",&base);
	printf("Enter Power: ");
	clear;
	scanf("%d",&pow);
	printf("%d ^ %d = %d",base,pow,power(base,pow));



	return 0;
}
