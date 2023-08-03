/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)


void array_input(float arr[2][2])
{
	for (int i = 0 ; i < 2 ; i++)
	{
		for (int j = 0 ; j < 2 ; j++)
		{
			printf("Enter Element[%d][%d]: ",i+1,j+1);
			clear;
			scanf("%f",&arr[i][j]);
		}
	}
}

int main ()
{
	float a[2][2],b[2][2];

	printf("Enter Elements of 1st array\n");
	array_input(a);

	printf("Enter Elements of 2nd array\n");
	array_input(b);

	printf("Sum of Matrix:\n");
	for (int i = 0 ; i < 2 ; i++)
	{
		for (int j = 0 ; j < 2 ; j++)
		{
			printf ("%f ",a[i][j] + b[i][j]);
		}
		printf("\n");
	}

	return 0;
}
