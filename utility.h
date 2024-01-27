//*###########################################
// Operation Systems, Lab 1, January 26th 2024
// Jason Manarroo | 100825106
//*###########################################

#ifndef UTILITY_H
#define UTILITY_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 50

typedef enum {
    KEYWORD,
    LITERAL,
    OPERATOR
} TokenType;

typedef void (*CommandFunc)(const char*);

typedef struct {
    char* token;
    TokenType type;
    CommandFunc func; // Function pointer for command execution
} Token;

// Function Declarations
void change_directory(const char* path);
void dummy_operator_function(const char* arg); // Dummy function for operator

char** parse_and_clean(const char* input, int* numTokens);
TokenType determine_token_type(const char* token, CommandFunc* func);
void tokenize(char** tokens, int numTokens, Token* tokenStructs);
void process_tokens(Token* tokens, int numTokens);

#endif 
