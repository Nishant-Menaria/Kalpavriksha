#include<stdio.h>
#include<stdlib.h>

int* firstAndLastOccuranceOfTarget(int *arr , int size , int target){
    
    int* ansArr=(int*)malloc(sizeof(int)*2);
    ansArr[0]=-1;
    ansArr[1]=-1;

    for(int i = 0 ; i < size ; i++){
        if(arr[i]==target){
            ansArr[0]=i;
            while(arr[i]==target)
                i++;
            ansArr[1]=i-1;
            return ansArr;
        }
    }
    return ansArr;
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
    int target;
    printf("Enter Target Value:");
    scanf("%d",&target);

    int* ansArr=firstAndLastOccuranceOfTarget(arr,n,target);

    if(ansArr[0]==-1)
        printf("%d does not occur in the given array.\n",target);
    else
        printf("%d apper from index %d to %d",target,ansArr[0],ansArr[1]);

    return 0;
}