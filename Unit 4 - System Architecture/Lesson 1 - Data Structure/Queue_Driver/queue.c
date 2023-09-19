/*
 * queue.c
 *
 *  Created on: Sep 16, 2023
 *      Author: AEMYS
 */


/* Check if QUEUE is valid and allocated correctly*/
#include "queue.h"
#include "stdio.h"

QUEUE_status QUEUE_NULL (QUEUE_Buf_t *QUEUE_buf, element_type *buf , uint8 flag)
{
	/* Flag is to avoid re-initialization of head & base*/
	if (flag == 0)
	{
		//initialize head & base with data buffer
		QUEUE_buf->base = buf;
		QUEUE_buf->head = buf;
		QUEUE_buf->tail = buf;
		flag++;
	}
	if (!QUEUE_buf->base || !QUEUE_buf->head)
		return queue_Null;
	return queue_no_error;
}

QUEUE_status QUEUE_Full (QUEUE_Buf_t * QUEUE_buf, element_type *buf)
{
	if (QUEUE_buf->head == (QUEUE_buf->base + QUEUE_buf->length))
		return queue_full;
	else
		return queue_no_error;
}

QUEUE_status QUEUE_init(QUEUE_Buf_t * QUEUE_buf, element_type *buf, uint32 length)
{
	/* Check if QUEUE is valid and allocated correctly*/
	if (QUEUE_NULL(QUEUE_buf,buf,1) == queue_Null)
		return queue_Null;

	/*Initializing QUEUE*/
	QUEUE_buf->length = length;
	QUEUE_buf->base = buf;
	QUEUE_buf->head = buf;
	QUEUE_buf->tail = buf;
	return queue_no_error;
}

QUEUE_status QUEUE_add(QUEUE_Buf_t * QUEUE_buf, element_type *buf, element_type data)
{
	/* Check if QUEUE is valid and allocated correctly*/
	if (QUEUE_NULL(QUEUE_buf,buf,1) == queue_Null)
		return queue_Null;

	if (QUEUE_buf->head == (QUEUE_buf->base + QUEUE_buf->length))
		QUEUE_buf->head = QUEUE_buf->base;


	*(QUEUE_buf->head) = data;
	QUEUE_buf->head++;
	return queue_no_error;
}

QUEUE_status QUEUE_get(QUEUE_Buf_t * QUEUE_buf, element_type *buf, element_type *data)
{
	/* Check if QUEUE is valid and allocated correctly*/
	if (QUEUE_NULL(QUEUE_buf,buf,1) == queue_Null)
		return queue_Null;

	if (QUEUE_buf->tail == (QUEUE_buf->base + QUEUE_buf->length))
		QUEUE_buf->tail = QUEUE_buf->base;

	*data = *(QUEUE_buf->tail);
	(QUEUE_buf->tail)++;
	return queue_no_error;
}

void QUEUE_print(QUEUE_Buf_t *QUEUE_buf, element_type *buf )
{
	for (uint32 i = 0; i < QUEUE_buf->length; i++)
		printf("ADD Element to Queue: %d\n",buf[i]);
}


