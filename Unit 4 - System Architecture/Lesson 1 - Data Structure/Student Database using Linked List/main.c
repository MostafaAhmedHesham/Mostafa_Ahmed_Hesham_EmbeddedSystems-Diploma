/*
 * main.c
 *
 *  Created on: Sep 18, 2023
 *      Author: AEMYS
 */

#include "single_linked_list.h"

void menu(struct student **head);

int main ()
{
	struct student *head = malloc(sizeof(struct student));
	menu(&head);
	return 0;
}


void menu(struct student **head)
{
	uint32 choice,count=0,end_index;
	uint8 again;
	char_t id[10];
	static uint8 flag=0;
	printf("\t Choose one from the following options\n");
	printf("1. ADD Student\n");
	printf("2. Delete Student\n");
	printf("3. View Students\n");
	printf("4. Delete all Students\n");
	printf("5. Students Count\n");
	printf("6. Reverse Students List\n");
	printf("7. Get student info by index from end \n");
	printf("8. Get Middle student info\n");
	printf("9. Student List loop fault detection\n");
	printf("10. End\n");
	printf("Enter option number: ");
	clear;
	scanf("%d",&choice);
	printf("_____________________________________________________________\n");
	switch (choice)
	{
		case 1:
			if (flag == 0)
			{
				create_first(head);
				flag++;
			}
			else
				add_student(*head);
			printf("Do you one to another operation ? (y or n): ");
			clear;
			scanf("%c",&again);
			if (again =='y' || again == 'Y')
				{
					printf("_____________________________________________________________\n");
					menu(head);
				}
			break;
		case 2:
			printf("Enter The Student ID: ");
			clear;
			scanf("%s",id);
			delete(head, id);
			printf("Do you one to another operation ? (y or n): ");
			clear;
			scanf("%c",&again);
			if (again =='y' || again == 'Y')
				{
					printf("_____________________________________________________________\n");
					menu(head);
				}
			break;
		case 3:
			print(*head);
			printf("Do you one to another operation ? (y or n): ");
			clear;
			scanf("%c",&again);
			if (again =='y' || again == 'Y')
				{
					printf("_____________________________________________________________\n");
					menu(head);
				}
			break;
		case 4:
			delete_all(head);
			flag = 0;
			printf("Do you one to another operation ? (y or n): ");
			clear;
			scanf("%c",&again);
			if (again =='y' || again == 'Y')
				{
					printf("_____________________________________________________________\n");
					menu(head);
				}
			break;
		case 5:
			//count_iterative(*head);
			count = count_recursion(*head);
		    printf("The Number of students is %d\n",count);
			printf("Do you one to another operation ? (y or n): ");
			clear;
			scanf("%c",&again);
			if (again =='y' || again == 'Y')
				{
					printf("_____________________________________________________________\n");
					menu(head);
				}
			break;
		case 6:
			reverse(head);
			printf("Do you one to another operation ? (y or n): ");
			clear;
			scanf("%c",&again);
			if (again =='y' || again == 'Y')
				{
					printf("_____________________________________________________________\n");
					menu(head);
				}
			break;
		case 7:
			printf("Enter The Student Index from End: ");
			clear;
			scanf("%d",&end_index);
			index_end(*head, end_index);
			printf("Do you one to another operation ? (y or n): ");
			clear;
			scanf("%c",&again);
			if (again =='y' || again == 'Y')
				{
					printf("_____________________________________________________________\n");
					menu(head);
				}
			break;
		case 8:
			middle_student(*head);
			printf("Do you one to another operation ? (y or n): ");
			clear;
			scanf("%c",&again);
			if (again =='y' || again == 'Y')
				{
					printf("_____________________________________________________________\n");
					menu(head);
				}
			break;
		case 9:
			loop_fault(*head);
			printf("Do you one to another operation ? (y or n): ");
			clear;
			scanf("%c",&again);
			if (again =='y' || again == 'Y')
				{
					printf("_____________________________________________________________\n");
					menu(head);
				}
			break;
		case 10:
			break;
		default:
			printf("Wrong choice\n");
			printf("_____________________________________________________________\n");
			menu(head);
	}
}
