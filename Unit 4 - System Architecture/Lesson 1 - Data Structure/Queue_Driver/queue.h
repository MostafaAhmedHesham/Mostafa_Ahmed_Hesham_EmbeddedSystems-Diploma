/*
 * queue.h
 *
 *  Created on: Sep 16, 2023
 *      Author: AEMYS
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "platform_types.h"
#define element_type uint8

typedef struct {
	uint32 length;
	element_type *base;
	element_type *head;
	element_type *tail;
}QUEUE_Buf_t;

typedef enum {
	queue_no_error,
	queue_full,
	queue_empty,
	queue_Null
}QUEUE_status;


/* If you use NULL function first time with a Queue put flag = 0 otherwise put it to 1 */
QUEUE_status QUEUE_NULL (QUEUE_Buf_t * QUEUE_buf, element_type *buf, uint8 flag);
QUEUE_status QUEUE_Full (QUEUE_Buf_t * QUEUE_buf, element_type *buf);
QUEUE_status QUEUE_init(QUEUE_Buf_t * QUEUE_buf, element_type *buf, uint32 length);
QUEUE_status QUEUE_add(QUEUE_Buf_t * QUEUE_buf, element_type *buf, element_type data);
QUEUE_status QUEUE_get(QUEUE_Buf_t * QUEUE_buf, element_type *buf, element_type *data);
void QUEUE_print(QUEUE_Buf_t *QUEUE_buf, element_type *buf );



#endif /* QUEUE_H_ */
