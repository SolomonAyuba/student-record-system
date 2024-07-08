 // Created by Solomon Ayuba on 07/07/2024.

#include <stdio.h>      // C library for input/output functions
#include <string.h>     // C library for string handling functions like 'strcpy' and 'strcat'

struct Student {
    // Struct: is a C data structure initialized to store groups of data types for various students' info.

    /*
     * Functionality 1 & 2: Initial Setup and Data Storage Phase
     * In this section Student's information, including name, roll number, and marks are stored using appropriate
     * data types.
    */

    // Variable, Data-type declaration
    char programName[50];   // allocates 50 character memory space for string program name
    char firstName[15];     // allocates 15 character memory space for student's first name input
    char lastName[15];      // allocates 15 character memory space for student's last name input
    char userName[30];      // allocates 30 character memory space for both first and last name

    int rollNumber;         // single integer for student roll number
    int marks[8];           // array for storing marks for 8 courses

    char courses[8][50];    // array for storing names of 8 courses, allocating 50 character mem space for each
    int passMark;
};

int main(void) {
    // The main method section where we use the different attributes from the Struct session above
    /* This section displays a welcome message and prompts the user to enter their full name.
     * After which the user is greeted by the entered name */

    struct Student student1;

    // Displays the program name
    strcpy(student1.programName, "Interactive Student Record System v1.0");
    printf("Hello, Welcome to the %s\nPlease enter your name to proceed\n", student1.programName);

    // Prompt student for their first name
    printf("First Name: ");
    fgets(student1.firstName, 15, stdin);
    student1.firstName[strcspn(student1.firstName, "\n")] = '\0'; // removes added newline space if present

    // Prompt student for their last name
    printf("Last Name: ");
    fgets(student1.lastName, 15, stdin);
    student1.lastName[strcspn(student1.lastName, "\n")] = '\0';  // removes added newline space if present

    // Concatenate firstName and lastName as userName
    strcpy(student1.userName, student1.firstName);
    strcat(student1.userName, " ");
    strcat(student1.userName, student1.lastName);

    // Greet student printing their concatenated username
    printf("\n");  // Inserts empty line before next code
    printf("Good day, %s!\n", student1.userName);

    // Prompt student to enter their roll number
    printf("\nPlease enter your 4-digit Roll Number: ");
    scanf("%d", &student1.rollNumber);
    printf("Roll Number: %d\n", &student1.rollNumber);

    // Consume leftover newline character
    getchar();

    /*
     * Functionality 3: Input and Output Phase
     * This section takes 8 courses scores from the student and displays their mark
     */

    // Assigning 8 courses to the 'Courses' Array
    strcpy(student1.courses[0], "Intro to Data Science");
    strcpy(student1.courses[1], "Intro to R Programming");
    strcpy(student1.courses[2], "Computer Programming I");
    strcpy(student1.courses[3], "Discrete Structures");
    strcpy(student1.courses[4], "Intro to Numerical Analysis");
    strcpy(student1.courses[5], "Mathematical Methods I");
    strcpy(student1.courses[6], "Sets, Logic & Algebra");
    strcpy(student1.courses[7], "Entrepreneurship");

    printf("\nWhat's your score for the following 8 courses (0-100):\n");

    // Prompts student to input scores for each 8 courses
    for (int i = 0; i < 8; i++) {
        printf("[%d] %s: ", i + 1, student1.courses[i]);
        scanf("%d", &student1.marks[i]);
    }

    printf("\nYOUR RESULTS ARE HERE\n");
    student1.passMark = 40;     // Declaring the passmark as 40

    // Displays the results of the courses
    for (int i = 0; i < 8; i++) {
        if (student1.marks[i] >= student1.passMark) {
            printf("You passed: %s\n", student1.courses[i]);
        } else {
            printf("Sorry, you failed : %s\n", student1.courses[i]);
        }
    }

    /*
     * Functionality 4: Student Records Management Phase
     * In this section:
     * 🧹 We implement a loop that allows students to input information for multiple students until
     *    the student decides to exit.
     * 🧹 Create an array to store information for multiple students, with the ability to add, remove,
     *      and modify student records.
     * 🧹 Implement functions for adding, modifying, and displaying student records. Ensuring these functions take
     *      appropriate arguments and return relevant information.
     */




    return 0;
}
