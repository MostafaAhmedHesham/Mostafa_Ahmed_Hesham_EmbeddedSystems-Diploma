/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

union uwork {
	char work[32];
	float num;
	int no;
}u;

struct swork {
	char work[32];
	float num;
	int no;
}s;


int  main ()
{
	printf("Union %d\n",sizeof(u));
	printf("Structure %d",sizeof(s));
	return 0;
}






