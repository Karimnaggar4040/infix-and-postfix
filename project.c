#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

typedef struct {
    char data[5];
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
    Node *p = s->top;
    float value = strtof(p->data, NULL);
    s->top = p->next;
    free(p);
    return value;
}

void push(Stack *s, float value) {
    Node *n = malloc(sizeof(Node));
    sprintf(n->data, "%f", value);
    n->next = s->top;
    s->top = n;
}

float peek(Stack *s) {
    return strtof(s->top->data, NULL);
}

int isEmpty(Stack *s) {
    return s->top ? 0 : 1;
}

int priority(char c){
    switch (c) {
        case '(':
            return 2;
        case '*':
        case '/':
        case '%':
            return 1;
        case '+':
        case '-':
            return 0;
    }
}

char* infixTopostfix(char*infix){
    int i, j = 0;
    char* postfix = malloc(sizeof(strlen(infix) + 1));
    Stack* s = initialize();
    for (i = 0; i < strlen(infix); i++) {
        if(isdigit(infix[i]))
            postfix[j++] = infix[i];
        else if(infix[i] == ')'){
            while(!isEmpty(s) && peek(s) != '(')
                postfix[j++] = pop(s);
            pop(s);
        }
        else if(isEmpty(s))
            push(s, infix[i]);
        else{
            while(!isEmpty(s) && priority(peek(s)) >= priority(infix[i]) && peek(s) != '(')
                postfix[j++] = pop(s);
            push(s, infix[i]);
        }
    }
    while (!isEmpty(s))
        postfix[j++] = pop(s);
    postfix[j] = '\0';
    return postfix;
}






int main(void) {
    return 0;
}
