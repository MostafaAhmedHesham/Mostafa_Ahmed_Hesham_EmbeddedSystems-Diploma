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
	int n,sum=0;
	printf("Enter a number: ");
	clear;
	scanf("%d",&n);

	if (n <= 0)
		printf("%d Solution doesn't exist\n",n);
	else
	{
		for (int i = 1 ; i <= n ; i++)
			sum = sum + i;
		printf("Factorial = %d\n\n",sum);
	}
	return 0;
}
