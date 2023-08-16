/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

struct sdistance
{
	int feet;
	float inch;
};


int  main ()
{
	struct sdistance distance1,distance2,sum;
	printf ("Enter Distance 1 Information\n");
	printf ("Enter Feet: ");
	clear;
	scanf("%d",&distance1.feet);
	printf ("Enter inch: ");
	clear;
	scanf("%f",&distance1.inch);
	printf ("Enter Distance 2 Information\n");
	printf ("Enter Feet: ");
	clear;
	scanf("%d",&distance2.feet);
	printf ("Enter inch: ");
	clear;
	scanf("%f",&distance2.inch);

	sum.feet = distance1.feet + distance2.feet;
	sum.inch = distance1.inch + distance2.inch;
	if (sum.inch > 12)
	{
		sum.inch = sum.inch - 12;
		sum.feet++;
	}
	printf("Sum of Distances = %d' %.2f''",sum.feet,sum.inch);
	return 0;
}






