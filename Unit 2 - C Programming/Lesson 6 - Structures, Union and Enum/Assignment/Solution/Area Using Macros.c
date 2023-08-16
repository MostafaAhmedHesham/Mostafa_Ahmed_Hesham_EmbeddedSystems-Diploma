/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)
#define area(a) 3.14*a*a

int  main ()
{
	float r;
	printf ("Enter radius: ");
	clear;
	scanf("%f",&r);
	printf("Area = %.5f",area(r));
	return 0;
}






