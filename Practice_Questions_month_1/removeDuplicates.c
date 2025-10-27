#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(){
    int size;
    scanf("%d",&size);

    int *array = (int *)malloc(sizeof(int)*size);
    int largest = INT_MIN;

    for(int index =0 ; index < size ; index++){
        scanf("%d",(array + index));
        if(*(array+index) > largest)
            largest = *(array + index);
    }

    int* freqCount = (int*)calloc(largest+1 , sizeof(int));

    int newSize=0;
    for(int index = 0 ; index < size ; index++ ){
        if(freqCount[*(array + index)] == 0){
            freqCount[*(array + index)]=1;
            *(array + newSize)=*(array + index);
            newSize++;
        }
    }

    array = (int*)realloc(array,newSize * sizeof(int));

    for(int index = 0 ; index < newSize ; index++){
        printf("%d\t",*(array + index));
    }
    printf("\n");

    free(array);
    free(freqCount);

    return 0;
}