#include <stdio.h>
#include <stdlib.h>
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

char* infixTopostfix(char*infix){
    // Commmeennnnnnntt
}






int main(void) {
    Stack *s = initialize();
    push(s, 16.78);
    push(s, 16);
    push(s, -5);
    printf("%.2f", peek(s));
    printf("\n");
    printf("%.2f", pop(s));
    printf("\n");
    printf("%.2f", pop(s));
    printf("\n");
    free(s);
    return 0;
}
