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
	int n, factorial =1;
	printf("Enter a number: ");
	clear;
	scanf("%d",&n);

	if (n <= 0)
		printf("%d Factorial doesn't exist\n",n);
	else
	{
		for (int i = 1 ; i <= n ; i++)
			factorial = i*factorial;
		printf("Factorial = %d\n\n",factorial);
	}
}

int main ()
{
	positive_or_negative();
	positive_or_negative();
	return 0;
}
