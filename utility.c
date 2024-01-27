//*###########################################
// Operation Systems, Lab 1, January 26th 2024
// Jason Manarroo | 100825106
//*###########################################

#include "utility.h"

void change_directory(const char* path) {
    if (chdir(path) != 0) {
        // Use perror to output a descriptive error message
        perror("Change directory failed");
    } else {
        // Correct array declaration
        char s[100];

        // Get and print the current working directory
        if (getcwd(s, sizeof(s)) != NULL) {
            printf("Current directory: %s\n", s);
        } else {
            perror("getcwd failed");
        }
    }
}

void dummy_operator_function(const char* arg) {
    printf("Operator function called with arsgument: %s\n", arg);
}


// ------------------ Parsing Features -----------------------



// int main() {
//     char input[] = "cd test < inputfile > outputfile";
//     int numTokens;
//     char** tokens = parse_and_clean(input, &numTokens);

//     Token* tokenStructs = (Token*)malloc(numTokens * sizeof(Token));
//     tokenize(tokens, numTokens, tokenStructs);

//     process_tokens(tokenStructs, numTokens);

//     // Cleanup
//     for (int i = 0; i < numTokens; i++) {
//         free(tokens[i]);
//     }
//     free(tokens);
//     free(tokenStructs);

//     return 0;
// }


//* KEYWORD & OPERATOR token-definitions aswell as associated function Pointers

const char* keywords[] = {"cd"};
CommandFunc keywordFunctions[] = {change_directory};

const char* operators[] = {"<"};
CommandFunc operatorFunctions[] = {dummy_operator_function};

//* In C, returning a char** (char ptr to ptr)
//* is a common way to represent a dynamically allocated array of strings (or array of pointers)

//TODO: comment btr
char** parse_and_clean(const char* input, int* numTokens) {
    char** tokens = (char**)malloc(MAX_TOKENS * sizeof(char*));
    char* token;
    char* tempInput = strdup(input); // Duplicate input string for strtok
    int i = 0;

    token = strtok(tempInput, " \t\n");
    while (token != NULL && i < MAX_TOKENS) {
        tokens[i] = strdup(token); // Duplicate token
        token = strtok(NULL, " \t\n");
        i++;
    }
    *numTokens = i;

    free(tempInput); //Free the copy of the Input (reducs mem. leaks)
    return tokens;
}

TokenType determine_token_type(const char* token, CommandFunc* func) {
    for (int i = 0; i < sizeof(keywords)/sizeof(char*); i++) {
        if (strcmp(token, keywords[i]) == 0) {
            *func = keywordFunctions[i];
            return KEYWORD;
        }
    }
    for (int i = 0; i < sizeof(operators)/sizeof(char*); i++) {
        if (strcmp(token, operators[i]) == 0) {
            *func = operatorFunctions[i];
            return OPERATOR;
        }
    }
    *func = NULL; // No function associated with literals
    return LITERAL;
}

void tokenize(char** tokens, int numTokens, Token* tokenStructs) {
    for (int i = 0; i < numTokens; i++) {
        
        CommandFunc func;
        tokenStructs[i].token = tokens[i];

        //* Pass the type determination fn, the `func` ptr to be set, before actually setting struct.func to func
        tokenStructs[i].type = determine_token_type(tokens[i], &func); 
        tokenStructs[i].func = func;
    }
}

void process_tokens(Token* tokens, int numTokens) {
    for (int i = 0; i < numTokens; i++) {
        printf("Token: %s, Type: %d\n", tokens[i].token, tokens[i].type);
        // Add further processing logic here
    }
}
