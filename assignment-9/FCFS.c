#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HASHMAP_SIZE 20

enum PROCESS_STATUS{
    READY,
    WAITING,
    TERMINATED,
    KILLED
};

typedef struct PCB{
    char name[20];
    int pID;
    int brustTime;
    int IoStart;
    int IoDuration;
    int killTime;
    int status;
    int inputTimeRemaning;
    int brustTimeremaning;
    int TAT;
    int WT;
    struct PCB* next;
}PCB;

typedef struct queueNode{
    PCB* pcbPointer;
    struct queueNode* next;
}queueNode;

typedef struct queue{
    queueNode* head;
    queueNode* tail;
}queue;

typedef struct FCFS{
    PCB* hashMap[HASHMAP_SIZE];
    queue* readyQueue;
    queue* watingQueue;
    queue* terminatedQueue;
}FCFS;

int hashFunction(int pID);
void insertToHashMap(FCFS* fcfsInstance,PCB* process);
void initilizeFcfsInstance(FCFS* fcfsInstance);
PCB* createProcess();
PCB* initializeProcess(char* input);
void printProcesses(FCFS* fcfsInstance);
void insertToQueue(queue** queuePointer , PCB* process);
PCB* dequeueFromReadyQueue(queue** queuePointer);
PCB* dequeueFromWatingQueue(queue** queuePointer , PCB* processPointer);
queueNode* createQueueNode(PCB* process);
void initializingKillTime(FCFS* fcfsinstance,char* terminalInput);
void freeQueue(FCFS* fcfsInstance);
void freeHashMap(FCFS* fcfsInstance);



int main(){
    FCFS* fcfsInstance=(FCFS*)calloc(1,sizeof(FCFS));
    initilizeFcfsInstance(fcfsInstance);
    char* terminalInput=calloc(50,sizeof(char));
    while(1){
        scanf(" %[^\n]",terminalInput);

        if(strcmp(terminalInput,"exit")==0){
            break;
        }


        if( strncmp(terminalInput,"KILL",3)==0){
                initializingKillTime(fcfsInstance,terminalInput);
        }else{
            PCB* newProcess=initializeProcess(terminalInput);
            insertToQueue(&(fcfsInstance->readyQueue),newProcess);
            insertToHashMap(fcfsInstance,newProcess);
            newProcess->status=READY;
        }
    }

    PCB* currProcess=NULL;
    int executingTime=1;
    while(1){

        if( !currProcess && !fcfsInstance->readyQueue->head && !fcfsInstance->watingQueue->head){
            break;
        }

        if(currProcess==NULL && fcfsInstance->readyQueue->head!=NULL){
            currProcess=dequeueFromReadyQueue( &(fcfsInstance->readyQueue) );
        }

        queueNode* temp=fcfsInstance->watingQueue->head;
        if(temp){
            temp->pcbPointer->inputTimeRemaning--;
            if(temp->pcbPointer->inputTimeRemaning==0){
                insertToQueue( &(fcfsInstance->readyQueue ), dequeueFromWatingQueue( &(fcfsInstance->watingQueue) , temp->pcbPointer) );
            } 
            temp=temp->next;
        }

        if(currProcess){
            currProcess->brustTimeremaning--;
            if( currProcess->brustTimeremaning == 0 ){
                printf("%d\t%d\n",currProcess->pID,executingTime);
                currProcess->TAT = executingTime;
                currProcess->WT= currProcess->TAT - currProcess->brustTime;
                insertToQueue(&(fcfsInstance->terminatedQueue) , currProcess);
                currProcess->status=TERMINATED;
                currProcess=NULL;
            }else if( currProcess->IoStart>0 && (currProcess->brustTime - currProcess->brustTimeremaning) == currProcess->IoStart){
                insertToQueue(&(fcfsInstance->watingQueue) , currProcess);
                currProcess->status=WAITING;
                currProcess=NULL;
            }else if( currProcess->killTime>0 && currProcess->killTime==executingTime){
                insertToQueue(&(fcfsInstance->terminatedQueue) , currProcess);
                currProcess->TAT=currProcess->WT=0;
                currProcess->status=KILLED; 
                currProcess=NULL;
            }
        }

        

        executingTime++;
        
    }
    printProcesses(fcfsInstance);
    freeQueue(fcfsInstance);
    freeHashMap(fcfsInstance);
    return 0;
}

int hashFunction(int pID){
    return pID%HASHMAP_SIZE;
}

void insertToHashMap(FCFS* fcfsInstance , PCB* process){
    int index=hashFunction(process->pID);
    process->next=fcfsInstance->hashMap[index];
    fcfsInstance->hashMap[index]=process;
}

void initilizeFcfsInstance(FCFS* fcfsInstance){
    if(!fcfsInstance)
        exit(1);

    fcfsInstance->readyQueue=(queue*)calloc(1,sizeof(queue));
    fcfsInstance->watingQueue=(queue*)calloc(1,sizeof(queue));
    fcfsInstance->terminatedQueue=(queue*)calloc(1,sizeof(queue));
}

PCB* createProcess(){
    PCB* newProcess=(PCB*)calloc(1,sizeof(PCB));
    if(!newProcess){
        printf("memory allocation fails.\n");
        exit(1);
    }
    newProcess->brustTime=0;
    newProcess->IoDuration=0;
    newProcess->IoStart=0;
    newProcess->next=NULL;
    newProcess->pID=0;
    return newProcess;
}

PCB* initializeProcess(char* input){
    if(input==NULL)
        return NULL;
    PCB* newProcess=createProcess();
    sscanf(input , "%s %d %d %d %d",
                    newProcess->name,
                    &(newProcess->pID),
                    &(newProcess->brustTime),
                    &(newProcess->IoStart),
                    &(newProcess->IoDuration));


    newProcess->brustTimeremaning=newProcess->brustTime;
    newProcess->inputTimeRemaning=newProcess->IoDuration;

    return newProcess;
}

queueNode* createQueueNode(PCB* process){
    queueNode* newNode=(queueNode*)calloc(1,sizeof(queueNode));
    if(!newNode){
        printf("memory allocation fails.\n");
        exit(1);
    }

    newNode->pcbPointer=process;
    newNode->next=NULL;
    return newNode;
}

void insertToQueue(queue** queuePointer , PCB* process){
    queueNode* newNode= createQueueNode(process);
    
    if( (*queuePointer)->head==NULL) {
        (*queuePointer)->head = (*queuePointer)->tail = newNode;
    }else{
        (*queuePointer)->tail->next=newNode;
        (*queuePointer)->tail=newNode;
    }
}

PCB* dequeueFromReadyQueue(queue** queuePointer){

    queueNode* temp=(*queuePointer)->head;
    if((*queuePointer)->head==(*queuePointer)->tail){
        (*queuePointer)->head=(*queuePointer)->tail=NULL;
    }else{
        (*queuePointer)->head=(*queuePointer)->head->next;
    }
    PCB* toReturn=temp->pcbPointer;
    free(temp);
    return toReturn;
}

PCB* dequeueFromWatingQueue(queue** queuePointer , PCB* processPointer){
    queueNode* prev=NULL;
    queueNode* curr=(*queuePointer)->head;
    while(curr){
        if(curr->pcbPointer->pID == processPointer->pID){
            if(prev==NULL){
                (*queuePointer)->head=(*queuePointer)->head->next;
                if(!((*queuePointer)->head))
                    (*queuePointer)->tail=NULL;
            }else{
                prev->next=curr->next;
            }
            PCB* toReturn=curr->pcbPointer;
            free(curr);
            return toReturn;
        }
        prev=curr;
        curr=curr->next;
    }
    printf("No process with %d process ID.\n",processPointer->pID);
    return NULL;
}

void initializingKillTime(FCFS* fcfsinstance,char* terminalInput){
    char command[5];
    int pID,killTime;
    sscanf(terminalInput,"%s %d %d",command,&pID,&killTime);
    int index=hashFunction(pID);
    PCB* process=fcfsinstance->hashMap[index];

    while( process!=NULL && process->pID!=pID)
        process=process->next;

    if(process!=NULL)
        process->killTime=killTime;
    else
        printf("No such Process.\n");
}

void printProcesses(FCFS* fcfsInstance){
    printf("PID\tName\tCPU\tIO\tSTATUS\tTATd\tWT\n");
    for(int index=0 ; index<HASHMAP_SIZE ; index++){
        PCB* process=fcfsInstance->hashMap[index];
        if(process){
            printf("%d\t%s\t%d\t%d\t",process->pID,process->name,process->brustTime,process->IoDuration);
            if(process->status==KILLED){
                printf("KILLED AT %d\t",process->killTime);
            }else{
                printf("OK\t");
            }
            printf("%d\t%d\n",process->TAT,process->WT);
        }
    }
   
}

void freeQueue(FCFS* fcfsInstance){
    queueNode* toDelete=fcfsInstance->readyQueue->head;
    while(fcfsInstance->readyQueue->head){
        free(toDelete);
        toDelete=fcfsInstance->readyQueue->head;
        fcfsInstance->readyQueue->head=fcfsInstance->readyQueue->head->next;
    }
    toDelete=fcfsInstance->watingQueue->head;
    while(fcfsInstance->watingQueue->head){
        free(toDelete);
        toDelete=fcfsInstance->watingQueue->head;
        fcfsInstance->watingQueue->head=fcfsInstance->watingQueue->head->next;
    }
    toDelete=fcfsInstance->terminatedQueue->head;
    while(fcfsInstance->terminatedQueue->head){
        free(toDelete);
        toDelete=fcfsInstance->terminatedQueue->head;
        fcfsInstance->terminatedQueue->head=fcfsInstance->terminatedQueue->head->next;
    }
}

void freeHashMap(FCFS* fcfsInstance){
    PCB* temp;
    for(int i = 0 ; i < HASHMAP_SIZE ; i++){
        temp=fcfsInstance->hashMap[i];
        while(temp){
            PCB* toDelete = temp;
            temp=temp->next;
            free(toDelete);
        }
    }
}