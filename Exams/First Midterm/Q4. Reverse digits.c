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

void reverse (int num)
{
	int reminder,reversed=0;
	while (num > 0)
	{
		reminder = num%10;
		reversed = reversed*10 + reminder;
		num/=10;
	}
	printf("The reversed number is: %d",reversed);
}
int main() {
	int num;
	printf ("Enter Number: ");
	clear;
	scanf("%d",&num);
	reverse(num);
    return 0;
}






