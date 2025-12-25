#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>

#define MAX 100

struct message {
    long mtype;       
    int n;             
    int arr[MAX];     
};

int cmp(const void *elem1, const void *elem2) {
    return (*(int *)elem1 - *(int *)elem2);
}

int main(){
    key_t key;
    int msgID;
    struct message msg;
    scanf("%d",&msg.n);

    key = ftok("data",77);

    msgID = msgget(key , 0666 | IPC_CREAT);
    
    for(int index = 0 ; index < msg.n ; index++){
        scanf("%d",&msg.arr[index]);
    }

    printf("before sorting:\n");
    for(int index = 0 ; index < msg.n ; index++){
        printf("%d\t",msg.arr[index]);
    }
    printf("\n");

    int id = fork();

    if( id == 0 ){

        msgrcv(msgID , &msg , sizeof(msg) - sizeof(long) ,1 , 0);
        qsort( msg.arr , msg.n ,sizeof(int) ,cmp);
        msg.mtype=2;
        msgsnd(msgID , &msg , sizeof(msg) - sizeof(long) , 0);
        exit(0);
        
    }else{
        
        msg.mtype=1;
        msgsnd(msgID , &msg , sizeof(msg) - sizeof(long)  , 0);
        wait(NULL);

        msgrcv(msgID , &msg , sizeof(msg) - sizeof(long) ,2 , 0);
        printf("After sorting:\n");
        for(int index = 0 ; index < msg.n ; index++){
            printf("%d\t",msg.arr[index]);
        }
        printf("\n");
        msgctl(msgID , IPC_RMID , NULL);
    }
    return 0;
}