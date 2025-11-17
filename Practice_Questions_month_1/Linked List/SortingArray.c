#include<stdio.h>
#include<stdlib.h>

void swap(int* a , int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

int main(){
    int n;
    printf("Enter number of elements:");
    scanf("%d",&n);
    
    int* arr=(int*)malloc(sizeof(int)*n);
    printf("Enter elements(0's 1's and 2's only):");
    for(int i=0;i<n;i++){
        scanf("%d",(arr+i));
    }

    int i = 0 , j = 0 , k = n-1;
    while(j<=k){

        if(arr[j]==0){
            swap(arr + i , arr + j);
            i++;
            j++;
        }else if(arr[j]==1){
            j++;
        }else{
            swap(arr + j , arr + k);
            k--;
        }
    }

    printf("Array After sorting:\n");
    for(int i = 0 ; i< n ; i++){
        printf("%d\t",arr[i]);
    }

}