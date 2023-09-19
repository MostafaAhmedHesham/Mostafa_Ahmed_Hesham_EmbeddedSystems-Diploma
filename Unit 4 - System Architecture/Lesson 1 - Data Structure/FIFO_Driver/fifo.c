/*
 * fifo.c
 *
 *  Created on: Sept 16, 2023
 *      Author: AEMYS
 */

#include "fifo.h"


/* Check if FIFO is valid and allocated correctly*/

FIFO_status FIFO_NULL (FIFO_Buf_t *FIFO_buf, element_type *buf , uint8 flag)
{
	/* Flag is to avoid re-initialization of head & base*/
	if (flag == 0)
	{
		//initialize head & base with data buffer
		FIFO_buf->base = buf;
		FIFO_buf->head = buf;
		flag++;
	}
	if (!FIFO_buf->base || !FIFO_buf->head)
		return fifo_Null;
	return fifo_no_error;
}

/*Check If FIFO is FULL*/
FIFO_status FIFO_FULL (FIFO_Buf_t * FIFO_buf)
{
	if (FIFO_buf->count >= FIFO_buf->length)
		return fifo_full;
	return fifo_no_error;
}

/*Check If FIFO is EMPTY*/
FIFO_status FIFO_EMPTY (FIFO_Buf_t * FIFO_buf)
{
	if (FIFO_buf->count == 0)
		return fifo_empty;
	return fifo_no_error;
}



FIFO_status FIFO_init(FIFO_Buf_t * FIFO_buf, element_type *buf, uint32 length)
{
	/* Check if FIFO is valid and allocated correctly*/
	if (FIFO_NULL(FIFO_buf,buf,1) == fifo_Null)
		return fifo_Null;

	/*Initializing FIFO*/
	FIFO_buf->length = length;
	FIFO_buf->base = buf;
	FIFO_buf->head = buf;
	FIFO_buf->count = 0;
	return fifo_no_error;
}

FIFO_status FIFO_add(FIFO_Buf_t * FIFO_buf, element_type *buf, element_type data)
{
	/* Check if FIFO is valid and allocated correctly*/
	if (FIFO_NULL(FIFO_buf,buf,1) == fifo_Null)
		return fifo_Null;

	/*Check If FIFO is FULL*/
	if (FIFO_FULL(FIFO_buf)==fifo_full)
		return fifo_full;

	*(FIFO_buf->head) = data;
	(FIFO_buf->count)++;
	FIFO_buf->head++;
	return fifo_no_error;
}

FIFO_status FIFO_get(FIFO_Buf_t * FIFO_buf, element_type *buf, element_type *data)
{
	/* Check if FIFO is valid and allocated correctly*/
	if (FIFO_NULL(FIFO_buf,buf,1) == fifo_Null)
		return fifo_Null;

	/*Check If FIFO is Empty*/
	if (FIFO_EMPTY(FIFO_buf) == fifo_empty)
		return fifo_empty;

	(FIFO_buf->count)--;
	*data = *(FIFO_buf->base);
	(FIFO_buf->base)++;
	return fifo_no_error;
}
