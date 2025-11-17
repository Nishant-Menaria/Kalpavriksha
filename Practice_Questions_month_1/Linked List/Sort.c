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

node* sort(node* head){
    if(head==NULL || head->next==NULL)
        return head;
    node* tail=head;

    while(tail->next!=NULL){
        tail=tail->next;
    }

    node* prev=NULL;
    node* curr=head;
    int flag=1;
    node* stop=NULL;

    while(curr!=tail){
        if(curr->data==0){
            if(prev==NULL){
                prev=head;
                curr=curr->next;
            }else{
                prev->next=curr->next;
                curr->next=head;
                head=curr;
                curr=prev->next;
            }
        }else if(curr->data==2){
            if(prev==NULL){
                head=head->next;
                curr->next=tail->next;
                tail->next=curr;
                curr=head;
            }else{
                prev->next=curr->next;
                curr->next=tail->next;
                tail->next=curr;
                curr=prev->next;
            }
        }else{
            if(prev==NULL){
                prev=head;
                curr=curr->next;
            }else{
                prev=prev->next;
                curr=prev->next;
            }
        }
    }
    return head;
}

int main(){
    
    node* head=createLinkedList();
   
    printf("LinkList before sorting.\n");
    printLinkList(head);
    printf("\n");

    head=sort(head);

    printf("LinkList after sorting.\n");
    printLinkList(head);


}