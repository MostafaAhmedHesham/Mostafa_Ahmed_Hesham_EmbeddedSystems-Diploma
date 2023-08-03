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
	char c;
	printf("Enter a Character: ");
	clear;
	scanf("%c",&c);

	if ((c  >= 'A' && c <= 'Z') || (c  >= 'a' && c <= 'z'))
		printf("%c is an alphabet \n",c);
	else
		printf("%c is not an alphabet \n",c);
}

int main ()
{
	positive_or_negative();
	positive_or_negative();
	positive_or_negative();
	return 0;
}
