/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

void Even_and_ODD(){
	int num;
	printf("Enter a Number: ");
	clear;
	scanf("%d",&num);

	if (num%2 == 0)
		printf("%d is Even Number\n",num);
	else
		printf("%d is Odd Number\n",num);
}



int main ()
{
	Even_and_ODD();
	Even_and_ODD();
	return 0;
}
