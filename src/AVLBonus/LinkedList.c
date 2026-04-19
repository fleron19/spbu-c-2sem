#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList* newList(void)
{
    LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

static Node* createNode(const char key[], const char val[])
{
    Node* newNode = (Node*)malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Allocation error\n");
        return NULL;
    }
    strncpy(newNode->key, key, 255);
    newNode->key[255] = '\0';
    strncpy(newNode->value, val, 255);
    newNode->value[255] = '\0';
    newNode->next = NULL;
    return newNode;
}

void listInsert(LinkedList* list, const char key[], const char val[])
{
    Node* newNode = createNode(key, val);
    list->size++;
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    Node* temp = list->head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

const char* listFind(LinkedList* list, const char key[])
{
    Node* curr = list->head;
    while (curr != NULL) {
        if (strcmp(key, curr->key) == 0) {
            return curr->value;
        }
        curr = curr->next;
    }
    return NULL;
}

void listDelete(LinkedList* list, const char key[])
{
    Node* curr = list->head;
    if (curr == NULL) {
        return;
    }
    if (strcmp(curr->key, key) == 0) {
        list->head = list->head->next;
        free(curr);
        list->size--;
        return;
    }
    Node* prev = curr;
    curr = prev->next;
    while (curr != NULL) {
        if (strcmp(key, curr->key) == 0) {
            prev->next = curr->next;
            free(curr);
            list->size--;
            return;
        }
        curr = curr->next;
    }
}

void listFree(LinkedList* list)
{
    if (list == NULL)
        return;
    Node* curr = list->head;
    while (curr != NULL) {
        Node* tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    list->head = NULL;
    free(list);
}
