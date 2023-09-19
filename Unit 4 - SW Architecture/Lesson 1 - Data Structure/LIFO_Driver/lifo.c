/*
 * Lifo.c
 *
 *  Created on: Sep 16, 2023
 *      Author: AEMYS
 */

#include "lifo.h"

/* Check if LIFO is valid and allocated correctly*/

LIFO_status LIFO_NULL (LIFO_Buf_t *lifo_buf, element_type *buf , uint8 flag)
{
	/* Flag is to avoid re-initialization of head & base*/
	if (flag == 0)
	{
		//initialize head & base with data buffer
		lifo_buf->base = buf;
		lifo_buf->head = buf;
		flag++;
	}
	if (!lifo_buf->base || !lifo_buf->head)
		return lifo_Null;
	return lifo_no_error;
}

/*Check If LIFO is FULL*/
LIFO_status LIFO_FULL (LIFO_Buf_t * lifo_buf)
{
	if (lifo_buf->count >= lifo_buf->length)
		return lifo_full;
	return lifo_no_error;
}

/*Check If LIFO is EMPTY*/
LIFO_status LIFO_EMPTY (LIFO_Buf_t * lifo_buf)
{
	if (lifo_buf->count == 0)
		return lifo_empty;
	return lifo_no_error;
}



LIFO_status LIFO_init(LIFO_Buf_t * lifo_buf, element_type *buf, uint32 length)
{
	/* Check if LIFO is valid and allocated correctly*/
	if (LIFO_NULL(lifo_buf,buf,1) == lifo_Null)
		return lifo_Null;

	/*Initializing LIFO*/
	lifo_buf->length = length;
	lifo_buf->base = buf;
	lifo_buf->head = buf;
	lifo_buf->count = 0;
	return lifo_no_error;
}

LIFO_status LIFO_add(LIFO_Buf_t * lifo_buf, element_type *buf, element_type data)
{
	/* Check if LIFO is valid and allocated correctly*/
	if (LIFO_NULL(lifo_buf,buf,1) == lifo_Null)
		return lifo_Null;

	/*Check If LIFO is FULL*/
	if (LIFO_FULL(lifo_buf)==lifo_full)
		return lifo_full;

	*(lifo_buf->head) = data;
	(lifo_buf->count)++;
	lifo_buf->head++;
	return lifo_no_error;
}

LIFO_status LIFO_get(LIFO_Buf_t * lifo_buf, element_type *buf, element_type *data)
{
	/* Check if LIFO is valid and allocated correctly*/
	if (LIFO_NULL(lifo_buf,buf,1) == lifo_Null)
		return lifo_Null;

	/*Check If LIFO is Empty*/
	if (LIFO_EMPTY(lifo_buf) == lifo_empty)
		return lifo_empty;

	(lifo_buf->count)--;
	lifo_buf->head--;
	*data = *(lifo_buf->head);
	return lifo_no_error;
}
