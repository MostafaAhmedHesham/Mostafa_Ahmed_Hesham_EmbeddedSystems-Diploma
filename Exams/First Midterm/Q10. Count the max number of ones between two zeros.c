/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#define clear fflush(stdin); fflush(stdout)

void ones (int num)
{
	int reminder, binary[32]={0},counter = 0,ones=0,max=0;

	/*Convert Number to binary*/
	while(num > 0)
	{
		reminder = num%2;
		binary[counter] = reminder;
		num/=2;
		counter++;
	}
	printf("The Binary = ");
	for (int i = counter ; i>=0 ; i--)
		printf("%d",binary[i]);

	/*Counting Algorithm*/
	for (int i = 0 ; i <= counter ; i++)
	{
		if (binary[i] == 0)
		{
			/*Record the number of previous ones before set it only if it exceeds maximum counted ones*/
			if (ones>max)
				max = ones;
			ones = 0;
			continue;		// Move to the next bit
		}
		if (binary[i] == 1)
			ones++;
	}
	printf("\nMaximum Number of ones is: %d",max);

}
int main() {
	int num;
	printf ("Enter a Number: ");
	clear;
	scanf("%d",&num);
	ones(num);
    return 0;
}
