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

node* createLinkedList(){
    int n;
    printf("Enter number of elements in the link list:");
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
    printf("\n");
    return head;
}

void printLinkList(node *head){
    while(head!=NULL){
        printf("%d->",head->data);
        head=head->next;
    }
}

node* swapingInPair(node* head){

    if(head==NULL || head->next==NULL)
        return head;

    node* prev=NULL;
    node* curr=head;
    node* temp=NULL;
    while(curr!=NULL && curr->next!=NULL){
        temp=curr->next;
        curr->next=temp->next;
        temp->next=curr;
        if(prev==NULL){
            head=temp;
        }else{
            prev->next=temp;
        }
        prev=curr;
        curr=curr->next;
    }
    return head;
}

int main(){
    
    node* head=createLinkedList();
   
    printf("LinkList before swaping.\n");
    printLinkList(head);
    printf("\n");

    head=swapingInPair(head);

    printf("LinkList after swaping.\n");
    printLinkList(head);


}