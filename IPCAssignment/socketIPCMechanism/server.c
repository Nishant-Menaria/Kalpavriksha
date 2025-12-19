#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>

pthread_mutex_t serverMutex;

void* clientRequestHandler(void* args){
    int clientSocket = * ((int *)args);
    free(args);
    FILE* fp;
    int balance,choice , amount;
    pthread_mutex_lock(&serverMutex);
    fp = fopen("./resource/accountDB.txt","r+");
    fscanf(fp , "%d" , &balance);
    recv(clientSocket , &choice ,sizeof(choice) , 0);
    if(choice == 1){
        recv(clientSocket , &amount , sizeof(int) , 0);
        if( amount > balance){
            printf("Not enough Balance.\n");
            return 0;
        }else{
            balance -= amount;
            fwrite(&balance , sizeof(int) , 1 ,fp);
        }
    }else if(choice == 2 ){
        recv(clientSocket , &amount , sizeof(int) , 0);
        balance+= amount;
        fwrite(&balance , sizeof(int) , 1 ,fp);
    }

    send( clientSocket , &balance ,sizeof(int) , 0);

    fclose(fp);
    pthread_mutex_unlock(&serverMutex);

    return NULL;
}

int main(){

    pthread_mutex_init(&serverMutex , NULL);
    int serverSocket = socket( AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8001);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket , (struct sockaddr*)&serverAddress , sizeof(serverAddress));

    listen( serverSocket , 5 );
    int clientSocket;
    while(1){
        clientSocket = accept(serverSocket , NULL ,NULL);
        int* CSocket = calloc(1, sizeof(int));
        *CSocket=clientSocket;

        pthread_t thread;
        pthread_create(&thread , NULL , &clientRequestHandler , CSocket);
        pthread_detach(thread);
    }

    pthread_mutex_destroy(&serverMutex);
    return 0;
}