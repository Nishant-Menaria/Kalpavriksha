#include<stdio.h>
#include<stdlib.h>
typedef struct linkListNode{
    int data;
    struct linkListNode* next;
}node;

node* createNode(int val){
    node* temp=(node*)malloc(sizeof(node));
    if(temp==NULL){
        printf("memory allocation fails/n");
        exit(1);
    }
    temp->data=val;
    temp->next=NULL;
    return temp;
}

void printLinkList(node *head){
    while(head!=NULL){
        printf("%d->",head->data);
        head=head->next;
    }
}

void rotateLinkList(node** head,int k , int size){
    node* temp=*head;
    node* newHead=NULL;

    for(int i = 1 ; temp!=NULL && i < size-k ; i++){
        temp=temp->next;
    }

    newHead=temp->next;
    temp->next=NULL;
    
    temp=newHead;
    while(temp->next!=NULL){
        temp=temp->next;
    }

    temp->next=*head;
    *head=newHead;
}

int main(){
    int n;
    printf("Enter number of elements in a link list:");
    scanf("%d",&n);
    
    int* arr=(int*)malloc(sizeof(int)*n);
    printf("Enter element of linklist :");
    for(int i=0;i<n;i++){
        scanf("%d",(arr+i));
    }

    node* head=NULL;
    node* prev=NULL;
    for(int i = 0 ; i < n ; i++){
        node* temp=createNode(arr[i]);
        if(head==NULL){
            head=temp;
            prev=head;
        }else{
            prev->next=temp;
            prev=temp;
        }
    }

    int K;
    printf("Enter the K(Number Of elemets to rotate):");
    scanf("%d",&K);

    printf("Linked List before Rotation:\n");
    printLinkList(head);

    rotateLinkList(&head , K, n);

    printf("Linked List After Rotation:\n");
    printLinkList(head);
    exit(0);
}