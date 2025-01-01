#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct building {
    char type;
    int toll;
    // int vertexNum;
    struct building *next;
}Building;

typedef struct list {
    Building *head;
    struct list *next;
}List;


List **createRoadMap(int roads);

void addNode(List *newList[],int s, int d, char *table);

Building *createBuilding(char x) {
    Building *newBuild = (Building*) malloc(sizeof(Building));
    newBuild->type = x;
    newBuild->next = NULL;
    return newBuild;
}

void display(List *newList[]);

int main() {
    int input;
    printf("Number of Roads: ");
    scanf("%d",&input);
    List **firstMap = createRoadMap(input);
    display(firstMap);
    // while(1) {
    //     printf("Number of Roads: ");
    //     scanf("%d",&input);
    //     // if(input == -1)break;
    //     createRoadMap(input);
    //     break;
    // }
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

void display(List *newList[]) {
    Building *ptr2;
    for(int i=0;i<5;i++) {
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
    // fgets(input,sizeof(input),stdin);
    return newList;
}