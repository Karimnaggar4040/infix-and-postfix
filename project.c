#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct
{
    float data[MAX];
    struct Node* next;
} Node;

typedef struct
{
    Node* top;
} Stack;

Stack* initialize()
{
    Stack* s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

float pop(Stack* s)
{
    Node* temp = s->top;
    float value = strtof(temp->data, NULL);
    s->top = temp->next;
    free(temp);
    return value;
}

void push(Stack* s, float value)
{
    Node* n = malloc(sizeof(Node));
    sprintf(n->data, "%f", value);
    n->next = s->top;
    s->top = n;
}

float peek(Stack* s)
{
    return strtof(s->top->data, NULL);
}

int isEmpty(Stack* s)
{
    return s->top ? 0 : 1;
}


int precedence(char c)
{
    switch (c)
    {
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
char* infixToPostfix(char* infix)
{
    char* postfix = malloc(
        strlen(infix) + 2); // Allocate enough space for postfix expression (including null terminator)
    Stack* s = initialize();

    int i, j = 0;
    char ch;

    for (i = 0; i < strlen(infix); i++)
    {
        if (infix[i] == '-' && isdigit(infix[i + 1]))
        {
            postfix[j++] = '-';
            i++;
        }
        while (isdigit(infix[i]) || infix[i] == '.')
        {
            postfix[j++] = infix[i];
            i++;
        }

        if (infix[i] == ' ')
            continue;
        if (postfix[j - 1] != ' ')
            postfix[j++] = ' ';

        if (ch == '(')
        {
            push(s, ch);
        }
        else if (ch == ')')
        {
            while ((ch = pop(s)) != '(' && !isEmpty(s))
            {
                postfix[j++] = ch;
                postfix[j++] = ' ';
            }
            //            if (ch == '(') {
            //                printf("Invalid expression: Missing closing parenthesis\n");
            //                exit(1);
            //            }
        }
        else
        {
            // Operator (+, -, *, /, %, ^)
            while (!isEmpty(s) && precedence(peek(s)) >= precedence(infix[i]))
            {
                postfix[j++] = pop(s);
                postfix[j++] = ' ';
            }
            push(s, infix[i]);
        }
    }

    // Pop remaining operators from the stack
    while (!isEmpty(s))
    {
        postfix[j++] = pop(s);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0'; // Add null terminator

    free(s); // Free memory allocated for the stack
    return postfix;
}

//Evaluate postfix expression
float PostfixEvaluation(char* postfix)
{
    int i, j = 0,flag=0;
    Stack* s = initialize();
    for (i = 0; i < strlen(postfix); i++)
    {
        if (postfix[j++] == '-' && postfix[j++] != ' ')
        {
            flag = 1;
            i++;
            if (postfix[i] >= '0' && postfix[i] <= '9')
                push(s, postfix[i] - '0');

        }
    }
}

int main(void)
{
    char n[MAX];
    strcpy(n, infixToPostfix("2 + ( -2.5 + 3.14 ) * ( -5.4 + 8.1 ) ^ ( -0.5 )"));
    printf("%s", n);
    return 0;
}
