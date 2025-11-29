#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct queue{
    int key;
    char* data;
    struct queue* next;
    struct queue* prev;
}queue;

typedef struct{
    queue* head;
    queue* tail;
    queue** hashMap;
    int cacheSize;
    int count;
}LRUCache;


queue** gHashmap;
int nodeInLinkList;
int gSizeOfCache;

LRUCache* createCache(int size);
int hashFunction(int key);
queue* creadteDoublyNode(char* data,int key);
char* get(int key, LRUCache* ptr);
void put(int key , char* data, LRUCache* ptr);
queue* insertToQueue(char* data, int key ,  LRUCache* ptr);
void insertToHashMap(queue* node , int key , LRUCache* ptr);
void moveToHeadAfterGet(queue* node, LRUCache* ptr);
int findInHashMap(int key , LRUCache* ptr);
int stringToDigit(char* s);

int main(){
    LRUCache* ptr=NULL;
    char terminalInput[50];
    while(1){
        scanf(" %[^\n]",terminalInput);
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
        ptr=createCache(size);
        break;
    }

    while(1){
        scanf(" %[^\n]",terminalInput);
        char* command=strtok(terminalInput," ");
        int key = stringToDigit(strtok(NULL , " "));
        char* data = strtok(NULL , " ");

        if(strcmp(command , "exit")==0)
            exit(0);
        
        if(strcmp(command, "put")==0){
            put(key,data,ptr);
        }else if(strcmp(command,"get")==0){
            printf("%s\n",get(key,ptr));
        }else{
            printf("please enter a valid command.\n");
        }
    }
}


LRUCache* createCache(int size){
    LRUCache* temp=(LRUCache*)calloc(1,sizeof(LRUCache));
    temp->hashMap=(queue**)calloc(size,sizeof(queue*));
    if(temp==NULL ||  temp->hashMap==NULL){
        printf("Dynamic memory allocation fails.\n");
        exit(1);
    }
    temp->head=temp->tail=NULL;
    temp->cacheSize=size;
    temp->count=0;
    return temp;
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

queue* insertToQueue(char* data ,int key,LRUCache* ptr){
    queue* newNode=creadteDoublyNode(data,key);
    if(ptr->cacheSize==ptr->count){
        int index=findInHashMap(ptr->tail->key,ptr);
        if(index!=-1)
            ptr->hashMap[index]=NULL;

        queue* toDelete=ptr->tail;

        if(ptr->tail->prev!=NULL){
            ptr->tail=ptr->tail->prev;
            ptr->tail->next=NULL;
        }else{
            ptr->head=ptr->tail=NULL;
        }

        free(toDelete);
        ptr->count--;
    }
    if(ptr->head==NULL){
        ptr->head=newNode;
        ptr->tail=newNode;
    }else{
        newNode->next=ptr->head;
        ptr->head->prev=newNode;
        ptr->head=newNode;
    }
    ptr->count++;
    return newNode;
}

void insertToHashMap(queue* node , int key , LRUCache* ptr){
    int index=hashFunction(key);

    for(int i = 0 ; i < ptr->cacheSize ; i++){
        int try= (index + i)% (ptr->cacheSize);

        if( ptr->hashMap[try]==NULL){
            ptr->hashMap[try]=node;
            return;
        }
    }
}

char* get(int key,LRUCache* ptr){
    int index=hashFunction(key);

    for(int i = 0 ; i < ptr->cacheSize ; i++){
        int try= (index + i)% (ptr->cacheSize);

        if( ptr->hashMap[try]==NULL) continue;

        if( ptr->hashMap[try]->key==key){
            moveToHeadAfterGet( ptr->hashMap[try],ptr);
            return ptr->hashMap[try]->data;
        }
    }

    return "null";
}

int findInHashMap(int key , LRUCache* ptr){
    int index=hashFunction(key);

    for(int i = 0 ; i < ptr->cacheSize ; i++){
        int try= (index + i)% (ptr->cacheSize);

        if( ptr->hashMap[try]==NULL)  continue;

        if(ptr->hashMap[try]->key==key)
            return try;
    }
    return -1;
}

void put(int key , char* data , LRUCache* ptr){
    char* copy=strdup(data);
    int index=findInHashMap(key,ptr);
    if(index==-1){
        insertToHashMap(insertToQueue(copy,key,ptr),key,ptr);
    }else{
        ptr->hashMap[index]->data=copy;
        moveToHeadAfterGet(gHashmap[index],ptr);
    }
}

int stringToDigit(char* number){
    if(number==NULL)
        return -1;
    int digit=0;
    for(int index = 0; number[index]!='\0'; index++){
        digit=digit *10 +(number[index] - '0');
    }
    return digit;
}

void moveToHeadAfterGet(queue* node,LRUCache* ptr){
    if(node->prev==NULL)
        return;
    else if(node->next==NULL){
        ptr->tail=ptr->tail->prev;
        ptr->tail->next=NULL;
        node->next=ptr->head;
        node->prev=NULL;
        ptr->head=node;
        return;
    }
    
    node->prev->next=node->next;
    node->next->prev=node->prev;
    node->prev=NULL;
    node->next=ptr->head;
    ptr->head=node;
}