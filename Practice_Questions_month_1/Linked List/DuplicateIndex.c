#include<stdio.h>
#include<stdlib.h>

int duplicateIndex(int *arr , int size){

    for(int i = 0 ; i < size - 1 ; i++){
        for(int j= i + 1 ; j < size ; j++){
            if(arr[i]==arr[j])
                return j;
        }
    }
    return -1;
}

int main(){
    int n;
    printf("Enter number of elements:");
    scanf("%d",&n);
    
    int* arr=(int*)malloc(sizeof(int)*n);
    printf("Enter elements:");
    for(int i=0;i<n;i++){
        scanf("%d",(arr+i));
    }

    int index=duplicateIndex(arr,n);

    if(index!=-1){
        printf("First occuring Duplicate is %d at index %d\n",arr[index],index);
    }else{
        printf("There is not duplicate element.\n");
    }

}