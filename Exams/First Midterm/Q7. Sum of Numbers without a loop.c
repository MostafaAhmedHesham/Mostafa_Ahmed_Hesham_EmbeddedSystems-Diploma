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

int SumToLimit (int num)
{
	if (num == 1)
		return 1;
	else
		return num + SumToLimit(num-1);
}
int main() {
	int num,sum;
	printf ("Please Enter the Number: ");
	clear;
	scanf("%d",&num);
	sum = SumToLimit (num);
	printf("Sum = %d",sum);
    return 0;
}
