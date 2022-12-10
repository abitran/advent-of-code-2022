#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define CAP 9

typedef struct stack{
    char data[256];
    int top;
}stack;


void push(stack *, char);

char pop(stack *);

char peep(stack *);

void populate(char *, stack *);

void reverse(stack *s);

void movemultiple(int, stack *, stack *);

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        fprintf(stderr, "[!] Cannot read file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    stack stacks[CAP];
    char buffer[100];

    for (int i = 0; i < CAP; i++)
        stacks[i].top = -1;

    int rev = 0;

    while(fgets(buffer, sizeof(buffer), fp)){
        if (buffer[0] == 'm'){
            if (!rev){
                for (int i = 0; i < CAP; i++)
                    reverse(&stacks[i]);
                rev = 1;
            }
            int qty, from, to;
            sscanf(buffer, "move %d from %d to %d", &qty, &from, &to);

            if (qty == 1)
                push(&stacks[to-1], pop(&stacks[from-1]));

            else
                movemultiple(qty, &stacks[from-1], &stacks[to-1]);
        }
        else
            populate(buffer, stacks);
    }

    for (int i = 0; i < CAP; i++)
       printf("%c", peep(&stacks[i]));


    return 0;
}


void push(stack *s, char val)
{
    if (s->top == 256){
        fprintf(stderr, "Stack is full!");
        exit(EXIT_FAILURE);
    }

    s->data[++(s->top)] = val;
}


char pop(stack *s)
{
    if (s->top == -1){
        fprintf(stderr, "Nothing to take from stack");
        exit(EXIT_FAILURE);
    }

    return (s->data[s->top--]);
}

char peep(stack *s)
{
    if (s->top == -1){
        fprintf(stderr, "Nothing to take from stack");
        exit(EXIT_FAILURE);
    }

    return (s->data[s->top]);
}


void populate(char *buffer, stack *s)
{
    for (int i = 0; i < CAP; i++)
        if (buffer[i*4+1] >= 'A' && buffer[i*4+1] <= 'Z')
            push(&s[i], buffer[i*4+1]);
}

void reverse(stack *s)
{
    char temp[s->top];

    for (int i = s->top, j = 0; i >= 0; i--, j++)
        temp[j] = s->data[i];

    for (int i = 0; i <= s->top; i++)
        s->data[i] = temp[i];
}

void movemultiple(int qty, stack *sf, stack *st)
{
    char buffer[qty];
    for (int i = 0; i < qty; i++)
        buffer[i] = pop(sf);

    char temp[qty];
    for (int i = qty-1, j = 0; i >= 0; j++, i--)
        temp[j] = buffer[i];

    for (int i = 0; i < qty; i++)
        buffer[i] = temp[i];

    for (int i = 0; i < qty; i++)
        push(st, buffer[i]);
}
