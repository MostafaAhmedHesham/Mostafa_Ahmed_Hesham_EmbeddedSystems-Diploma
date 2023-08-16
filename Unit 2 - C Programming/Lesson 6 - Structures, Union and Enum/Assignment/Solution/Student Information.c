/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

struct sstudent
{
	char name[100];
	int roll;
	float marks;
};


int  main ()
{
	struct sstudent student;
	printf ("Enter Name: ");
	clear;
	gets(student.name);
	printf ("Enter roll number: ");
	clear;
	scanf("%d",&student.roll);
	printf ("Enter marks: ");
	clear;
	scanf("%f",&student.marks);

	printf("\nDisplay Information\n");
	printf ("Name: %s\n",student.name);
	printf ("Roll: %d\n",student.roll);
	printf ("Marks: %.2f\n",student.marks);
	return 0;
}






