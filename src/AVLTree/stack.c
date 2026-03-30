#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

struct StackNode {
    void* value;
    struct StackNode* next;
};
struct Stack {
    struct StackNode* head;
};

Stack* newStack(void)
{
    Stack* stack = calloc(1, sizeof(*stack));
    return stack;
}

void push(Stack* stack, void* value)
{
    struct StackNode* node = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (node == NULL) {
        printf("Allocation error\n");
        return;
    }

    node->value = value;
    node->next = stack->head;
    stack->head = node;
}
void* pop(Stack* stack)
{
    struct StackNode* oldNode = stack->head;
    void* res = oldNode->value;
    stack->head = oldNode->next;

    free(oldNode);
    return res;
}
bool isEmpty(Stack* stack)
{
    return stack->head == NULL;
}
void deleteStack(Stack* stack)
{
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}

void* top(Stack* stack)
{
    return stack->head->value;
}
