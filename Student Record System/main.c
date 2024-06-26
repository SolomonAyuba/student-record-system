#include <stdio.h>
#include <string.h>

int main(void) {
    // Variable, Data-type declaration
    char programName[] = "Interactive Student Record System v1.0";
    char firstName[15];
    char lastName[15];
    char userName[30];

    // Displays welcome message and prompts the user to enter their full name. Then greets the user by their full name
    printf("Welcome to the %s \n Please enter your name to proceed \n", programName);
    printf("First Name: ");
    fgets(firstName, 15, stdin);

    printf("Last Name: ");
    fgets(lastName, 15, stdin);

    strcpy(userName, firstName);
    //strcat(userName, " ");
    strcat(userName, lastName);
    printf("\n");
    printf("Good day!, %s", userName);



    //scanf("%s", firstName, "\n" , lastName);




    /*
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
