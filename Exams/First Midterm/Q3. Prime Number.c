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

void prime (int num1,int num2)
{
	while (num1 < num2)
	{
		for (int j = 1 ; j <= num2 ; j++)
		{
			if (num1%j == 0)
			{
				if (j != num1 && j != 1)
					break;
				else if (j == num1)
				{
					printf("%d ",num1);
					break;
				}
			}
		}
		num1++;
	}

}
int main() {
	int num1,num2;
	printf ("Enter start of limit: ");
	clear;
	scanf("%d",&num1);
	printf ("Enter End of limit: ");
	clear;
	scanf("%d",&num2);
	prime(num1,num2);
    return 0;
}






