//*###########################################
// Operation Systems, Lab 1, January 26th 2024
// Jason Manarroo | 100825106
//*###########################################

#include "utility.h"

//! ------------------ Internal Command Implementations -------------------------

void change_directory(const Token* tokens, int token_count) { // 1.i
    if (token_count > 0) {
        // Use the first argument as the directory path
        if (chdir(tokens[0].token) != 0) {
            perror("Change directory failed");
        } else {
            char s[100];
            if (getcwd(s, sizeof(s)) == NULL) {
                perror("myshell: Change Directory Procedure Failed !");
            }
        }
    } else {
        // Handle the case where no arguments are provided
        printf("No directory specified for cd command...\n");
    }
}


void clear_screen(const Token* tokens, int token_count) { //1.ii
    printf("\033[H\033[J");
}

void list_dir(const Token* tokens, int token_count) { //1.iii
    const char* directory = (token_count > 0) ? tokens[0].token : ".";

    DIR *d;
    struct dirent *dir;
    d = opendir(directory);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        perror("dir command failed");
    }
}

extern char **environ; //* Requires the external environ variable declared in <unistd.h>.

void environ_func(const Token* tokens, int token_count) { //1.iv
    for (char **env = environ; *env != 0; env++) {
        char *thisEnv = *env;
        printf("%s\n", thisEnv);    
    }
}

void echo(const Token* tokens, int token_count) { //1.v
    for (int i = 0; i < token_count; i++) {
        printf("%s ", tokens[i].token);
    }
    printf("\n");
}

void help(const Token* tokens, int token_count) { //1.vi
    system("more manual.txt"); //TODO Replace 'manual.txt' with the manual file
}

void pause_shell(const Token* tokens, int token_count) { //1.vii
    printf("Press Enter to continue...");
    getchar();
}

void quit(const Token* tokens, int token_count) { // 1.viii
    exit(0);
}



void dummy_operator_function(const Token* tokens, int token_count) {
}

//! ------------------ Parsing Functionality --------------------------

void command_pipeline(char* input) {
    int numTokens;
    char** tokens = parse_and_clean(input, &numTokens);

    Token* tokenStructs = (Token*)malloc(numTokens * sizeof(Token));
    tokenize(tokens, numTokens, tokenStructs);

    process_tokens(tokenStructs, numTokens);

    //Free Allocated Variables
    free(tokens);
    free(tokenStructs);
}

//* KEYWORD & OPERATOR token-definitions aswell as associated function Pointers (to be loaded into Token structs upon pipeline call)

const char* keywords[] = {"cd", "clr", "dir", "environ", "echo", "help", "pause", "quit"};
CommandFunc keywordFunctions[] = {change_directory, clear_screen, list_dir, environ_func, echo, help, pause_shell,quit};

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

//TODO: comment btr
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
    
    //TODO: For debug, remove soon
    for (int i = 0; i < numTokens; i++) {
        printf("Token: %s, Type: %d\n", tokens[i].token, tokens[i].type);
        // Add further processing logic here
    }

    // ------ Requirement 1. Internal Commands (Executing Associated Token Func.) ------
    
    if(tokens[0].type == KEYWORD && tokens[0].func != NULL){
        //* &tokens[1] points to tokens[1] and onwards (without traditional array slicing)
        tokens[0].func(&tokens[1], numTokens - 1);
        return;
    }

    // ------ Requirement 2. X ------


}
