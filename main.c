#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pQueue.h"

typedef struct list {
    Building *head;
}List;

int len;
List **createRoadMap(int roads);

void addNode(List *newList[],int s, int d, char *table);
void pathing(List **roadMap, int item, char src, char dst);


void display(List *newList[]);

int main() {
    int input;
    printf("Number of Roads: ");
    scanf("%d",&input);
    List **firstMap = createRoadMap(input);
    display(firstMap);
    pathing(firstMap,66,'E','S');
    return 0;
}

void addNode(List *newList[], int s, int d, char *table) {
    Building *tmp, *dest;
    dest = createBuilding(table[d]);
    tmp=newList[s]->head;
    while(tmp->next != NULL) tmp=tmp->next;
    tmp->next=dest;
}

void display(List **newList) {
    Building *ptr2;
    for(int i=0;i<len;i++) {
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
    char charTable[256]="";
    char **totalInput = (char**)malloc(sizeof(char*)*roads);
    while (getchar() != '\n');
    for(int i=0;i<roads;i++){
        totalInput[i]=(char*)malloc(256);
        fgets(input,sizeof(input),stdin);
        strcpy(totalInput[i],input);
        if(indexNum(charTable,input[0]) == -1) {
            strncat(charTable,&input[0],1);
        } 
        if(indexNum(charTable,input[2])== -1) {
            strncat(charTable,&input[2],1);
        }
    }
    List **newList = (List**)malloc(sizeof(List*)*strlen(charTable));
    Building *src;
    for(int x=0;x<strlen(charTable);x++) {
        newList[x]=(List*)malloc(sizeof(List));
        newList[x]->head = NULL;
        if(newList[x]->head==NULL) {
            src = createBuilding(charTable[x]);
            newList[x]->head = src;
        }
    }
    for(int i=0;i<roads;i++) {
        addNode(newList,indexNum(charTable,totalInput[i][0]),indexNum(charTable,totalInput[i][2]),charTable);
    }
    len=strlen(charTable);
    return newList;
}

Building *findNode(List **roadMap,char c) {
    for(int i=0;i<len;i++) {
        if(roadMap[i]->head->type==c) {
            return roadMap[i]->head;
        }
    }
    return NULL;
}

int tollCost(char c, int item) {
    if(isupper(c)) {
        if(item % 20 != 0 && item > 20) return item+(item/20)+1;
        if(item % 20==0) return item+(item/20);
        else return item+1;
    }
    return item+1;
}

void pushAll(Building *list,Node **pQ,int item) {
    Building *ptr = list->next;
    Node *p = *pQ;
    while(ptr!=NULL) {
        push(&p,ptr,tollCost(ptr->type,item));
        ptr=ptr->next;
    }
    *pQ = p;
}

void pathing(List **roadMap, int item, char src, char dst) {
    int needItem=item;
    Node *pQ = NULL;
    Building *ptr = findNode(roadMap,src);
    Building *final = findNode(roadMap,dst);

    while(ptr!=final) {
        pushAll(ptr,&pQ,needItem);
        ptr=findNode(roadMap,peek(pQ)->type);
        needItem=peekToll(pQ);
        pop(pQ);
    }
    printf("needItem: %d\n",needItem);
}
