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
	int x;
	printf("Enter an integer: ");
	clear;
	scanf("%d",&x);
	printf("You Entered: %d",x);
	return 0;
}
