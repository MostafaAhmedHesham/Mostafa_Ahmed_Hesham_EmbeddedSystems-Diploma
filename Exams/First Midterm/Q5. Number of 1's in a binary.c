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

void ones (int num)
{
	int counter = 0,reminder;
	while (num > 0)
	{
		reminder = num%2;
		if (reminder == 1)
			counter++;
		num/=2;
	}
	printf("The Number of 1's = %d",counter);
}
int main() {
	int num;
	printf ("Enter a Number: ");
	clear;
	scanf("%d",&num);
	ones(num);
    return 0;
}






