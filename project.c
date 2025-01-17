#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100


//Handle the case where an undefined operand2 is entered (in precedence function)
//Handle the case of missing one of the parentheses (in the parentheses' condition)


typedef struct {
    float data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

Stack *initialize() {
    Stack *s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

float pop(Stack *s) {
    Node *temp = s->top;
    float value = temp->data;
    s->top = temp->next;
    free(temp);
    return value;
}

void push(Stack *s, float value) {
    Node *n = malloc(sizeof(Node));
    n->data = value;
    n->next = s->top;
    s->top = n;
}

float peek(Stack *s) {
    return s->top->data;
}

int isEmpty(Stack *s) {
    return s->top ? 0 : 1;
}


int precedence(char c) {
    switch (c) {
        case '^':
            return 3;
        case '*':
        case '/':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

// Infix to postfix conversion function
char *infixToPostfix(char *infix) {
    char *postfix = malloc(
            strlen(infix) + 2); // Allocate enough space for postfix expression (including null terminator)
    Stack *s = initialize();

    int i, j = 0;
    char ch;

    for (i = 0; i < strlen(infix); i++) {
        if (infix[i] == '-' && isdigit(infix[i + 1])) {
            postfix[j++] = '-';
            i++;
        }
        while (isdigit(infix[i]) || infix[i] == '.') {
            postfix[j++] = infix[i];
            i++;
        }

        if (infix[i] == ' ')
            continue;
        if (postfix[j - 1] != ' ')
            postfix[j++] = ' ';

        if (infix[i] == '(') {
            push(s, infix[i]);
        } else if (infix[i] == ')') {
            while ((ch = pop(s)) != '(' && !isEmpty(s)) {
                postfix[j++] = ch;
                postfix[j++] = ' ';
            }
            //            if (ch == '(') {
            //                printf("Invalid expression: Missing closing parenthesis\n");
            //                exit(1);
            //            }
        } else {
            // operand2 (+, -, *, /, %, ^)
            while (!isEmpty(s) && precedence(peek(s)) >= precedence(infix[i])) {
                postfix[j++] = pop(s);
                postfix[j++] = ' ';
            }
            push(s, infix[i]);
        }
    }

    // Pop remaining operand2s from the stack
    while (!isEmpty(s)) {
        postfix[j++] = pop(s);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0'; // Add null terminator

    free(s); // Free memory allocated for the stack
    return postfix;
}

float evaluate(float operand1, float operand2, char operator) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        case '^':
            return pow(operand1, operand2);
        case '%':
            return (int) operand1 % (int) operand2;
    }
}


float PostfixEvaluation(char *postfix) {
    int i, j = 0;
    float number1, number2, number3, operand2, operand1, result;
    Stack *s = initialize();
    for (i = 0; i < strlen(postfix); i++) {
        // IF SYMBOL IS AN OPERAND : push in stack
        j = i; // ??????? 3lshan ndmn en el j tb2a mashya m3 el i mn awal el loop
        if (postfix[j] == '-' && postfix[j + 1] != ' ' && postfix[j + 2] == ' ') // -ve one digit number
        {
            i++;
            number1 = -1 * (postfix[i] - '0');
            // if (postfix[i] >= '0' && postfix[i] <= '9') 3lshan howa law msh space yb2a digit
            push(s, number1);
        }
        // Need a condition that skips the space
        if (isdigit(postfix[j]) && postfix[j + 1] == ' ')// +ve single digit
            push(s, postfix[i] - '0');


        if ((isdigit(postfix[j]) && postfix[j + 1] == '.') || (postfix[j] == '-' && isdigit(postfix[j + 1]) && postfix[j + 2] == '.'))//floating point one digit
        {
            int flag = 0;
            number3 = 1;
            if (postfix[j] == '-'){
                number3 = -1;
                j++;
                i++;
                flag = 1;
            }
            number3 *= (postfix[j] - '0');
            int k = j + 2, f = 1;
            while (isdigit(postfix[k])) {
                if (flag)
                    number3 -= (postfix[k] - '0')* pow(0.1, f);
                else
                    number3 += (postfix[k] - '0')* pow(0.1, f);
                k++;
                f++;
                i++;
            }
            i++;
            push(s, number3);
        }

        if ((isdigit(postfix[j]) && isdigit(postfix[j + 1])) || (postfix[j] == '-' && isdigit(postfix[j + 1]) && isdigit(postfix[j + 2])))// Double Digit
        {
            int flag = 0;
            number2 = 1;
            if(postfix[j] == '-') {
                number2 = -1;
                j++;
                i++;
                flag = 1;
            }
            number2 *= (postfix[i] - '0') * 10 + (postfix[i + 1] - '0');
            if (isdigit(postfix[j]) && postfix[j + 2] == '.'){
                int k = j + 3, f = 1;
                while (isdigit(postfix[k])) {
                    if (flag)
                        number2 -= (postfix[k] - '0')* pow(0.1, f);
                    else
                        number2 += (postfix[k] - '0')* pow(0.1, f);
                    k++;
                    f++;
                    i++;
                }
            }
            push(s, number2);
            i++;
        }

        // IF SYMBOL IS AN OPERATOR
        if ((postfix[j] == '+' || postfix[j] == '-' || postfix[j] == '*' || postfix[j] == '/' || postfix[j] == '^' ||
             postfix[j] == '%') && postfix[j + 1] == ' ') {
            operand2 = pop(s);
            operand1 = pop(s);
            char operator = postfix[j];
            result = evaluate(operand1, operand2, operator);
            push(s, result);
        }
    }
    return pop(s);
}

int main(void) {
    char infix[MAX], *postfix;
    printf("Please enter the infix expression:\n");
    fflush(stdin);
    fgets(infix, MAX, stdin);
    postfix = infixToPostfix(infix);
    printf("The postfix expression is: \n%s\n", postfix);
    float result = PostfixEvaluation(postfix);
    printf("Value: %f", result);
    return 0;
}
