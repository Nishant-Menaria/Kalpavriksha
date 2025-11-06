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

node* mergeLinkedList(node* head1 , node* head2){
    if(head1==NULL)
        return head2;
    else if(head2==NULL)
        return head1;

    node* newHead=NULL;
    if(head1->data<head2->data){
        newHead=head1;
        head1=head1->next;
    }else{
        newHead=head2;
        head2=head2->next;
    }

    node* temp=newHead;
    while(head1!=NULL && head2!=NULL){

        if(head1->data<head2->data){
            temp->next=head1;
            head1=head1->next;
        }else{
            temp->next=head2;
            head2=head2->next;
        }
        temp=temp->next;
    }

    if(head1==NULL)
        temp->next=head2;
    else
        temp->next=head1;

    return newHead;
}



int main(){
    
    node* head1=createLinkedList();
    node* head2=createLinkedList();

    printf("First Linked List:\n");
    printLinkList(head1);
    printf("\n");

    printf("second Linked List:\n");
    printLinkList(head2);
    printf("\n");

    node* newHead=mergeLinkedList(head1,head2);

    printf("Linked List After merging:\n");
    printLinkList(newHead);
    exit(0);
}