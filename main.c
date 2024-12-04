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

int main() {
    char expression[MAX_EXPRESSION_LENGTH + 1];
    char ch;
    int count = 0;
    
    printf("==== SIMPLE CALCULATOR ====\n");

    do {
        printf("Enter an expression: ");
        fgets(expression, MAX_EXPRESSION_LENGTH + 1, stdin);
        expression[strcspn(expression, "\n")] = 0;

        if (!input_validation(expression, strlen(expression))) {
            printf("Expression invalid!\n\n");
        }
    } while (!input_validation(expression, strlen(expression)));
}