#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "balance.h"

#define MAX_EXPRESSION_LENGTH 50
#define INIT_NUMBERS_LENGTH 25


bool input_validation(const char *expression, const int len) {
    int digit_count = 0;
    int operator_count = 0;

    char valid_operators[] = {'+', '*', '/', '-'};

    for (int i = 0; i < len; i++) {
        if (isdigit(expression[i])) {
            while (i < len && isdigit(expression[i])) {
                i++;
            }
            digit_count++;
        }
        else if (strchr(valid_operators, expression[i]) != NULL) {
            operator_count++;
        }
        else if (expression[i] == ' ' || strchr("()[]", expression[i]) != NULL) {
            continue;
        }
        else {
            return false;
        }
    }
    if (operator_count != digit_count - 1) {
        return false;
    }
    return true;
}

int operators_precedence(char operator) {
    switch(operator) {
        case '*':
            return 3;
        case '/':
            return 2;
        case '+':
            return 1;
        case '-':
            return 0;
    }
}

void separator(int **numbers, int **operators, const char *expression, int *num_count, int *op_count) {
    *op_count = 0;
    *num_count = 0;
    *numbers = malloc(sizeof(int) * 50);
    *operators = malloc(sizeof(int) * 50);

    for (int i = 0; expression[i] != '\0'; i++) {
        if (isdigit(expression[i])) {
            int num = 0;
            while (expression[i] != '\0' && isdigit(expression[i])) {
                num = num * 10 + (expression[i++] - '0');
            }
            if (*num_count == INIT_NUMBERS_LENGTH - 1) {
                *numbers = realloc(*numbers, sizeof(int) * *num_count * 2);
                if (!*numbers) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
            }
            (*numbers)[(*num_count)++] = num;   
        }
        if (strchr("+-*/", expression[i]) != NULL) {
            if (*op_count == INIT_NUMBERS_LENGTH - 1) {
                *operators = realloc(*operators, sizeof(int) * *op_count * 2);
                if (!*operators) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }    
            }
            (*operators)[(*op_count)++] = operators_precedence(expression[i]);
        }
    }
    (*op_count)--;
}

void sort_precedence(int **numbers, int **operator, const int num_count, const int op_count) {
    for (int i = 0; i < op_count; i++) {
        for (int j = i + 1; j < op_count; j++) {
            if ((*operator)[j] > (*operator)[j - 1]) {
                int temp = (*operator)[j - 1];
                (*operator)[j - 1] = (*operator)[j];
                (*operator)[j] = temp;
            }
        }
    }
}

int main() {
    char expression[MAX_EXPRESSION_LENGTH + 1];
    char ch;
    int count = 0;
    
    int num_count, op_count;

    int *numbers = NULL;
    int *operators =  NULL;

    printf("==== SIMPLE CALCULATOR ====\n");
    do {
        printf("Enter an expression: ");
        fgets(expression, MAX_EXPRESSION_LENGTH + 1, stdin);
        expression[strcspn(expression, "\n")] = 0;

        if (!input_validation(expression, strlen(expression)) || !isBalanced(expression)) {
            printf("Expression invalid!\n\n");
        }

    } while (!input_validation(expression, strlen(expression)) || !isBalanced(expression));

    separator(&numbers, &operators, expression, &num_count, &op_count);
    sort_precedence(&numbers, &operators, num_count, op_count);
}