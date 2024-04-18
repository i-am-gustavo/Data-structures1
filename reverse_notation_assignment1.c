#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void push(Stack *stack, char c) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++stack->top] = c;
}

char pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/' || c == '%') {
        return 2;
    } else {
        return 0;
    }
}

char *infix_to_rpn(char *expression) {
    Stack stack;
    stack.top = -1;
    char *rpn = (char *)malloc(MAX_SIZE * sizeof(char));
    int rpn_index = 0;

    for (int i = 0; i < strlen(expression); i++) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            rpn[rpn_index++] = expression[i];
        } else if (expression[i] == '(') {
            push(&stack, expression[i]);
        } else if (expression[i] == ')') {
            while (stack.top != -1 && stack.data[stack.top] != '(') {
                rpn[rpn_index++] = pop(&stack);
            }
            if (stack.top == -1) {
                printf("Invalid expression\n");
                exit(EXIT_FAILURE);
            }
            pop(&stack);  // Remove '(' from stack
        } else if (is_operator(expression[i])) {
            while (stack.top != -1 && precedence(stack.data[stack.top]) >= precedence(expression[i])) {
                rpn[rpn_index++] = pop(&stack);
            }
            push(&stack, expression[i]);
        }
    }

    while (stack.top != -1) {
        if (stack.data[stack.top] == '(') {
            printf("Invalid expression\n");
            exit(EXIT_FAILURE);
        }
        rpn[rpn_index++] = pop(&stack);
    }

    rpn[rpn_index] = '\0';
    return rpn;
}

int main() {
    char expression[MAX_SIZE];
    printf("Enter the infix expression: ");
    fgets(expression, MAX_SIZE, stdin);
    char *rpn_expression = infix_to_rpn(expression);
    printf("Reverse Polish Notation (RPN) expression: %s\n", rpn_expression);
    free(rpn_expression);
    return 0;
}
