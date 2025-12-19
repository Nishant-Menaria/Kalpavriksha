#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){
    
    int clientSocket = socket( AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8001);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if( connect( clientSocket , (struct sockaddr *)&serverAddress , sizeof(serverAddress) ) !=0 ){
        printf("Connetion fails\n");
        exit(1);
    }
    
    int choice,amount;

    do{
        printf("1. Withdraw\n");
        printf("2. Deposit\n");
        printf("3. Display Balance\n");
        printf("4. exit\n");
        scanf("%d",&choice);
        if(choice < 1 || choice > 4){
            printf("Enter a valid option.\n");
            continue;
        }

        if(choice == 4){
            exit(0);
        }

        send( clientSocket , &choice , sizeof(int) , 0);

        if(choice == 1 || choice == 2 ){
            printf("enter Amount:");
            scanf("%d",&amount);
            send(clientSocket , &amount , sizeof(int) , 0);
        }

        recv(clientSocket , &amount , sizeof(int) , 0);

        if(choice ==1 || choice ==2){
            printf("Update Balance is :%d\n",amount);
            continue;
        }else{
            printf("Your current Balance is: %d\n",amount);
        }

    }while(1);


    return 0;
}

