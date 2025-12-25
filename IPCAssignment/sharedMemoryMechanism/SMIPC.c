#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int cmp(const void *elem1, const void *elem2) {
    return (*(int *)elem1 - *(int *)elem2);
}

int main(){
    key_t key;
    int shmID;
    int* shm;
    int n;
    scanf("%d",&n);

    key = ftok("data",77);

    shmID = shmget(key , sizeof(int)*n , 0666 | IPC_CREAT);

    shm = (int *)shmat(shmID , NULL , 0);
    
    for(int index = 0 ; index < n ; index++){
        scanf("%d",&shm[index]);
    }

    printf("before sorting:\n");
    for(int index = 0 ; index < n ; index++){
        printf("%d\t",shm[index]);
    }

    printf("\n");
    int id = fork();

    if( id == 0 ){

        qsort(shm , n ,sizeof(int) ,cmp);
        shmdt(shm);

    }else{
        
        wait(NULL);

        printf("After sorting:\n");
        for(int index = 0 ; index < n ; index++){
            printf("%d\t",shm[index]);
        }
        printf("\n");
        shmdt(shm);
    }
    return 0;
}