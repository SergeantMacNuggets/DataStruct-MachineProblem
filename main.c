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

typedef struct caseOne {
    int caseNum;
    int totalToll;
    struct caseOne *next;
} Case;

void addNode(List *newList[],int s, int d, char *table);
int pathing(List **roadMap, int item, char src, char dst);
void display(List *newList[]);

Case *createCase(int num, int toll) {
    Case *newCase = (Case*)malloc(sizeof(Case));
    newCase->caseNum = num;
    newCase->totalToll=toll;
    newCase->next=NULL;
    return newCase;
}

void displayCase(Case *head) {
    Case *ptr = head;
    while(ptr!=NULL) {
        printf("Case %d: %d\n",ptr->caseNum,ptr->totalToll);
        ptr=ptr->next;
    }
    printf("\n");
}

void getPath(int *x, char *src, char *dst) {
    char input[256];
    char num[256]="";
    int flag=0,i;
    printf("Path (toll, src, dest): ");
    fgets(input, sizeof(input),stdin);
    for(i=0;i<strlen(input);i++) {
        if(input[i]==' ' && !flag) {
            strncpy(num,input,i);
            *x = atoi(num);
            if(*x <= 0 || *x > 1000) {
                printf("Input must be (0 < p <= 1000), Try Again!\n");
                getPath(&(*x),&(*src),&(*dst));
            }
            flag = 1;
            i++;
            break;
        }
    }
    *src = input[i];
    *dst = input[i+2];
}

int main() {
    int input;
    int i=1,x;
    char src, dst;
    Case *head = NULL, *ptr=NULL, *tail=NULL;
    while(1) {
        printf("Number of Roads: ");
        scanf("%d",&input);
        if(input == -1) break;
        else if(input < 0 && input != -1) {
            printf("Input must be (0 <= n), Try Again!\n");
            continue;
        }
        List **firstMap = createRoadMap(input);
        // display(firstMap);
        getPath(&x,&src,&dst);
        if(head==NULL) {
            head = createCase(i,pathing(firstMap,x,src,dst));
            tail=head;
        } else {
            ptr = createCase(i,pathing(firstMap,x,src,dst));
            tail->next=ptr;
            tail=ptr;
        }
        i++;
    }
    displayCase(head);
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
        addNode(newList,indexNum(charTable,totalInput[i][2]),indexNum(charTable,totalInput[i][0]),charTable);
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

int ifVisited(char *table, char c){
    for(int i=0;i<strlen(table);i++) {
        if(table[i]==c) {
            return 1;
        }
    }
    return 0;
}

void pushAll(Building *list,Node **pQ,int item,char *c) {
    Building *ptr = list->next;
    while(ptr!=NULL) {
        if(ifVisited(c,ptr->type)==1) {
            ptr=ptr->next;
        } else {
            push(&(*pQ),ptr,tollCost(ptr->type,item));
            // printf("src: %c pushed: %c tollCost: %d\n",list->type,ptr->type,tollCost(ptr->type,item));
            ptr=ptr->next;
        }
    }
    // displayAll(pQ);
}

int pathing(List **roadMap, int item, char src, char dst) {
    int needItem=item;
    Node *pQ = NULL;
    char visitedNode[256]="";
    Building *ptr = findNode(roadMap,src);
    Building *final = findNode(roadMap,dst);
    Node *test = NULL;
    while(ptr!=final) {
        strncat(visitedNode,&(ptr->type),1);
        // printf("visitedNode: %s\n",visitedNode);
        pushAll(ptr,&pQ,needItem,visitedNode);
        ptr=findNode(roadMap,peek(pQ)->type);
        needItem=peekToll(pQ);
        if(peek(pQ)->type==final->type) {
            break;
        }
        // printf("pop: %c\n",peek(pQ)->type);
        pop(&pQ);
    }
    return needItem;
}
