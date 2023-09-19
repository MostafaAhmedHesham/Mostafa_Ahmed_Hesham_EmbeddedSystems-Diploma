/*
 * lifo.h
 *
 *  Created on: Sep 16, 2023
 *      Author: AEMYS
 */

#ifndef LIFO_H_
#define LIFO_H_

#include "platform_types.h"
#define element_type uint32

typedef struct {
	uint32 length;
	element_type *base;
	element_type *head;
	uint32 count;
}LIFO_Buf_t;

typedef enum {
	lifo_no_error,
	lifo_full,
	lifo_empty,
	lifo_Null
}LIFO_status;


/* If you use NULL function first time with a buffer but flag = 0 otherwise but it to 1 */
LIFO_status LIFO_NULL (LIFO_Buf_t * lifo_buf,element_type *buf, uint8 flag);
LIFO_status LIFO_FULL (LIFO_Buf_t * lifo_buf);
LIFO_status LIFO_EMPTY (LIFO_Buf_t * lifo_buf);
LIFO_status LIFO_init(LIFO_Buf_t * lifo_buf, element_type *buf, uint32 length);
LIFO_status LIFO_add(LIFO_Buf_t * lifo_buf, element_type *buf, element_type data);
LIFO_status LIFO_get(LIFO_Buf_t * lifo_buf, element_type *buf, element_type *data);

#endif /* LIFO_H_ */
