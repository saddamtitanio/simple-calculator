#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

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
        else if (expression[i] == ' ') {
            continue;
        }
    }
    if (operator_count != digit_count - 1) {
        return false;
    }
    return true;
}

void separator(int **numbers, char **operators, const char *expression, const int len) {
    int d_count = 0;

    *numbers = malloc(sizeof(int) * 50);
    *operators = malloc(sizeof(char) * 50);

    for (int i = 0; i < len; i++) {
        if (isdigit(expression[i])) {
            int num = 0;
            while (i < len && isdigit(expression[i])) {
                num = num * 10 + (expression[i++] - '0');
            }
            if (d_count == INIT_NUMBERS_LENGTH - 1) {
                *numbers = realloc(*numbers, sizeof(int) * d_count * 2);
                if (!*numbers) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
            }
            (*numbers)[d_count++] = num;   
        }
    }
    *numbers = realloc(*numbers, d_count * sizeof(int));
}

int main() {
    char expression[MAX_EXPRESSION_LENGTH + 1];
    char ch;
    int count = 0;
    
    int *numbers = NULL;
    char *operators =  NULL;

    printf("==== SIMPLE CALCULATOR ====\n");

    do {
        printf("Enter an expression: ");
        fgets(expression, MAX_EXPRESSION_LENGTH + 1, stdin);
        expression[strcspn(expression, "\n")] = 0;

        if (!input_validation(expression, strlen(expression))) {
            printf("Expression invalid!\n\n");
        }
    } while (!input_validation(expression, strlen(expression)));

    separator(&numbers, &operators, expression, strlen(expression));

    for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
        printf("%d ", numbers[i]);
    }
}