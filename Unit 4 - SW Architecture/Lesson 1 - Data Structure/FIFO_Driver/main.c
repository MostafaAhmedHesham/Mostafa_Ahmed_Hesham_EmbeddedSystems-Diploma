/*
 * main.c
 *
 *  Created on: Sep 16, 2023
 *      Author: AEMYS
 */

#include "fifo.h"
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

#define BUFF_SIZE 5

int main() {

	FIFO_Buf_t buffer;

	/* using static data */
	element_type arr[BUFF_SIZE];

	/*Using Dynamic Allocation*/
	//element_type *arr = (element_type*)malloc(BUFF_SIZE*sizeof(element_type));

	/*NULL test*/
	//element_type *arr = NULL;

	if (FIFO_NULL(&buffer,arr,0) == fifo_no_error)
		FIFO_init(&buffer, arr, BUFF_SIZE);
	else
		printf("FIFO Is't Initialized Correctly\n");

	/* Adding Element to Buffer*/
	for (uint32 i= 0 ; i < BUFF_SIZE ; i++)
	{
		if (FIFO_NULL(&buffer,arr,1) == fifo_Null)
		{
			printf("FIFO Is't Initialized Correctly\n");
			break;
		}
		if (FIFO_FULL(&buffer) == fifo_full)
		{
			printf("FIFO is FULL\n");
			break;
		}
		else
		{
			FIFO_add(&buffer, arr, i+1);
			printf("ADD Element to buffer: %d\n",arr[i]);
		}

	}

	/*Get element from Buffer*/
	element_type get_variable = 0; //Variable used to receive the data from get function
	for (uint32 i = 0 ; i < BUFF_SIZE ; i++)
	{
		if (FIFO_NULL(&buffer,arr,1) == fifo_Null)
		{
			printf("FIFO Is't Initialized Correctly\n");
			break;
		}
		if (FIFO_EMPTY(&buffer) == fifo_empty)
		{
			printf("FIFO is Empty\n");
			break;
		}
		else
		{
			FIFO_get(&buffer, arr, &get_variable);
			printf("Get Element from buffer: %d\n",get_variable);
		}
	}
	return 0;
}
