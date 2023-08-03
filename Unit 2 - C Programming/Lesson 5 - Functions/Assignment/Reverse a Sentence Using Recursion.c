/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define clear fflush(stdin); fflush(stdout)


void reverse(int size,int count,char arr[size])
{
	char temp = arr[size-1];
	arr[size-1] = arr[count];
	arr[count] = temp;
	size--;
	count++;
	if(size != count && (size-count)>1)
		reverse(size,count,arr);
}

int main ()
{
	char sent[100];
	int size;
	printf("Enter a sentence: ");
	clear;
	gets(sent);
	size = strlen(sent);
	reverse(size,0,sent);
	printf("%s",sent);
	return 0;
}
