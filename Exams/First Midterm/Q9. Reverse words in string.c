/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#define clear fflush(stdin); fflush(stdout)


void reverse(char name[],int size)
{
	char spaceidx[20] = {0};//To Store the index of Spaces to determine start of each name
	int counter = 0;

	/* Store The index of Spaces keeping the first index 0 to save the index of first name (counter+1) */
	for (int i = 0 ; i < size ; i++)
	{
		if (name[i] == ' ')
		{
			spaceidx[counter+1] = i+1; // i+1 to store the beginning of each name
			counter++;
		}
	}

	/*Printing The Strings in reverse order*/
	for (int i = 0 ; i <= counter ; i++)
	{
		//Printing chars starting from index just after space
		int start = spaceidx[counter - i];
		while(name[start] != ' ' && name[start] != 0) //Stop if there is space or Null char
			{
				printf("%c",name[start]);
				start++;
			}
		printf(" ");
	}
}



int main() {
	char name[100] = {0};	//To store The input String
	int size = 0;
	printf ("Please Enter the Name: ");
	clear;
	gets(name);
	size = strlen(name);

	reverse(name,size);

    return 0;
}
