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
	int m = 29;
	int *ab;
	printf("Address of m : %p\n",&m);
	printf("value of m : %d\n",m);


	ab = &m;
	printf("Address of pointer ab : %p\n",ab);
	printf("vContent of pointer ab : %d\n",*ab);

	m = 34;
	printf("Address of pointer ab : %p\n",ab);
	printf("vContent of pointer ab : %d\n",*ab);


	*ab = 7;
	printf("Address of m : %p\n",&m);
	printf("value of m : %d\n",m);


	return 0;
}






