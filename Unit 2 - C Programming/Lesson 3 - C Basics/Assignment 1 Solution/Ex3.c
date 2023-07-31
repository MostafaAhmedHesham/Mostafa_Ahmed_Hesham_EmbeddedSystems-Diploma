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
	int x , y;
	printf("Enter First integer: ");
	clear;
	scanf("%d",&x);
	printf("Enter Second integer: ");
	clear;
	scanf("%d",&y);
	printf("Sum: %d",x+y);
	return 0;
}
