#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct queue{
    int key;
    char* data;
    struct queue* next;
    struct queue* prev;
}queue;


queue** gHashmap;
int nodeInLinkList;
int gSizeOfCache;

void createCache();
int hashFunction(int key);
queue* creadteDoublyNode(char* data,int key);
char* get(int key,queue** head , queue** tail);
void put(int key , char* data,queue** head , queue** tail);
queue* insertToQueue(char* data, int key , queue** head , queue** tail);
void insertToHashMap(queue* node , int key);
void moveToHeadAfterGet(queue* node,queue** head , queue** tail);
int findInHashMap(int key);
int stringToDigit(char* s);

int main(){
    queue* head=NULL;
    queue* tail=NULL;
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
        gSizeOfCache=size;
        createCache();
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
            put(key,data,&head,&tail);
        }else if(strcmp(command,"get")==0){
            printf("%s\n",get(key,&head,&tail));
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

queue* insertToQueue(char* data ,int key,queue** head , queue** tail){
    queue* newNode=creadteDoublyNode(data,key);
    if(nodeInLinkList==gSizeOfCache){
        int index=findInHashMap((*tail)->key);
        if(index!=-1)
            gHashmap[index]=NULL;

        queue* toDelete=(*tail);

        if((*tail)->prev!=NULL){
            *tail=(*tail)->prev;
            (*tail)->next=NULL;
        }else{
            *head=*tail=NULL;
        }

        free(toDelete);
        nodeInLinkList--;
    }
    if(*head==NULL){
        *head=newNode;
        *tail=newNode;
    }else{
        newNode->next=*head;
        (*head)->prev=newNode;
        *head=newNode;
    }
    nodeInLinkList++;
    return newNode;
}

void insertToHashMap(queue* node , int key ){
    int index=hashFunction(key);

    for(int i = 0 ; i < gSizeOfCache ; i++){
        int try= (index + i)%gSizeOfCache;

        if(gHashmap[try]==NULL){
            gHashmap[try]=node;
            return;
        }
    }
}

char* get(int key,queue** head , queue** tail){
    int index=hashFunction(key);

    for(int i = 0 ; i < gSizeOfCache ; i++){
        int try= (index + i)%gSizeOfCache;

        if(gHashmap[try]==NULL) continue;

        if(gHashmap[try]->key==key){
            moveToHeadAfterGet(gHashmap[try],head,tail);
            return gHashmap[try]->data;
        }
    }

    return "null";
}

int findInHashMap(int key){
    int index=hashFunction(key);

    for(int i = 0 ; i < gSizeOfCache ; i++){
        int try= (index + i)%gSizeOfCache;

        if(gHashmap[try]==NULL)  continue;

        if(gHashmap[try]->key==key)
            return try;
    }
    return -1;
}

void put(int key , char* data ,queue** head , queue** tail){
    char* copy=strdup(data);
    int index=findInHashMap(key);
    if(index==-1){
        insertToHashMap(insertToQueue(copy,key,head,tail),key);
    }else{
        gHashmap[index]->data=copy;
        moveToHeadAfterGet(gHashmap[index],head,tail);
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

void moveToHeadAfterGet(queue* node,queue** head , queue** tail){
    if(node->prev==NULL)
        return;
    else if(node->next==NULL){
        *tail=(*tail)->prev;
        (*tail)->next=NULL;
        node->next=*head;
        node->prev=NULL;
        *head=node;
        return;
    }
    
    node->prev->next=node->next;
    node->next->prev=node->prev;
    node->prev=NULL;
    node->next=*head;
    *head=node;
}