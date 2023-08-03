/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

void positive_or_negative(){
	float num;
	printf("Enter a Number: ");
	clear;
	scanf("%f",&num);

	if (num > 0)
		printf("%f is positive \n",num);
	else if (num < 0)
		printf("%f is negative \n",num);
	else
		printf("You Entered Zero");
}


int main ()
{
	positive_or_negative();
	positive_or_negative();
	positive_or_negative();
	return 0;
}
