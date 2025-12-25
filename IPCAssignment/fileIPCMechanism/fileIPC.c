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
        FILE* fp = fopen("data.txt" , "r");
        fread(arr , sizeof(int) , n , fp);
        fclose(fp);

        qsort(arr , n ,sizeof(int) ,cmp);

        fp=fopen("data.txt","w");
        if(fp==NULL){
            printf("error in opening file.\n");
            exit(1);
        }
        fwrite(arr , sizeof(int) ,n ,fp);
        fclose(fp);
        fclose(fp);
       
    }else{

        FILE* fp=fopen("data.txt","w");
        if(fp==NULL){
            printf("error in opening file.\n");
            exit(1);
        }
        fwrite(arr , sizeof(int) ,n ,fp);
        fclose(fp);

        wait(NULL);

        fp=fopen("data.txt","r");
        fread(arr , sizeof(int) , n , fp);

        fclose(fp);
        printf("after sorting:\n");
        for(int index = 0 ; index < n ; index++){
            printf("%d\t",arr[index]);
        }
    }
    return 0;
}