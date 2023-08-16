/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

struct scomplex
{
	float real;
	float img;
};

struct scomplex sum(struct scomplex num1,struct scomplex num2)
{
	struct scomplex sum;
	sum.real = num1.real + num2.real;
	sum.img = num1.img + num2.img;
	return sum;
}

struct scomplex input(struct scomplex num)
{
	printf("Enter Real part: ");
	clear;
	scanf("%f",&num.real);
	printf("Enter Imaginary part: ");
	clear;
	scanf("%f",&num.img);
	return num;
}


int  main ()
{
	struct scomplex num1,num2;
	printf ("For first complex number: \n");
	num1 = input(num1);
	printf ("For second complex number: \n");
	num2 = input(num2);

	printf("Sum = %.2f + %.2fi",sum(num1,num2).real,sum(num1,num2).img);
	return 0;
}






