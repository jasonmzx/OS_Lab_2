// gcc -o testprog test_program.c

#include <stdio.h>

int main(int argc, char *argv[]) {
    char input[100]; // Buffer to store input

    // Check if there are any command-line arguments
    if (argc > 1) {
        printf("Received arguments:\n");
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    } else {
        printf("No arguments received.\n");
    }

    printf("\nEnter some text: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        printf("You entered: %s\n", input);
    } else {
        printf("No input read.\n");
    }

    return 0;
}
