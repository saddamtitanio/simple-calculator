#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100

typedef struct
{
    char braces[100];
    int top;
} Stack;

bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, char ch) {
    stack->braces[++(stack->top)] = ch;
}

void pop(Stack *stack) {
    (stack->top)--;
}

char getTopParantheses(Stack stack) {
    return (stack.braces[stack.top]);
}

bool isBalanced(const char *str) {
    Stack stack = {.top = -1};
    for (int i = 0; str[i] != '\0'; i++) {
        if (strchr("()[]", str[i]) != NULL) {
            if (isEmpty(&stack)) {
                push(&stack, str[i]);
            }
            else if ((getTopParantheses(stack) == '(' && str[i] == ')') ||
                    (getTopParantheses(stack) == '[' && str[i] == ']')) {
                pop(&stack);
            }
            else {
                push(&stack, str[i]);
            }
        }
    }
    return (isEmpty(&stack));
}