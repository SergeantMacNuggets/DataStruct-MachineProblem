#include <stdio.h>
#include <stdlib.h>


typedef struct Node_q{
    char type;
    struct Node_q *next;
} NodeQ;

typedef struct queue {
    NodeQ *first, *last;
}Queue;

NodeQ *createNodeQ(char c) {
    NodeQ *newNodeQ = (NodeQ*)malloc(sizeof(NodeQ));
    newNodeQ->type = c;
    newNodeQ->next=NULL;
    return newNodeQ;
}

Queue *createQueue() {
    Queue *newQueue = (Queue*)malloc(sizeof(Queue));
    newQueue->last=NULL;
    newQueue->first=newQueue->last;
    return newQueue;
}

void enqueue(Queue *q, char c) {
    NodeQ *ptr=createNodeQ(c);
    if(q->last == NULL) {
        q->first = q->last = ptr;
        return;
    }
    q->last->next = ptr;
    q->last = ptr;
}

void dequeue(Queue *q) {
    NodeQ *temp;
    if(q->first==NULL && q->last==NULL) {
        printf("Queue Underflow\n");
        return;
    }
    temp = q->first;
    q->first = q->first->next;
    if(q->first==NULL) q->last=NULL;
    free(temp);
}

NodeQ *getFront(Queue *q) {
    if(q->first==NULL && q->last==NULL) {
        printf("Queue is empty\n");
        return NULL;
    }
    return q->first;
}

NodeQ *getRear(Queue *q) {
    if(q->first==NULL && q->last==NULL) {
        printf("Queue is empty\n");
        return NULL;
    }
    return q->last;
}

char peekChar(Queue *q) {
    return q->first->type;
}

void displayAllQ(Queue *q) {
    NodeQ *ptr = q->first;
    while(ptr!=NULL) {
        printf("[%c] -> ",ptr->type);
        ptr=ptr->next;
    }
    printf("NULL\n");
}