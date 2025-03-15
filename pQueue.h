#include <stdio.h>
#include <stdlib.h>

typedef struct building {
    char type;
    struct building *next;
}Building;

typedef struct node {
    int toll;
    Building *hut;
    struct node *next;
}Node;

Node *createNode(Building *b, int x) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->hut = b;
    newNode->toll = x;
    newNode->next=NULL;
    return newNode;
}

Building *createBuilding(char x) {
    Building *newBuild = (Building*) malloc(sizeof(Building));
    newBuild->type = x;
    newBuild->next = NULL;
    return newBuild;
}

Building *peek(Node *n) {
    if(n == NULL) return NULL;
    return n->hut;
}

int peekToll(Node *n) {
    if(n==NULL) return -1;
    return n->toll;
}

void push(Node **n, Building *b, int x) {
    Node *head = *n;
    Node *nVal = *n;
    Node *temp = createNode(b,x);
    if(*n==NULL) {
        *n=createNode(b,x);
        return;
    }
    if(nVal->toll > x) {
        temp->next = *n;
        *n=temp;
    }

    else {

        while(head->next!=NULL && head->next->toll < x) {
            head=head->next;
        }

        temp->next = head->next;
        head->next = temp;

    }
}

void pop(Node **n) {

    Node *temp = *n;
    *n = (*n)->next;
    free(temp);

}

void displayAll(Node **q) {
    Node *ptr = *q;

    while(ptr!=NULL) {
        printf("[%d,%c] -> ",ptr->toll,ptr->hut->type);
        ptr=ptr->next;
    }
    
    printf("NULL\n");
}