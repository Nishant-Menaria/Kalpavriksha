#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STACK_SIZE 100

int gStack[STACK_SIZE];
int gTop=-1;
int gMinStack=__INT_MAX__;

void push(int val){
    if(gTop==STACK_SIZE-1){
        printf("Stack OverFlow.\n");
        return;
    }
    if(gMinStack > val)
        gMinStack=val;
    
    gStack[++gTop]=val;
}

void pop(){
    if(gTop<0){
        printf("Stack UnderFlow.\n");
        return;
    }
    if(gStack[gTop]==gMinStack){
        int newMinStack=__INT_MAX__;
        for(int i = 0 ; i < gTop ; i++){
            if(gStack[i]<newMinStack)
                newMinStack=gStack[i];
        }
        gMinStack=newMinStack;
    }
    gTop--;
}

int MinStack(){
    return gMinStack;
}



int main(){
    int n ;
    printf("Enter the Number of Stack Operations:");
    scanf("%d",&n);

    char** commands=(char**)malloc(n*sizeof(char*));
    printf("Enter stack operations :");
    for(int i = 0 ; i < n ; i++){
        commands[i]=(char*)malloc(10);
        scanf(" %[^\n]",commands[i]);
    }
    int values[n];
    printf("Enter the values that you want to push:");
    for(int i = 0 ; i < n ; i++){
        if(strcasecmp(*(commands + i) , "push")!=0)
            continue;
        scanf("%d",&values[i]);
    }


    for(int i = 0 ; i< n ; i++){
        if(strcasecmp(*(commands + i) , "MinStack")==0){
            printf("null\t");
            continue;
        }else if(strcasecmp(*(commands + i) , "getMin")==0){
            if(gTop == -1)
                printf("null\t");
            else
                printf("%d\t",gMinStack);
        }else if(strcasecmp(*(commands + i) , "push")==0){
            printf("null\t");
            push(values[i]);
        }else if(strcasecmp(*(commands + i) , "pop")==0){
            printf("null\t");
            pop();
        }else{
            if(gTop!=-1)
                printf("%d\t",gStack[gTop]);
            else 
                printf("null\t");
        }
    }
}