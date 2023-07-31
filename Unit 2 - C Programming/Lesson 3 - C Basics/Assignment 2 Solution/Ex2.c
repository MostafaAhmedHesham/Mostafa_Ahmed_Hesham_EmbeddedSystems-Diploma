/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

void Vowel_or_Consonant(){
	char c;
	printf("Enter a letter: ");
	clear;
	scanf("%c",&c);

	if (c == 'a' || c == 'e' || c == 'o' || c == 'u' || c == 'i')
		printf("%c is Vowel Letter\n",c);
	else if (c == 'A' || c == 'E' || c == 'O' || c == 'U' || c == 'I')
		printf("%c is Vowel Letter\n",c);
	else
		printf("%c is Consonant Letter\n",c);
}


int main ()
{
	Vowel_or_Consonant();
	Vowel_or_Consonant();
	return 0;
}
