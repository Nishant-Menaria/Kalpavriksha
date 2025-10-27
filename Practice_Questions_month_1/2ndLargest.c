#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(){
    int sizeOfArray;
    do{
        scanf("%d",&sizeOfArray);
        if(sizeOfArray <= 2)
            printf("Size of Array should be greater than 2 \n");
    }while(sizeOfArray <= 2);

    int* array=(int *)calloc(sizeOfArray , sizeof(int));

    for(int arrayIndex = 0 ; arrayIndex < sizeOfArray ; arrayIndex++){
        scanf("%d",&array[arrayIndex]);
    }

    int largest=*(array);
    int secondLargest= INT_MIN;

    int smallest=*(array);
    int secondSmallest=INT_MAX;

    for(int arrayIndex=1 ; arrayIndex < sizeOfArray ; arrayIndex++){
        if( *(array + arrayIndex) > largest){
            secondLargest = largest;
            largest=*(array + arrayIndex);
        }else if( *(array + arrayIndex) < largest){
            if(*(array + arrayIndex) > secondLargest)
                secondLargest=*(array + arrayIndex);
        }

        if(*(array + arrayIndex) < smallest){
            secondSmallest = smallest;
            smallest = *(array + arrayIndex);
        }else if( *(array + arrayIndex) > smallest){
            if(*(array + arrayIndex) < secondSmallest){
                secondSmallest = *(array + arrayIndex);
            }
        }
    }

    if(secondLargest == INT_MIN && secondSmallest==INT_MAX){
        printf("All the Elments in the array are same");
        return 0;
    }
    printf("Second second Largest element : %d\n",secondLargest);
    printf("Second second smallest element : %d\n",secondSmallest);
    return 0;
}