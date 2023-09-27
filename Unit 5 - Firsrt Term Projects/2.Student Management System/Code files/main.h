/*
 * main.h
 *
 *  Created on: Sep 24, 2023
 *      Author: AEMYS
 */
#ifndef MAIN_H_
#define MAIN_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define clear fflush(stdin); fflush(stdout)

struct Sinfo
{
	char fname[50];
	char lname[50];
	int roll;
	float GPA;
    char courses[3][50]  ;//Courses registered by the student
}st_base[55];


void add_student_file();
void add_student_manually();
void find_by_id();
void find_by_firstName();
void find_by_course();
void total_number_of_students();
void del_student_by_id();
void update_student_by_id();
void show_all_students_information();


#endif /* MAIN_H_ */
