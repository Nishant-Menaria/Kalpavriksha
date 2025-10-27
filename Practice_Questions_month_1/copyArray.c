#include<stdio.h>
#include<stdlib.h>

int main(){
    int size;
    scanf("%d",&size);

    int* array =(int *)malloc(size * sizeof(int));
    int* copyArray=(int *)malloc(size * sizeof(int));
    for(int index=0; index<size ; index++){
        scanf("%d",array + index);
    }

    for(int index=0 ; index <size ; index++){
        *(copyArray + index)=*(array + index);
    }

    printf("Original Array : \n");
    for(int index = 0 ; index<size ; index++){
        printf("%d\t",*(array + index));
    }
    printf("\n");

    printf("Copy Array : \n");
    for(int index = 0 ; index<size ; index++){
        printf("%d\t",*(copyArray + index));
    }

}

