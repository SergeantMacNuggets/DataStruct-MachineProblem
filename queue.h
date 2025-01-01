#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    char type;
    int val;
    struct node *next;
} Node;

typedef struct queue {
    Node *first, *last;
}Queue;

Node *createNode(int x, char c) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->type = c;
    newNode->val = x;
    newNode->next=NULL;
    return newNode;
}

Queue *createQueue() {
    Queue *newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->last=NULL;
    newQueue->first=newQueue->last;
    return newQueue;
}

void enqueue(Queue *q, int x, char c) {
    Node *ptr=createNode(x,c);
    if(q->last == NULL) {
        q->first = q->last = ptr;
        return;
    }
    q->last->next = ptr;
    q->last = ptr;
}

void dequeue(Queue *q) {
    Node *temp;
    if(q->first==NULL && q->last==NULL) {
        printf("Queue Underflow\n");
        return;
    }
    temp = q->first;
    q->first = q->first->next;
    if(q->first==NULL) q->last=NULL;
    free(temp);
}

Node *getFront(Queue *q) {
    if(q->first==NULL && q->last==NULL) {
        printf("Queue is empty\n");
        return NULL;
    }
    return q->first;
}

Node *getRear(Queue *q) {
    if(q->first==NULL && q->last==NULL) {
        printf("Queue is empty\n");
        return NULL;
    }
    return q->last;
}

void displayAll(Queue *q) {
    Node *ptr = q->first;
    while(ptr!=NULL) {
        printf("[%d,%c] -> ",ptr->val,ptr->type);
        ptr=ptr->next;
    }
    printf("NULL\n");
}