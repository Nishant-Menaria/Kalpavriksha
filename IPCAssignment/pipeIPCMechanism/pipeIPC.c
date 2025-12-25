#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int cmp(const void *elem1, const void *elem2) {
    return (*(int *)elem1 - *(int *)elem2);
}

int main(){
    int n;
    scanf("%d",&n);
    int arr[n];

    int fd[2];
    if(pipe(fd) != 0){
        printf("creating pipe fails\n");
        return 1;
    }
    for(int index = 0 ; index < n ; index++){
        scanf("%d",&arr[index]);
    }

    printf("before sorting:\n");
    for(int index = 0 ; index < n ; index++){
        printf("%d\t",arr[index]);
    }

    printf("\n");

    int id = fork();

    if( id == 0 ){
        read(fd[0] , arr , sizeof(int) *n);
        close(fd[0]);
        qsort(arr , n ,sizeof(int) ,cmp);
        write(fd[1] , arr , sizeof(int) * n);
        close(fd[1]);
    }else{

        write(fd[1] , arr, sizeof(int)*n);
        close(fd[1]);
        wait(NULL);

        read(fd[0] , arr , sizeof(int)*n);
        close(fd[0]);

        printf("After sorting:\n");
        for(int index = 0 ; index < n ; index++){
            printf("%d\t",arr[index]);
        }
        printf("\n");
    }
    return 0;
}