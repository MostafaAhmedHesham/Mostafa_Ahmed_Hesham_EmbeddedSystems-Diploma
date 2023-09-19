/*
 * single_linked_list.c
 *
 *  Created on: Sep 18, 2023
 *      Author: AEMYS
 */
#include "single_linked_list.h"

void count_iterative (struct student *head)
{
	if (head == NULL)
		printf("The Linked List is Empty");
    struct student *ptr = head;
    uint32 counter = 0;
    while (ptr != NULL)
    {
        ptr = ptr->link;
        counter++;
    }
    printf("The Number of students is %d\n",counter);
}
uint32 count_recursion (struct student *head)
{
	if (head == NULL)
		return 0;
	else
	   return 1 + count_recursion(head->link);
}


void print(struct student *head)
{
	if (head == NULL)
		printf("The Linked List is Empty\n");
	struct student *ptr = head;
	uint32 counter = 1;
	while (ptr != NULL)
	{
		printf("student Number %d ID = %s\n",counter,ptr->m_ID);
		printf("student Number %d Name = %s\n",counter,ptr->m_Name);
		printf("student Number %d Height = %d\n",counter,ptr->m_Height);
		printf("_____________________________________________________________\n");
		ptr = ptr->link;
		counter++;
	}
}

void create_first(struct student **head)
{
	struct student *ptr = malloc(sizeof(struct student));
	printf("Please Enter The ID of First student: ");
	clear;
	scanf("%s",ptr->m_ID);

	printf("Please Enter The Name of First student: ");
	clear;
	gets(ptr->m_Name);

	printf("Please Enter The Height First student: ");
	clear;
	scanf("%d",&ptr->m_Height);
	ptr->link = NULL;
	(*head) = ptr;
}

void add_student(struct student *head)
{
	struct student *add = malloc(sizeof(struct student));
	printf("Please Enter The ID of student: ");
	clear;
	scanf("%s",add->m_ID);

	printf("Please Enter The Name of student: ");
	clear;
	gets(add->m_Name);

	printf("Please Enter The Height student: ");
	clear;
	scanf("%d",&add->m_Height);
	add->link = NULL;

	struct student *ptr = head;
	while(ptr->link != NULL) 	/*Reading the link data of the student before shifting it*/
		ptr = ptr->link;

	ptr->link = add;
}
void delete_first(struct student **head)
{
	struct student *temp = *head;

	*head = (*head) -> link;

	free(temp);
	temp = NULL;
}


void delete_last (struct student *head)
{
	struct student *temp = NULL;
	struct student *ptr = head;

	while (ptr->link->link != NULL)
		ptr = ptr->link;

	temp = ptr->link;
	ptr->link = NULL;
	free(temp);
	temp = NULL;
}

void delete_position(struct student **head,	uint32 position)
{
	struct student *ptr = *head;
	struct student *temp = NULL;

	if (position == 1)
		delete_first(head);
	else
	{
		for (int i = 0 ; i < position - 2 ; i++)
			ptr = ptr ->link;

		temp = ptr -> link;
		ptr -> link = temp -> link;
		free(temp);
		temp = NULL;
	}
}

void delete(struct student **head, char_t*id)
{
	struct student *ptr = malloc(sizeof(struct student));
	ptr = *head;
	uint32 count = 1;
	while(strcmp(ptr->m_ID, id)!= 0)
	{
		ptr = ptr->link;
		count++;
	}
	if (ptr->link == NULL)
		delete_last(*head);
	else if (count == 1)
		delete_first(head);
	else
		delete_position(head,count);
}



void delete_all(struct student **head)
{
	struct student *temp = *head;

	while (temp != NULL)
	{
		*head = (*head)->link;
		free(temp);
		temp = *head;
	}
}

void reverse (struct student **head)
{
	struct student *switcher = *head;
	struct student *old_adress = *head;


	switcher = (*head) -> link;
	(*head) -> link = NULL;

	while (switcher != NULL)
	{
		*head = switcher;
		switcher = switcher -> link;
		(*head) -> link = old_adress;
		old_adress = *head;
	}
}

void index_end(struct student *head, uint32 index)
{
    struct student *main_ptr = head;
    struct student *ref_ptr = head;
    uint32 count = 0;

    while (ref_ptr != NULL)
    {
        ref_ptr = ref_ptr->link;
        count++;
        if (count > index)	//To keep the the required distance between two pointers
        	main_ptr = main_ptr->link;
    }
    printf("Student Number %d from the end ID = %s\n", index, main_ptr->m_ID);
    printf("Student Number %d from the end Name = %s\n", index, main_ptr->m_Name);
    printf("Student Number %d from the end Height = %d\n", index, main_ptr->m_Height);
}
void middle_student(struct student *head)
{
    struct student *one_step = head;
    struct student *two_steps = head;
    uint32 count = 1;

    while (two_steps->link != NULL)
    {
    	one_step = one_step->link;
    	if(two_steps->link->link == NULL)
    		two_steps = two_steps->link;
    	else
    		two_steps = two_steps->link->link;
    	count++;
    }
    printf("Middle Student no. %d and his ID = %s\n", count, one_step->m_ID);
    printf("Middle Student no. %d and his Name = %s\n", count, one_step->m_Name);
    printf("Middle Student no. %d and his Height = %d\n", count, one_step->m_Height);
}
void loop_fault(struct student *head)
{
    struct student *one_step = head;
    struct student *two_steps = head;
    uint32 count = 1;

    while (one_step && two_steps && two_steps->link)
    {
    	one_step = one_step->link;
    	if(two_steps->link->link == NULL)
    		two_steps = two_steps->link;
    	else
    		two_steps = two_steps->link->link;
    	if(one_step == two_steps)
    		printf("Loop Detected");
    	count++;
    }
}


















