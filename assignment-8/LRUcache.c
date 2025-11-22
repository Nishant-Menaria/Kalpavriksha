#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct queue{
    int key;
    char* data;
    struct queue* next;
    struct queue* prev;
}queue;

#define Deleted (queue*)0xFFFFFFFF
queue* gHead;
queue* gTail;
queue** gHashmap;
int nodeInLinkList;
int gSizeOfCache;

void createCache();
int hashFunction(int key);
queue* creadteDoublyNode(char* data,int key);
char* get(int key);
void put(int key , char* data);
queue* insertToQueue(char* data, int key);
void insertToHashMap(queue* node , int key);
void moveToHeadAfterGet(queue* node);
int findInHashMap(int key);
int stringToDigit(char* s);

int main(){
    char terminalInput[50];
    scanf(" %[^\n]",terminalInput);
    while(1){
        char* command=strtok(terminalInput," ");
        if(command==NULL || strcmp(command, "createCache")!=0){
            printf("please initilize the cache first.\n");
            continue;
        }
        char* cacheSize=strtok(NULL , " ");
        int size=stringToDigit(cacheSize);
        while(size<1 || size>1000){
            printf("please enter size between 1-1000:");
            scanf("%d",&size);
        }
        gSizeOfCache=size;
        createCache();
        break;
    }

    while(1){
        scanf(" %[^\n]",&terminalInput);
        char* command=strtok(terminalInput," ");
        int key = stringToDigit(strtok(NULL , " "));
        char* data = strtok(NULL , " ");

        if(strcmp(command , "exit")==0)
            exit(0);
        
        if(strcmp(command, "put")==0){
            put(key,data);
        }else if(strcmp(command,"get")==0){
            printf("%s\n",get(key));
        }else{
            printf("please enter a valid command.\n");
        }
    }
}


void createCache(){
    gHashmap=(queue**)calloc(gSizeOfCache,sizeof(queue*));
    if(gHashmap==NULL){
        printf("Dynamic memory allocation fails.\n");
        return;
    }
}

int hashFunction(int key){
    return key%gSizeOfCache;
}

queue* creadteDoublyNode(char* data, int key){
    queue* newNode=(queue*)malloc(sizeof(queue));
    if(newNode==NULL){
        printf("Memory allocation fails.\n");
        exit(1);
    }
    newNode->key=key;
    newNode->data=data;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

queue* insertToQueue(char* data ,int key){
    queue* newNode=creadteDoublyNode(data,key);
    if(nodeInLinkList==gSizeOfCache){
        int index=findInHashMap(gTail->key);
        if(index!=-1)
            gHashmap[index]=Deleted;

        queue* toDelete=gTail;

        if(gTail->prev!=NULL){
            gTail=gTail->prev;
            gTail->next=NULL;
        }else{
            gHead=gTail=NULL;
        }

        free(toDelete);
        nodeInLinkList--;
    }
    if(gHead==NULL){
        gHead=newNode;
        gTail=newNode;
    }else{
        newNode->next=gHead;
        gHead->prev=newNode;
        gHead=newNode;
    }
    nodeInLinkList++;
    return newNode;
}

void insertToHashMap(queue* node , int key ){
    int index=hashFunction(key);

    for(int i = 0 ; i < gSizeOfCache ; i++){
        int try= (index + i*i)%gSizeOfCache;

        if(gHashmap[try]==NULL || gHashmap[try]==Deleted){
            gHashmap[try]=node;
            return;
        }
    }
}

char* get(int key){
    int index=hashFunction(key);

    for(int i = 0 ; i < gSizeOfCache ; i++){
        int try= (index + i*i)%gSizeOfCache;

        if(gHashmap[try]==NULL) return "null";

        if(gHashmap[try]==Deleted) continue;

        if(gHashmap[try]->key==key){
            moveToHeadAfterGet(gHashmap[try]);
            return gHashmap[try]->data;
        }
    }

    return "null";
}

int findInHashMap(int key){
    int index=hashFunction(key);

    for(int i = 0 ; i < gSizeOfCache ; i++){
        int try= (index + i*i)%gSizeOfCache;

        if(gHashmap[try]==NULL) return -1;

        if(gHashmap[try]==Deleted)  continue;

        if(gHashmap[try]->key==key)
            return try;
    }
    return -1;
}

void put(int key , char* data){
    char* copy=strdup(data);
    int index=findInHashMap(key);
    if(index==-1){
        insertToHashMap(insertToQueue(copy,key),key);
    }else{
        gHashmap[index]->data=copy;
        moveToHeadAfterGet(gHashmap[index]);
    }
}

int stringToDigit(char* s){
    if(s==NULL)
        return -1;
    int digit=0;
    for(int i = 0 ; s[i]!='\0' ; i++){
        digit=digit *10 +(s[i] - '0');
    }
    return digit;
}

void moveToHeadAfterGet(queue* node){
    if(node->prev==NULL)
        return;
    else if(node->next==NULL){
        gTail=gTail->prev;
        gTail->next=NULL;
        node->next=gHead;
        node->prev=NULL;
        gHead=node;
        return;
    }
    
    node->prev->next=node->next;
    node->next->prev=node->prev;
    node->prev=NULL;
    node->next=gHead;
    gHead=node;
}