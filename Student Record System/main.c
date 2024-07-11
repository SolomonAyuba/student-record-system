#include <ctype.h>
#include <stdio.h>      // C library for input/output functions
#include <string.h>     // C library for string handling functions like 'strcpy' and 'strcat'
#include <stdlib.h>     // C library for Dynamic Memory Allocation. Used in this code to free memory when not in use
/* C preprocessor directive used to define macros. Used to create a constant of 10 students as starting capcity for
 * dynamic memory allocation
 */
#define STARTING_CAPACITY 10

    /* The Struct function stores groups of various data types for various student. I call it Array on steriods.
     * Struct: is a C data structure initialized to store groups of data types for various students info.
     * We declare various variable and data-type as needed in the program.
     */
typedef struct {
    char firstName[15];     // allocates 15 character memory space for student's first name input
    char lastName[15];      // allocates 15 character memory space for student's last name input
    char userName[30];      // allocates 30 character memory space for both first and last name
    int rollNumber;         // integer for storing Students Roll Number
    int marks[8];           // array for storing Marks for 8 Courses
    char courses[8][50];    // array for storing names of 8 Courses, allocating 50 character memory space for each
    int passMark;           // integer for storing Pass Mark
} Student;

    /*
     * This function assigns character strings to the courses variable declared in the Struct above.
     * We define the title of the 8 courses as intended for this program
     */
void labelCourses(char courses[8][50]) {
    strcpy(courses[0], "Intro to Data Science");
    strcpy(courses[1], "Intro to R Programming");
    strcpy(courses[2], "Computer Programming I");
    strcpy(courses[3], "Discrete Structures");
    strcpy(courses[4], "Intro to Numerical Analysis");
    strcpy(courses[5], "Mathematical Methods I");
    strcpy(courses[6], "Sets, Logic & Algebra");
    strcpy(courses[7], "Entrepreneurship");
}

    /* This function employs the use of a pointer and prompts the Student to enter Firstname, Lastname, Roll Number and
     * Marks for the 8 courses.
     * We concatenate the inputed First and Lastname then assigns the values to the variable Username
     * The student is then welcomed and greeted by their Username
     * We prompt the user to enter a 4-digit roll Number which is validated before proceeding
     * We display the 8 courses and prompt the user to enter value for each using a for loop
    */
void inputStudentData(Student *student) {

    printf("First Name: ");
    fgets(student->firstName, 15, stdin);
    student->firstName[strcspn(student->firstName, "\n")] = '\0'; // removes added newline space if present

    printf("Last Name: ");
    fgets(student->lastName, 15, stdin);
    student->lastName[strcspn(student->lastName, "\n")] = '\0';  // removes added newline space if present

    strcpy(student->userName, student->firstName);
    strcat(student->userName, " ");
    strcat(student->userName, student->lastName);

    printf("\nGood day, %s!\n", student->userName);

    // Ask's user for 4digit roll number and validates the number.
    while (1) {
        printf("Please enter your 4-digit Roll Number: ");
        scanf("%d", &student->rollNumber);
        getchar(); // this function consumes leftover \n (newline) character after the roll number is entered

        if(student->rollNumber >= 1000 && student->rollNumber <= 9999) {
            break;
        } else {
            printf("\nOops! Invalid Roll Number. Please enter a valid 4-digit Number.\n");
        }
    }

    labelCourses(student->courses); // displays courses while executing next line

    // Prompts user for the mark of the 8 courses
    printf("\nWhat's your score for the following 8 courses (0-100):\n");

    for (int i = 0; i < 8; i++) {
        printf("[%d] %s: ", i + 1, student->courses[i]);
        scanf("%d", &student->marks[i]);
    }
    getchar();  // This function Consumes the leftover \n (newline) character after the student enters their marks
}

// This Structure function adds students to our record utilizing the realloc() function for dynamic memory allocation
Student *addStudent(Student *students, int *studentCount, int *capacity) {
    if (*studentCount >= *capacity) {
        *capacity *= 2;
        students = realloc(students, (*capacity) * sizeof(Student));
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
void removeStudent(Student students[], int *studentCount, int rollNumber) {
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
void modifyStudent(Student students[], int studentCount, int rollNumber) {
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
    } else {
        printf("Modifying student with the roll number %d:\n", rollNumber);
        inputStudentData(&students[index]);
    }
}

// This function displays student result as inputed by the student
void displayStudentResults(Student *student) {
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
void saveToFile(Student *students, int studentCount, const char* filename) {
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
void loadFromFile(Student **students, int *studentCount, int *capacity, const char *filename) {
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        printf("Could not open file for reading.\n");
        return;
    }
    while (1) {
        if (*studentCount >= *capacity) {
            *capacity *= 2;
            *students = realloc(*students, (*capacity) * sizeof(Student));
            if (*students == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }
        }
        Student *student = &(*students)[*studentCount];
        if(fscanf(file, "%14s %14s %d", student->firstName, student->lastName, &student->rollNumber) !=3) {
            break;
        }
        for (int i =0; i < 8; i++) {
            fscanf(file, "%d", &student->marks[i]);
        }
        strcpy(student->userName, student->firstName);
        strcat(student->userName, " ");
        strcat(student->userName, student->lastName);
        labelCourses(student->courses);
        (*studentCount)++;
    }
    fclose(file);
}

// This function allows the user to search for a student information using the roll number
void searchStudent (Student *students, int studentCount, int rollNumber) {
    for(int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("\nWe found this student, isn't that nice! \n\nSTUDENT'S INFORMATION");
            displayStudentResults(&students[i]);
            return;
        }
    }
    printf("Oop! The Roll Number %d isn't assigned to a student yet. Try again!\n", rollNumber);
}

// This function calculates and displays the average marks for all students
void calculateAverageMarks(Student *students, int studentCount) {
    if (studentCount == 0) {
        printf("You need to provide atleast 2 students to calculate their average marks.\n");
        return;
    }
    int totalMarks[8] = {0};
    for (int i = 0; i < studentCount; i++) {
        for (int j = 0; j < 8; j++) {
            totalMarks[j] += students[i].marks[j];
        }
    }
    printf("\nAVERAGE MAKRS OF ALL STUDENT FOR EACH COURSE:\n");
    for (int j = 0; j < 8; j++) {
        printf("  %s: %.2f\n", students[0].courses[j], (float)totalMarks[j] / studentCount);
    }
}

// This function calculates the total marks a student gets in preparationg for the function that sorts and display the
// marks in ascending and descending order
int getTotalMarks(Student *student) {
    int total = 0;
    for (int i = 0; i < 8; i++) {
        total += student->marks[i];
    }
    return total;
}

// This function enables sorting the student's marks in ascending order
int compareAscending(const void *a, const void *b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    return getTotalMarks(studentA) - getTotalMarks(studentB);
}

// This function enables sorting the student's marks in descending order
int compareDescending(const void *a, const void *b) {
    Student* studentA = (Student*)a;
    Student* studentB = (Student*)b;
    return getTotalMarks(studentB) - getTotalMarks(studentA);
}

// This function allows for sorting and displaying the record of students in chosen order
void sortAndDisplayStudents(Student* students, int studentCount, int order) {
    if(studentCount == 0) {
        printf("No students in the record to sort.\n");
        return;
    }
    if(order == 1) {
        qsort(students, studentCount, sizeof(Student), compareAscending);
        printf("\nSTUDENTS SORTED BY MARKS in ↑ ASCENDING ORDER:");
    } else if (order == 2) {
        qsort(students, studentCount, sizeof(Student), compareDescending);
        printf("\nSTUDENTS SORTED BY MARKS in ↓ DESCENDING ORDER:");
    }
    for (int i = 0; i < studentCount; i++) {
        displayStudentResults(&students[i]);
    }
}

    /* The main method that houses and drives the established data structure, functions, dynamic memory allocation
     * file saving and loading functions, record search, and calculaton and sorting functions
     */
    int main(void){
        char programName[50] = "Interactive Student Record System v1.0";
        printf("Hello, Welcome to the %s\n", programName);

        // Using the malloc function from the #define preprocessor directive
        // this section effects dynamic memory allocation as new students are added
        int capacity = STARTING_CAPACITY;
        Student* students = malloc(capacity * sizeof(Student));
        if (students == NULL) {
            printf("Oop! Memory allocation failed. \n");
            return 1;
        }

        int studentCount = 0;

        // The function to read the saved records from the file indicated
        loadFromFile(&students, &studentCount, &capacity, "StudentRecordSystem.txt");

        // This loop section executes the established functions based on the choice of the user
        while (1) {
            printf("\nWould you like to:");
            printf("\n1. Add a New Student");
            printf("\n2. Remove Existing Student");
            printf("\n3. Modify Existing Student Record");
            printf("\n4. Display all Students");
            printf("\n5. Search for Existing Student by their Roll Number");
            printf("\n6. Display Average Marks of all Students per course");
            printf("\n7. Sort and Display Students by their Marks");
            printf("\n8. Save Student Record to File");
            printf("\n9. Load Student Record from File");
            printf("\n10. Quit\n");
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
            } else if(option == 5){
                printf("\nWhat's the student's Roll Number: ");
                int rollNumber;
                scanf("%d", &rollNumber);
                // This function Consumes the leftover \n (newline) character after the student enters the rollNumber
                getchar();
                searchStudent(students, studentCount, rollNumber);
            } else if(option == 6) {
                calculateAverageMarks(students, studentCount);
            } else if(option == 7) {
                printf("\nCHOOSE SORTING ORDER:\n1. ↑ Ascending Order\n2. ↓ Descending order\nORDER: ");
                int order;
                scanf("%d", &order);
                // This function Consumes the leftover \n (newline) character after the user enters the order choice
                getchar();
                sortAndDisplayStudents(students, studentCount, order);
            } else if(option == 8) {
                saveToFile(students, studentCount, "StudentRecordSystem.txt");
                printf("Student Record saved to File.\n");
            } else if(option == 9) {
                loadFromFile(&students, &studentCount, &capacity, "StudentRecordSystem.txt");
                printf("Student Record Loaded from File.\n");
            } else if(option == 10) {
                saveToFile(students, studentCount, "StudentRecordSystem.txt");
                break;
            } else {
                printf("Opp! Invalid option. Please try again.\n");
            }
        }

        free(students); // Dynamic memory allocation function to free memory when no longer needed.

        printf("\nHurray! you registered '%d' number of student.\n\nThank you for using our %s Software\n"
               "\n© Solomon Ayuba | Okong Olugbenga Enang | Abel Odiri Odemudia | Christiana Chatt Richards "
               "| Olufemi Adesope"
               "\nData Science Department \nComputer Programming I (Group 6)", studentCount, programName);


        /* I CAN'T GET THE FILE READ AND WRITE FUNCTION TO WORK. KINDLY REVERT IF IT'S THE SAME CASE ON YOUR PC.
         * All Question through 8 has been solved in this code but i can't get question 6 (file operation) to save
         */

        return 0;

}