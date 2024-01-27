//*###########################################
// Operation Systems, Lab 1, January 26th 2024
// Jason Manarroo | 100825106
//*###########################################

#include "utility.h"

#define MAX_INPUT_LENGTH 512
#define MAX_PATH_LENGTH 1024

int main(int argc, char *argv[]) {

    char* SHELL_PREFIX = "> myshell";
    char* SHELL_SEPERATOR = "$"; //* Example: myshell/path/to/dir $ <user input>

    //* ---- Visual Appeal (additional) Escape Codes ----

    char* GREEN_EC =  "\033[1;32m";
    char* YELLOW_EC = "\033[1;33m";
    char* RESET_EC =  "\033[0m";

    //* ---- Main Shell Buffers ----

    char input[MAX_INPUT_LENGTH];
    char cwd[MAX_PATH_LENGTH];
    char full_prompt[MAX_INPUT_LENGTH + MAX_PATH_LENGTH];


    printf("\nWelcome to myshell, By: Jason Manarroo 100825106 \n\n");

    // Main loop
    while (1) {

        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("Error getting current directory");
            continue;
        }

        // Construct and display shell prompt
        snprintf(full_prompt, sizeof(full_prompt), "%s%s:~%s%s%s%s  ", 
        YELLOW_EC, SHELL_PREFIX, GREEN_EC, cwd, RESET_EC, SHELL_SEPERATOR);

        printf("%s", full_prompt);
        fflush(stdout); 
        
        // Read a line of input
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break; // Exit if input fails (e.g., EOF is encountered)
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;

        // Process the input (you can add more logic here)
        printf("You entered: %s\n", input);

        // Example: exit the loop if the user types "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Add more command handling logic here
    }

    return 0;
}
