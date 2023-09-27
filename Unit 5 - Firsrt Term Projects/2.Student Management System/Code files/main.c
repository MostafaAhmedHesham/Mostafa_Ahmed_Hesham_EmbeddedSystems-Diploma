/*
 * main.c
 *
 *  Created on: Sep 24, 2023
 *      Author: AEMYS
 */
#include "main.h"

int main() {
    int choice;

    do {
        printf("Menu:\n");
        printf("1. Add a student from a file\n");
        printf("2. Add a student manually\n");
        printf("3. Find a student by ID\n");
        printf("4. Find a student by first name\n");
        printf("5. Find students by course\n");
        printf("6. Total number of students\n");
        printf("7. Delete a student by ID\n");
        printf("8. Update a student by ID\n");
        printf("9. Show all students' information\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        clear;
        scanf("%d", &choice);
        printf("========================================================\n");

        switch (choice) {
            case 1:
                add_student_file();
                break;
            case 2:
                add_student_manually();
                break;
            case 3:
                find_by_id();
                break;
            case 4:
                find_by_firstName();
                break;
            case 5:
                find_by_course();
                break;
            case 6:
                total_number_of_students();
                break;
            case 7:
                del_student_by_id();
                break;
            case 8:
                update_student_by_id();
                break;
            case 9:
                show_all_students_information();
                break;
            case 0:
                printf("\t\t----------->Exiting program.\n");
                break;
            default:
                printf("\t\t----------->Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

/**
 * Function: add_student_file
 * Description: Reads student information from a file and adds it to the student database.
 * Parameters: None
 * Returns: None
 */
int studentCount = 0; // Keep track of the number of students
void add_student_file() {
    FILE *fp;
    fp = fopen("database.txt", "r");

    if (fp == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[100];

    while (fgets(line, sizeof(line), fp)) {
        int counter = 1;
        struct Sinfo new_s;
        char *token = strtok(line, " ");

        while (token != NULL) {
            switch (counter) {
                case 1:
                    new_s.roll = atoi(token);
                    break;
                case 2:
                    strcpy(new_s.fname, token);
                    break;
                case 3:
                    strcpy(new_s.lname, token);
                    break;
                case 4:
                    new_s.GPA = atof(token);
                    break;
                default:
                    if (counter - 5 <= 2) {
                        strcpy(new_s.courses[counter - 5], token);
                    }
            }
            token = strtok(NULL, " ");
            counter++;
        }

        // Add the new student to st_base array
        if (studentCount < 55) {
            st_base[studentCount] = new_s;
            studentCount++;
        } else {
            printf("Maximum number of students reached.\n");
            break;
        }
    }

    fclose(fp);
    printf("Student data imported successfully.\n");
}

/**
 * Function: add_student_manually
 * Description: Manually adds a student's information to the student database.
 * Parameters: None
 * Returns: None
 */

void add_student_manually() {
    if (studentCount < 55) {
        printf("Enter student's first name: ");
        clear;
        scanf("%s", st_base[studentCount].fname);
        printf("Enter student's last name: ");
        clear;
        scanf("%s", st_base[studentCount].lname);
        clear;
        printf("Enter student's roll number: ");
        clear;
        scanf("%d", &st_base[studentCount].roll);
        printf("Enter student's GPA: ");
        clear;
        scanf("%f", &st_base[studentCount].GPA);
        printf("Enter up to 3 courses (one per line, empty line to finish):\n");
        for (int i = 0; i < 3; i++) {
            printf("Course %d: ", i + 1);
            clear;
            scanf("%s", st_base[studentCount].courses[i]);

            // Stop input if the user enters an empty line
            if (st_base[studentCount].courses[i][0] == '\0') {
                break;
            }
        }

        studentCount++;
        printf("\t\t----------->Student added successfully.\n");
        printf("========================================================\n");
    } else {
        printf("\t\t----------->Maximum number of students reached.\n");
        printf("========================================================\n");
    }
}

/**
 * Function: find_by_id
 * Description: Finds and displays a student's information by their roll number.
 * Parameters: None
 * Returns: None
 */
void find_by_id() {
    int searchRoll;
    printf("Enter student's roll number to find: ");
    clear;
    scanf("%d", &searchRoll);

    printf("===============================================================\n");

    int found = 0; // To check if the student was found

    for (int i = 0; i < studentCount; i++) {
        if (st_base[i].roll == searchRoll) {
            printf("\t\t----------->Student found:\n");
            printf("First Name: %s\n", st_base[i].fname);
            printf("Last Name: %s\n", st_base[i].lname);
            printf("Roll Number: %d\n", st_base[i].roll);
            printf("GPA: %.2f\n", st_base[i].GPA);
            printf("Courses:\n");
            for (int j = 0; j < 3; j++) {
                if (st_base[i].courses[j][0] != '\0') {
                    printf("  %s\n", st_base[i].courses[j]);
                }
            }
            printf("========================================================\n");
            found = 1;
            break; // Student found, exit loop
        }
    }

    if (!found) {
        printf("\t\t----------->Student with roll number %d not found.\n", searchRoll);
        printf("===============================================================\n");
    }
}


/**
 * Function: find_by_firstName
 * Description: Finds and displays students' information by their first name.
 * Parameters: None
 * Returns: None
 */
void find_by_firstName() {
    char searchFirstName[50];
    printf("Enter student's first name to find: ");
    clear;
    scanf("%s", searchFirstName);

    printf("===========================================================================\n");

    int found = 0; // To check if any students were found with the given first name

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(st_base[i].fname, searchFirstName) == 0) {
            printf("\t\t----------->Student found:\n");
            printf("First Name: %s\n", st_base[i].fname);
            printf("Last Name: %s\n", st_base[i].lname);
            printf("Roll Number: %d\n", st_base[i].roll);
            printf("GPA: %.2f\n", st_base[i].GPA);
            printf("Courses:\n");
            for (int j = 0; j < 3; j++) {
                if (st_base[i].courses[j][0] != '\0') {
                    printf("  %s\n", st_base[i].courses[j]);
                }
            }
            printf("========================================================\n");
            found = 1;
        }
    }

    if (!found) {
        printf("\t\t----------->No students found with the first name: %s\n", searchFirstName);
        printf("===========================================================================\n");
    }
}

/**
 * Function: find_by_course
 * Description: Finds and displays students' information by a specific course.
 * Parameters: None
 * Returns: None
 */

void find_by_course() {
    char searchCourse[100];
    printf("Enter course ID to find students: ");
    clear;
    scanf("%s", searchCourse);

    printf("==================================================================\n");

    int found = 0; // To check if any students were found for the given course

    for (int i = 0; i < studentCount; i++) {
        for (int j = 0; j < 3; j++) {
            if (strcmp(st_base[i].courses[j], searchCourse) == 0) {
                found = 1;
                break; // Student found for the course, exit inner loop
            }
        }
    }
    if (found)
    {
    	printf("\t\t----------->Students found for course ID: %s\n", searchCourse);
        for (int i = 0; i < studentCount; i++) {
            for (int j = 0; j < 3; j++) {
                if (strcmp(st_base[i].courses[j], searchCourse) == 0) {
                    printf("First Name: %s\n", st_base[i].fname);
                    break; // Student found for the course, exit inner loop
                }
            }
        }
        printf("==================================================================\n");
    }

    if (!found) {
        printf("\t\t----------->No students found for course ID: %s\n", searchCourse);
        printf("==================================================================\n");
    }
}



/**
 * Function: total_number_of_students
 * Description: Displays the total number of students in the database.
 * Parameters: None
 * Returns: None
 */

void total_number_of_students() {
    printf("\t\t----------->Total number of students: %d\n", studentCount);
    printf("=========================================================\n");
}


/**
 * Function: del_student_by_id
 * Description: Deletes a student from the database by their roll number.
 * Parameters: None
 * Returns: None
 */

void del_student_by_id() {
    int deleteRoll;
    printf("Enter student's roll number to delete: ");
    clear;
    scanf("%d", &deleteRoll);

    for (int i = 0; i < studentCount; i++) {
        if (st_base[i].roll == deleteRoll) {
            // Shift all elements after the found student to the left
            for (int j = i; j < studentCount - 1; j++) {
                st_base[j] = st_base[j + 1];
            }
            studentCount--;
            printf("\t\t----------->Student with roll number %d deleted.\n", deleteRoll);
            printf("================================================================\n");
            return;
        }
    }

    printf("\t\t----------->Student with roll number %d not found.\n", deleteRoll);
    printf("===================================================================\n");
}


/**
 * Function: update_student_by_id
 * Description: Updates a student's information in the database by their roll number.
 * Parameters: None
 * Returns: None
 */
void update_student_by_id() {
    int updateRoll;
    printf("Enter student's roll number to update: ");
    clear;
    scanf("%d", &updateRoll);

    printf("===================================================================\n");

    int found = 0; // To check if the student was found

    for (int i = 0; i < studentCount; i++) {
        if (st_base[i].roll == updateRoll) {
            printf("Enter updated information for the student:\n");
            printf("Enter student's first name: ");
            clear;
            scanf("%s", st_base[i].fname);
            printf("Enter student's last name: ");
            clear;
            scanf("%s", st_base[i].lname);
            printf("Enter student's roll number: ");
            clear;
            scanf("%d", &st_base[i].roll);
            printf("Enter student's GPA: ");
            clear;
            scanf("%f", &st_base[i].GPA);

            printf("Enter up to 3 courses (one per line, empty line to finish):\n");
            for (int j = 0; j < 3; j++) {
                printf("Course %d: ", j + 1);
                clear;
                scanf("%s", st_base[i].courses[j]);

                // Stop input if the user enters an empty line
                if (st_base[i].courses[j][0] == '\0') {
                    break;
                }
            }

            printf("\t\t----------->Student with roll number %d updated.\n", updateRoll);
            printf("===================================================================\n");
            found = 1;
            break; // Student found, exit loop
        }
    }

    if (!found) {
        printf("\t\t----------->Student with roll number %d not found.\n", updateRoll);
        printf("===================================================================\n");
    }
}


/**
 * Function: show_all_students_information
 * Description: Displays information for all students in the database.
 * Parameters: None
 * Returns: None
 */
void show_all_students_information() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("All Students:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Student %d:\n", i + 1);
        printf("First Name: %s\n", st_base[i].fname);
        printf("Last Name: %s\n", st_base[i].lname);
        printf("Roll Number: %d\n", st_base[i].roll);
        printf("GPA: %.2f\n", st_base[i].GPA);

        printf("Courses:\n");
        for (int j = 0; j < 3; j++) {
            if (st_base[i].courses[j][0] != '\0') {
                printf("  %s\n", st_base[i].courses[j]);
            }
        }
        printf("==========================\n");
    }
}







