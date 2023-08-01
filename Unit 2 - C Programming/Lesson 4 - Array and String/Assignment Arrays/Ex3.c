/*
 * main.c
 *
 *  Created on: Jul 23, 2023
 *      Author: AEMYS
 */
#include "stdio.h"
#include "stdlib.h"
#define clear fflush(stdin); fflush(stdout)

void print_matrix(int row,int col,int arr[row][col])
{
	for (int i = 0 ; i < row ; i++)
	{
		for (int j = 0 ; j < col ; j++)
			printf("%d ",arr[i][j]);
		printf("\n");
	}
}

int main ()
{
	int row,col;
	printf("Enter the number of Rows: ");
	clear;
	scanf("%d",&row);
	printf("Enter the number of Columns: ");
	clear;
	scanf("%d",&col);
	int arr[row][col],transpose_arr[col][row];

	for (int i = 0 ; i < row ; i++)
	{
		for (int j = 0 ; j < col ; j++)
		{
			printf("Enter Element[%d][%d]: ",i+1,j+1);
			clear;
			scanf("%d",&arr[i][j]);
		}
	}
	for (int i = 0 ; i < row ; i++)
	{
		for (int j = 0 ; j < col ; j++)
			transpose_arr[j][i]= arr[i][j];
	}
	printf("Array You Entered\n");
	print_matrix(row,col,arr);

	printf("Transpose:\n");
	print_matrix(col,row,transpose_arr);
	return 0;
}
