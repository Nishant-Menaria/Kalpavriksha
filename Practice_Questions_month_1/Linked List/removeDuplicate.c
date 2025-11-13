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

void removeDuplicate(node** head){
    if(*head==NULL || (*head)->next==NULL)
        return;
    node* curr=*head;
    while(curr!=NULL){
        node* temp=curr->next;
        while(temp!=NULL && temp->data==curr->data){
            node* toDelete=temp;
            temp=temp->next;
            free(toDelete);
        }
        curr->next=temp;
        curr=temp;
    }
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

    printf("Linked List before removing Duplicates:\n");
    printLinkList(head);
    printf("\n");

    removeDuplicate(&head);

    printf("Linked List After removing Duplicates:\n");
    printLinkList(head);
    exit(0);
}