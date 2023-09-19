/*
 ============================================================================
 Name        : main.c
 Author      : AEMYS
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "lifo.h"
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

#define BUFF_SIZE 5

int main() {

	LIFO_Buf_t buffer;

	/* using static data */
	//uint32 arr[BUFF_SIZE];

	/*Using Dynamic Allocation*/
	element_type *arr = (element_type*)malloc(BUFF_SIZE*sizeof(element_type));

	/*NULL test*/
	//uint32 *arr = NULL;

	if (LIFO_NULL(&buffer,arr,0) == lifo_no_error)
		LIFO_init(&buffer, arr, BUFF_SIZE);
	else
		printf("LIFO Is't Initialized Correctly\n");

	/* Adding Element to Buffer*/
	for (uint32 i= 0 ; i < BUFF_SIZE ; i++)
	{
		if (LIFO_NULL(&buffer,arr,1) == lifo_Null)
		{
			printf("LIFO Is't Initialized Correctly\n");
			break;
		}
		if (LIFO_FULL(&buffer) == lifo_full)
		{
			printf("LIFO is FULL\n");
			break;
		}
		else
		{
			LIFO_add(&buffer, arr, i+1);
			printf("ADD Element to buffer: %d\n",arr[i]);
		}

	}

	/*Get element from Buffer*/
	element_type get_variable = 0; //Variable used to receive the data from get function
	for (uint32 i = 0 ; i < BUFF_SIZE ; i++)
	{
		if (LIFO_NULL(&buffer,arr,1) == lifo_Null)
		{
			printf("LIFO Is't Initialized Correctly\n");
			break;
		}
		if (LIFO_EMPTY(&buffer) == lifo_empty)
		{
			printf("LIFO is Empty\n");
			break;
		}
		else
		{
			LIFO_get(&buffer, arr, &get_variable);
			printf("Get Element from buffer: %d\n",get_variable);
		}
	}
	return 0;
}









