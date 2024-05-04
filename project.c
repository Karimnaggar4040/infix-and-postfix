#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAX 100


//Handle the case where an undefined operand2 is entered (in precedence function)
//Handle the case of missing one of the parentheses (in the parentheses' condition)


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

        if (infix[i] == '(')
        {
            push(s, infix[i]);
        }
        else if (infix[i] == ')')
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
            // operand2 (+, -, *, /, %, ^)
            while (!isEmpty(s) && precedence(peek(s)) >= precedence(infix[i]))
            {
                postfix[j++] = pop(s);
                postfix[j++] = ' ';
            }
            push(s, infix[i]);
        }
    }

    // Pop remaining operand2s from the stack
    while (!isEmpty(s))
    {
        postfix[j++] = pop(s);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0'; // Add null terminator

    free(s); // Free memory allocated for the stack
    return postfix;
}

float evaluate(float operand1 , float operand2 , char operator)
{
    switch (operator)
    {
    case '+':
        return operand1 + operand2 ;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    case '^':
        return pow(operand1,operand2);
    case '%':
        return (int)operand1 % (int)operand2;
    }
}


float PostfixEvaluation(char* postfix)
{
    int i, j = 0;
    float number1,number2,operand2,operand1,result;
    Stack* s = initialize();
    for (i = 0; i < strlen(postfix); i++)
    {
        // IF SYMBOL IS AN OPERAND : push in stack
        j = i; // ??????? 3lshan ndmn en el j tb2a mashya m3 el i mn awal el loop
        if (postfix[j] == '-' && postfix[j+1] != ' ') // -ve one digit number
        {
            i++;
            number1 = -1 * (postfix[i] - '0');
            // if (postfix[i] >= '0' && postfix[i] <= '9') 3lshan howa law msh space yb2a digit
            push(s, number1);
        }
        // Need a condition that skips the space
        if (isdigit(postfix[j]) && postfix[j+1] == ' ')// +ve single digit
            push(s, postfix[i]);

        if (isdigit(postfix[j]) && isdigit(postfix[j+1]))// Double Digit
        {
            number2 = (postfix[i] - '0') *10 + (postfix[i+1] - '0');
            push(s,number2);
        }

        // IF SYMBOL IS AN OPERATOR
        if ((postfix[j] == '+' || postfix[j] == '-' || postfix[j] == '*' || postfix[j] == '/' || postfix[j] == '^' || postfix[j] == '%') && postfix[j+1] == ' ')
        {
            operand2 = pop(s);
            operand1 = pop(s);
            char operator = postfix[j-1];
            result = evaluate(operand1,operand2,operator);
            push (s,result);
        }
    }
    return pop(s);
}

int main(void)
{
    char infix[MAX], *postfix;
    printf("Please enter the infix expression:\n");
    fflush(stdin);
    fgets(infix, MAX, stdin);
    postfix = infixToPostfix(infix);
    printf("The postfix expression is: \n%s\n", postfix);
    float result = PostfixEvaluation(postfix);
    printf("Value: %.1f",result);
    return 0;
}
