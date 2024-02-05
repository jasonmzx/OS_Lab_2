//*###########################################
// Operation Systems, Lab 1, January 26th 2024
// Jason Manarroo | 100825106
// Ahmed Darwish  | 100754743
// Juliano Falotico | 100658311 
//*###########################################

#include "utility.h"

#define MAX_INPUT_LENGTH 512
#define MAX_PATH_LENGTH 1024

void set_shell_env_variable() { //* Requirement 1. IX
    char execpath[MAX_PATH_LENGTH];

    // Read the symbolic link '/proc/self/exe' to get the path of the current executable
    // Using ssize_t as the readlink can return -1 (negative) therefore signed int is needd
    
    ssize_t len = readlink("/proc/self/exe", execpath, sizeof(execpath) - 1);
    
    if (len != -1) {
        execpath[len] = '\0'; // Null-terminate the path
        
        if (setenv("shell", execpath, 1) != 0) { // Set the 'shell' environment variable
            perror("setenv failure !!");
        } else {
            printf("\nShell environment variable set to: %s\n", execpath);
        }
    } else {
        perror("readlink failure !!");
    }
}

int main(int argc, char *argv[]) {
    
    set_shell_env_variable();

    char* SHELL_PREFIX = "> myshell";
    char* SHELL_SEPERATOR = "$"; //* Example: myshell/path/to/dir $ <user input>

    //* ---- Visual Appeal (additional features) Escape Codes ----

    char* GREEN_EC =  "\033[1;32m";
    char* YELLOW_EC = "\033[1;33m";
    char* RESET_EC =  "\033[0m";

    //* ---- Main Shell Buffers ----

    char input[MAX_INPUT_LENGTH];
    char cwd[MAX_PATH_LENGTH]; //Current Path myshell is in (usually starts at shell environ. loc)
    char full_prompt[MAX_INPUT_LENGTH + MAX_PATH_LENGTH];

    printf("Welcome to myshell, By: Jason Manarroo 100825106 \n\n");

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

        // Example: exit the loop if the user types "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Process the input (you can add more logic here)
        command_pipeline(input);

        // Add more command handling logic here
    }

    return 0;
}
