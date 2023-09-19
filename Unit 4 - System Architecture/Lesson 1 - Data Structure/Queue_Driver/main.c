/*
 * main.c
 *
 *  Created on: Sep 16, 2023
 *      Author: AEMYS
 */


#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

#define BUFF_SIZE 5

int main() {

	QUEUE_Buf_t buffer;

	/* using static data */
	element_type arr[BUFF_SIZE];

	/*Using Dynamic Allocation*/
	//element_type *arr = (element_type*)malloc(BUFF_SIZE*sizeof(element_type));

	/*NULL test*/
	//element_type *arr = NULL;

	if (QUEUE_NULL(&buffer,arr,0) == queue_no_error)
		QUEUE_init(&buffer, arr, BUFF_SIZE);
	else
		printf("QUEUE Is't Initialized Correctly\n");

	for (uint32 i= 0 ; i < BUFF_SIZE ; i++)
	{
		if (QUEUE_Full(&buffer, arr)== queue_full)
			printf("Warning Queue is Full, Elements will be overwritten\n");

		if (QUEUE_NULL(&buffer,arr,1) == queue_Null)
		{
			printf("QUEUE Is't Initialized Correctly\n");
			break;
		}
		else
			QUEUE_add(&buffer, arr, i+1);
	}

	/*Printing arr buffer to check that is circular*/
	QUEUE_print(&buffer, arr);


	/*Get element from Buffer*/
	element_type get_variable = 0; //Variable used to receive the data from get function
	for (uint32 i = 0 ; i < BUFF_SIZE ; i++)
	{
		if (QUEUE_NULL(&buffer,arr,1) == queue_Null)
		{
			printf("QUEUE Is't Initialized Correctly\n");
			break;
		}
		else
		{
			QUEUE_get(&buffer, arr, &get_variable);
			printf("Get Element from Queue: %d\n",get_variable);
		}
	}
	return 0;
}
