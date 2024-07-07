#include <stdio.h>      // C library for input/output functions
#include <string.h>     // C library for string handling functions like 'strcpy' and 'strcat'

int main(void) {

    /* SOLOMON's Code:
    Functionality 1: Initial Setup Phase
    This section displays a welcome message and prompts the user to enter their full name.
    After which the user is greeted by the entered name
    */

    // Variable, Data-type declaration
    char programName[] = "Interactive Student Record System v1.0";
    char firstName[15];     // allocates 15 character memory space for firstname
    char lastName[15];      // allocates 15 character memory space for lastname
    char userName[30];      // allocates 30 character memory space for both first and lastname

    printf("Hello, Welcome to the %s \n Please enter your name to proceed \n", programName);

    // prompts user for their first name
    printf("First Name: ");
    fgets(firstName, 15, stdin);
    // removes added newline space if present
    firstName[strcspn(firstName, "\n")] = '\0';

    // prompts user for their last name
    printf("Last Name: ");
    fgets(lastName, 15, stdin);
    // removes added newline space if present
    lastName[strcspn(lastName, "\n")] = '\0';

    // Concatenate's firstName and LastName as userName
    strcpy(userName, firstName);
    strcat(userName, " ");
    strcat(userName, lastName);

    // Greets user and prints concatenated user name
    printf("\n");  // Inserts space before next code
    printf("Good day!, %s", userName);

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

    printf("\n");  // Inserts space before next code
    printf("\n""Please enter your 8 digit Roll Number: ");
    scanf("%d", &rollNumber);

    printf("%d", rollNumber);



















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
     * "%p" = accesses the RAM location of a variable
    */

        /*
    // Okon's Code: Question 1 & 2
    printf("Hello and welcome to the Student Record System!\n");

    char name[20];
    printf("Please tell me your name: ");
    fgets(name, 20, stdin);
    printf("Good day %s", name);

    char studentName[20];
    int rollNum[1000];
    double marks[1000];

    printf("Testing a version for christine, have a nice day\n");
    printf("This is a demo for Able Inception");
    */

    return 0;
}
