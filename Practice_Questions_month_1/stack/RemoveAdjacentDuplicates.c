#include<stdio.h>
#include<stdlib.h>
#define STACK_SIZE 100

char stack[STACK_SIZE];
int gTop=-1;

void push(char val){
    stack[++gTop]=val;
}

void pop(){
    gTop--;
}


int main(){

    char* str = (char*)malloc(100*sizeof(char));
    printf("Enter Your string:");
    scanf("%s",str);

    for(int i = 0 ; str[i]!='\0' ; i++){

        if(stack[gTop]==str[i]){
            pop();
            continue;
        }
    

        if(gTop == -1 || stack[gTop]!=str[i])
            push(str[i]);
    
    }

    int i = 0 ;
    printf("%d",gTop);
    while(gTop>=0){
        str[i++]=stack[gTop--];
    }
    printf("String After Removing adjacent Duplicates.\n");
    for(int j = i-1 ; j>=0 ; j--){
        printf("%c",str[j]);
    }
}