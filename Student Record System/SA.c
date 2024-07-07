//
// Created by Solomon Ayuba on 07/07/2024.
//
#include <stdio.h>      // C library for input/output functions
#include <string.h>     // C library for string handling functions like 'strcpy' and 'strcat'


struct Student {
    /*
    Functionality 1: Initial Setup Phase
    This section displays a welcome message and prompts the user to enter their full name.
    After which the user is greeted by the entered name
    */

    // Variable, Data-type declaration
    char programName[50] = "Interactive Student Record System v1.0";
    char firstName[15];     // allocates 15 character memory space for firstname
    char lastName[15];      // allocates 15 character memory space for lastname
    char userName[30];      // allocates 30 character memory space for both first and lastname

    /*
   Functionality 2: Data Storage Phase
   This section stores students information, including name, roll number, and marks,
   using appropriate data types.
   (Recall that the student name has been stored in Initial Setup Phase)
   */

    // Allocates 8 characters for student roll number
    int rollNumber[8];
    // Allocates 2 characters for student marks across 8 courses
    int mark1[2];
    int mark2[2];
    int mark3[2];
    int mark4[2];
    int mark5[2];
    int mark6[2];
    int mark7[2];
    int mark8[2];

};

int main(void) {

    struct Student student1;
    printf("Hello, Welcome to the %s \n Please enter your name to proceed \n", student1.programName);

    // prompts user for their first name
    printf("First Name: ");
    fgets(student1.firstName, 15, stdin);
    // removes added newline space if present
    student1.firstName[strcspn(student1.firstName, "\n")] = '\0';

    // prompts user for their last name
    printf("Last Name: ");
    fgets(student1.lastName, 15, stdin);
    // removes added newline space if present
    student1.lastName[strcspn(student1.lastName, "\n")] = '\0';

    // Concatenate's firstName and LastName as userName
    strcpy(student1.userName, student1.firstName);
    strcat(student1.userName, " ");
    strcat(student1.userName, student1.lastName);

    // Greets user and prints concatenated user name
    printf("\n");  // Inserts space before next code
    printf("Good day!, %s", student1.userName);





    printf("\n");  // Inserts space before next code
    printf("\n""Please enter your 8 digit Roll Number: ");
    scanf("%d", &student1.rollNumber);

    printf("%d", student1.rollNumber);






















    /*
     * Brainstorming (ignore this portion)
     * //scanf("%s", firstName,);
     * printf("Hello, World!\n  ");
     * printf("my favourite %s is  %d", "Digit");
     * "%s = string character";
     * %c = character ;
     * "%d = integers";
     * "%f = float, double";
     * "%lf = float, double when using scan()";
    */
    return 0;
}
