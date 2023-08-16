/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define clear fflush(stdin); fflush(stdout)

struct employee {
    char name[50];
    int id;
};

int main() {
	struct employee e1 = {"Mostafa" , 100};
	struct employee e2 = {"Ahmed" , 101};
	struct employee e3 = {"Hesham" , 102};

	/*Initialization of pointer to array of pointers*/
	struct employee *(*ptr)[] = &(struct employee *[]){&e1,&e2,&e3};
	printf("Employee Name: %s\n",(*ptr)[0]->name);
	printf("Employee ID: %d",(*ptr)[0]->id);



    return 0;
}






