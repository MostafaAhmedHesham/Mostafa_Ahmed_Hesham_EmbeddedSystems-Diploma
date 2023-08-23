/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define clear fflush(stdin); fflush(stdout)

float sq_root (int num)
{
	return sqrt(num);
}
int main() {
	float num;
	printf ("Please Enter the Number: ");
	clear;
	scanf("%f",&num);
	printf("%.3f",sq_root(num));
    return 0;
}