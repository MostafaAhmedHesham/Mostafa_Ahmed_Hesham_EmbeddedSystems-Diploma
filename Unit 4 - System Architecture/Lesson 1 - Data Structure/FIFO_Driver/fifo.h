/*
 * fifo.h
 *
 *  Created on: Sep 16, 2023
 *      Author: AEMYS
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "platform_types.h"
#define element_type uint32

typedef struct {
	uint32 length;
	element_type *base;
	element_type *head;
	uint32 count;
}FIFO_Buf_t;

typedef enum {
	fifo_no_error,
	fifo_full,
	fifo_empty,
	fifo_Null
}FIFO_status;


/* If you use NULL function first time with a buffer put flag = 0 otherwise put it to 1 */
FIFO_status FIFO_NULL (FIFO_Buf_t * FIFO_buf,element_type *buf, uint8 flag);
FIFO_status FIFO_FULL (FIFO_Buf_t * FIFO_buf);
FIFO_status FIFO_EMPTY (FIFO_Buf_t * FIFO_buf);
FIFO_status FIFO_init(FIFO_Buf_t * FIFO_buf, element_type *buf, uint32 length);
FIFO_status FIFO_add(FIFO_Buf_t * FIFO_buf, element_type *buf, element_type data);
FIFO_status FIFO_get(FIFO_Buf_t * FIFO_buf, element_type *buf, element_type *data);
#endif /* FIFO_H_ */
