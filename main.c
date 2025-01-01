#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pQueue.h"

typedef struct list {
    Building *head;
}List;


List **createRoadMap(int roads);

void addNode(List *newList[],int s, int d, char *table);
int pathing(List **roadMap, int item, char src, char dst);


void display(List *newList[],int roads);

int main() {
    int input;
    printf("Number of Roads: ");
    scanf("%d",&input);
    List **firstMap = createRoadMap(input);
    display(firstMap,input);
    return 0;
}

void addNode(List *newList[], int s, int d, char *table) {
    Building *src, *tmp, *dest;
    if(newList[s]->head==NULL) {
        src = createBuilding(table[s]);
        newList[s]->head = src;
    }
    dest = createBuilding(table[d]);
    tmp=newList[s]->head;
    while(tmp->next != NULL) tmp=tmp->next;
    tmp->next=dest;
}

void display(List **newList,int roads) {
    Building *ptr2;
    for(int i=0;i<roads;i++) {
        ptr2=newList[i]->head;
        while(ptr2!=NULL) {
            printf("%c -> ",ptr2->type);
            ptr2=ptr2->next;
        }
        printf("NULL\n");
    }
}

int indexNum(char *table,char c) {
    for(int i=0;i<strlen(table);i++) {
        if(table[i] == c) {
            return i;
        }
    }
    return -1;
}

List **createRoadMap(int roads) {
    char input[256];
    char charTable[256];
    int flag=0;
    List **newList = (List**)malloc(sizeof(List*)*roads);
    while (getchar() != '\n');
    for(int i=0;i<roads;i++){
        newList[i]=(List*)malloc(sizeof(List));
        newList[i]->head = NULL;
        fgets(input,sizeof(input),stdin);
        if(indexNum(charTable,input[0]) == -1) {
            charTable[flag++] = input[0];
        } 
        if(indexNum(charTable,input[2])== -1) {
            charTable[flag++]=input[2];
        }
        addNode(newList,indexNum(charTable,input[0]),indexNum(charTable,input[2]),charTable);
    }
    return newList;
}

// Building *findNode()

// int pathing(List **roadMap, int item, char src, char dst) {

// }
