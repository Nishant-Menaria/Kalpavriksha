#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(){
    int size;
    scanf("%d",&size);

    int *array = (int *)malloc(sizeof(int)*size);

    int largest=INT_MIN;
    for(int index =0 ; index < size ;index++){
        scanf("%d",array + index);
        if(*(array + index) > largest){
            largest=*(array + index);
        }
    }

    int* freqCountArray=(int *)calloc(largest+1 , sizeof(int));

    for(int index =0; index<size ; index++){
        freqCountArray[*(array + index)]++;
    }

    for(int index = 0 ; index < largest +1 ; index++){
        if(*(freqCountArray+index)!=0){
            printf("Element %d appears %d times\n",index , *(freqCountArray + index ));
        }
    }


}