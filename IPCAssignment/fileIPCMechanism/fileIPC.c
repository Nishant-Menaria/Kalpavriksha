#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&arr[i]);
    }
    int id = fork();

    if( id == 0 ){

        printf("before sorting:\n");
        for(int i = 0 ; i < n ; i++){
            printf("%d\t",arr[i]);
        }
        printf("\n");

        FILE* fp=fopen("data.txt","r+");
        fwrite(arr , sizeof(int) ,n ,fp);

        wait(NULL);

        fread(arr , sizeof(int) , n , fp);

        fclose(fp);
        printf("after sorting:\n");
        for(int i = 0 ; i < n ; i++){
            printf("%d\t",arr[i]);
        }
    }else{
        FILE* fp = fopen("data.txt" , "r+");
        fread(arr , sizeof(int) , n , fp);
        qsort(arr , n ,sizeof(int) ,cmp);
        fwrite(arr , sizeof(int) ,n ,fp);
        fclose(fp);
    }
    return 0;
}