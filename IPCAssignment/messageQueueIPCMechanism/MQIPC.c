#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(){
    key_t key;
    int msgID;
    int n;
    scanf("%d",&n);
    int arr[n];
    key = ftok("data",77);

    msgID = msgget(key , 0666);
    
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&arr[i]);
    }

    printf("before sorting:\n");
    for(int i = 0 ; i < n ; i++){
        printf("%d\t",arr[i]);
    }

    printf("\n");
    msgsnd(msgID , arr , sizeof(int)*n , 0);

    int id = fork();

    if( id == 0 ){

        msgrcv(msgID , arr , sizeof(int)*n ,1 , 0);
        qsort(arr , n ,sizeof(int) ,cmp);
        msgsnd(msgID , arr , sizeof(int)*n , 0);
        exit(0);
        
    }else{

        wait(NULL);

        msgrcv(msgID , arr , sizeof(int)*n ,2 , 0);
        printf("After sorting:\n");
        for(int i = 0 ; i < n ; i++){
            printf("%d\t",arr[i]);
        }
        printf("\n");
        msgctl(msgID , IPC_RMID , NULL);
    }
    return 0;
}