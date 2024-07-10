#include <stdio.h>      // C library for input/output functions
#include <string.h>     // C library for string handling functions like 'strcpy' and 'strcat'
#include <stdlib.h>     // C library for Dynamic Memory Allocation. Used in this code to free memory when not in use
#define STARTING_CAPACITY 10   // C preprocessor directive used to define macros. Used to create a constant of
                              //  10 students as starting capcity for dynamic memory allocation

// The Struct function stores groups of various data types for various student. I call it Array on steriods.
struct Student {
    // Struct: is a C data structure initialized to store groups of data types for various students info.

    // Variable, Data-type declaration
    char firstName[15];     // allocates 15 character memory space for student's first name input
    char lastName[15];      // allocates 15 character memory space for student's last name input
    char userName[30];      // allocates 30 character memory space for both first and last name

    int rollNumber;         // single integer for student roll number
    int marks[8];           // array for storing marks for 8 courses

    char courses[8][50];    // array for storing names of 8 courses, allocating 50 character mem space for each
    int passMark;
};

// This function assigns the strings of character to the courses variable declared in the Struct above
void initializeCourses(char courses[8][50]) {
    strcpy(courses[0], "Intro to Data Science");
    strcpy(courses[1], "Intro to R Programming");
    strcpy(courses[2], "Computer Programming I");
    strcpy(courses[3], "Discrete Structures");
    strcpy(courses[4], "Intro to Numerical Analysis");
    strcpy(courses[5], "Mathematical Methods I");
    strcpy(courses[6], "Sets, Logic & Algebra");
    strcpy(courses[7], "Entrepreneurship");
}

// This function handles the requested input prompt provided by the student
void inputStudentData(struct Student* student) {
    // Prompt student for their first name
    printf("First Name: ");
    fgets(student->firstName, 15, stdin);
    student->firstName[strcspn(student->firstName, "\n")] = '\0'; // removes added newline space if present

    // Prompt student for their last name
    printf("Last Name: ");
    fgets(student->lastName, 15, stdin);
    student->lastName[strcspn(student->lastName, "\n")] = '\0';  // removes added newline space if present

    // Concatenate firstName and lastName as userName
    strcpy(student->userName, student->firstName);
    strcat(student->userName, " ");
    strcat(student->userName, student->lastName);

    // Greet student printing their concatenated username
    printf("\n");  // Inserts empty line before next code
    printf("Good day, %s!\n", student->userName);

    // Prompt student to enter their roll number
    printf("\nPlease enter your 4-digit Roll Number: ");
    scanf("%d", &student->rollNumber);
    // This function Consumes the leftover \n (newline) character after the student enters the roll number.
    getchar();

    // Initialize courses
    initializeCourses(student->courses);

    printf("\nWhat's your score for the following 8 courses (0-100):\n");

    // Prompts student to input scores for each 8 courses
    for (int i = 0; i < 8; i++) {
        printf("[%d] %s: ", i + 1, student->courses[i]);
        scanf("%d", &student->marks[i]);
    }
    getchar();  // This function Consumes the leftover \n (newline) character after the student enters their marks
}

// This Structure function adds students to our record utilizing the realloc() function for dynamic memory allocation
struct Student* addStudent(struct Student* students, int* studentCount, int* capacity) {
    if (*studentCount >= *capacity) {
        *capacity *= 2;
        students = realloc(students, (*capacity) * sizeof(struct Student));
        if (students == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }
    inputStudentData(&students[*studentCount]);
    (*studentCount)++;
    return students;
}

// This function using the roll number removes existing students from our record
void removeStudent(struct Student students[], int* studentCount, int rollNumber) {
    int index = -1;
    for (int i = 0; i < *studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("The Student with the roll number %d doesn't exist on our record.\n", rollNumber);
        return;
    }
    for (int i = index; i < *studentCount - 1; i++) {
        students[i] = students[i+1];
    }
    (*studentCount)--;
    printf("The Student with the roll number %d has successfully been removed.\n", rollNumber);
}

// This function using the roll number modifies existing student's information
void modifyStudent(struct Student students[], int studentCount, int rollNumber) {
    int index = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            index = 1;
            break;
        }
    }
    if (index == -1) {
        printf("The Student with the roll number %d doesn't exist on our record.\n", rollNumber);
        return;
    }
    printf("Modifying student with the roll number %d:\n", rollNumber);
    inputStudentData(&students[index]);

}

// This function displays student result as inputed by the student
void displayStudentResults(struct Student* student) {
    printf("\n   Fullname: %s \n   Roll Number: %d\nSEMESTER RESULT\n", student->userName, student->rollNumber);
    student->passMark = 40;     // Declaring the pass mark as 40

    for (int i = 0; i < 8; i++) {
        if (student->marks[i] >= student->passMark) {
            printf("  ✅ Hurray! you passed: %s\n", student->courses[i]);
        } else {
            printf("  ❌ Sorry, you failed: %s\n", student->courses[i]);
        }
    }
}

// This function saves the students full name, roll number, and marks in a .txt file.
void saveToFile(struct Student* students, int studentCount, const char* filename) {
    FILE* file = fopen(filename, "w");
    if(file == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %s %d", students[i].firstName, students[i].lastName, students[i].rollNumber);
        for (int j = 0; j < 8; j++) {
            fprintf(file, " %d", students[i].marks[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// This function loads the student record from a .txt file
void loadFromFile(struct Student** students, int* studentCount, int* capacity, const char* filename) {
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        printf("Could not open file for reading.\n");
        return;
    }
    while (1) {
        if (*studentCount >= *capacity) {
            *capacity *= 2;
            *students = realloc(*students, (*capacity) * sizeof(struct Student));
            if (*students == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }
        }
        struct Student* student = &(*students)[*studentCount];
        if(fscanf(file, "%14s %14s %d", student->firstName, student->lastName, &student->rollNumber) !=3) {
            break;
        }
        for (int i =0; i < 8; i++) {
            fscanf(file, "%d", &student->marks[i]);
        }
        strcpy(student->userName, student->firstName);
        strcat(student->userName, " ");
        strcat(student->userName, student->lastName);
        initializeCourses(student->courses);
        (*studentCount)++;
    }
    fclose(file);
}

// The main method that houses and drives the established data structure, functions, dynamic memory allocation
// file saving and loading functions
int main(void) {
    char programName[50] = "Interactive Student Record System v1.0";
    printf("Hello, Welcome to the %s\n", programName);

    int capacity = STARTING_CAPACITY;
    struct Student* students = malloc(capacity * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed. \n");
        return 1;
    }

    int studentCount = 0;

    loadFromFile(&students, &studentCount, &capacity, "Student Record System Questions.txt");

    while (1) {
        printf("\nWould you like to:");
        printf("\n1. Add a New Student");
        printf("\n2. Remove Existing Student");
        printf("\n3. Modify Existing Student Record");
        printf("\n4. Display all Students");
        printf("\n5. Quit\n");
        printf("\nChoose an option: ");

        int option;
        scanf("%d", &option);
        getchar(); // This function Consumes the leftover \n (newline) character after the student picks an option

        if (option == 1) {
            students = addStudent(students, &studentCount, &capacity);
        } else if(option == 2) {
            printf("Enter roll number of student to remove: ");
            int rollNumber;
            scanf("%d", &rollNumber);
            // This function Consumes the leftover \n (newline) character after the student enters their rollNumber
            getchar();
            removeStudent(students, &studentCount, rollNumber);
        } else if(option == 3) {
            printf("Enter roll number of student to modify: ");
            int rollNumber;
            scanf("%d", &rollNumber);
            // This function Consumes the leftover \n (newline) character after the student enters the rollNumber
            getchar();
            modifyStudent(students, studentCount, rollNumber);
        } else if(option == 4) {
            for(int i = 0; i < studentCount; i++) {
                printf("\nSTUDENT INFORMATION\n   Student Number: %d", i + 1);
                displayStudentResults(&students[i]);
            }
        } else if(option == 5) {
            saveToFile(students, studentCount, "Student Record System Questions.txt");
            break;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }

    free(students);

    printf("\nHurray! you registered %d number of student.\nThank you for using our %s software",
        studentCount, programName);


    return 0;
}
