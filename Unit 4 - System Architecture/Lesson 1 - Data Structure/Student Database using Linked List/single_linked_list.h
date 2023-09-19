/*
 * single_linked_list.h
 *
 *  Created on: Sep 18, 2023
 *      Author: AEMYS
 */

#ifndef SINGLE_LINKED_LIST_H_
#define SINGLE_LINKED_LIST_H_

#include "platform_types.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define clear fflush(stdin); fflush(stdout)

struct student
{
    char_t m_ID[10];
    char_t m_Name[100];
    uint32 m_Height;
    uint32 data;
    struct student *link;
};

void count_iterative (struct student *head);
uint32 count_recursion (struct student *head);
void print(struct student *head);
void create_first(struct student **head);
void add_student(struct student *head);
void delete_first(struct student **head);
void delete_last (struct student *head);
void delete(struct student **head, char_t*id);
void delete_position(struct student **head, uint32 position);
void delete_all(struct student **head);
void reverse (struct student **head);
void index_end(struct student *head,uint32 index);
void middle_student(struct student *head);
void loop_fault(struct student *head);

#endif /* SINGLE_LINKED_LIST_H_ */
