/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)


int  main ()
{
	char letter = 'A', *ptr;
	ptr = &letter;
	while (letter <= 'Z')
	{
		printf("%c ",*ptr);
		(*ptr)++;
	}
	return 0;
}






