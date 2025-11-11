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

node* sortLinkList(node* head){
    if(head==NULL)
        return head;

    node* tail=head;
    while(tail->next!=NULL){
        tail=tail->next;
    }

    node* curr=head;
    node* prev=NULL;

    while(curr!=tail){

        if(curr->data==0){
            if(prev!=NULL){
                prev->next=curr->next;
                curr->next=head;
                head=curr;  
            }
        }else if(curr->data==2){
            if(prev!=NULL){
                prev->next=curr->next;
                tail->next=curr;
            }else{
                head=curr->next;
                tail->next=curr;
            }
            curr->next=NULL;
        }
    }
    return head;
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


    printf("Linked list before sorting:\n");
    printLinkList(head);


    head = sortLinkList(head);

    printf("Linked list after sorting:\n");
    printLinkList(head);
    
    exit(0);
}