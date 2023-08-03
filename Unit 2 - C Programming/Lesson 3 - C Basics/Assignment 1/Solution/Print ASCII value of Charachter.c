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
	char x;
	printf("Enter a Character: ");
	clear;
	scanf("%c",&x);
	printf("ASCII value of %c = %d",x,x);
	return 0;
}
