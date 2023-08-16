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
	char name[30];
	int roll;
	float marks;
};


int  main ()
{
	struct sstudent students[10];
	//for (int i = 0 ; i < sizeof(students)/sizeof(students[0]) ; i++)
	for (int i = 0 ; i < 3 ; i++)
	{
		printf("For Student no.%d\n",i+1);
		printf ("Enter Name: ");
		clear;
		gets(students[i].name);
		printf ("Enter roll number: ");
		clear;
		scanf("%d",&students[i].roll);
		printf ("Enter marks: ");
		clear;
		scanf("%f",&students[i].marks);
		printf("\n");
	}
	//for (int i = 0 ; i < sizeof(students)/sizeof(students[0]) ; i++)
	for (int i = 0 ; i < 3 ; i++)
	{
		printf("\nDisplay Information of student no.%d\n",i+1);
		printf ("Name: %s\n",students[i].name);
		printf ("Roll: %d\n",students[i].roll);
		printf ("Marks: %.2f\n",students[i].marks);
	}

	return 0;
}






