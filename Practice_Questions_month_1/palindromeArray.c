#include<stdio.h>
#include<stdlib.h>
int main(){
    int size;
    scanf("%d",&size);

    int* array =(int *)malloc(size * sizeof(int));

    for(int index=0; index<size ; index++){
        scanf("%d",array + index);
    }

    for(int low =0 , high =size-1 ; low<high ; low++ , high--){
        if(*(array+low)!=*(array+high)){
            printf("Not Palindrome\n");
            return 0;
        }
    }
    
    printf("Palindrome\n");
    return 0;
}