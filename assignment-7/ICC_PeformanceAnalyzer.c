#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Players_data.h"


typedef struct MyPlayer {
    Player player;
    float peformanceIndex;
    struct MyPlayer* next;
} MyPlayer;

typedef struct {
    int teamID;
    char* name;
    int totalPlayer;
    float averageBattingStrikeRate;
} Team;



MyPlayer* createPlayer(Player* player);
void insertIntoList(Player* player , MyPlayer** head);
// void addPlayer(MyPlayer** head);


int main(){
    MyPlayer* head[3]={NULL};
    int choice;

    for(int playerIndex = 0 ;playerIndex < playerCount ; playerIndex++ ){
        if(strcmp(players[playerIndex].role, "Batsman")==0){

            insertIntoList((players + playerIndex) , head + 0);

        }else if(strcmp(players[playerIndex].role, "Bowler")==0){
            insertIntoList((players + playerIndex) , head + 1);
        }else{
            insertIntoList((players + playerIndex) , head + 2);
        }
    }

    for(int i = 0  ; i < 3 ; i++){
        MyPlayer* temp=head[i];
        printf("Printing Head %d\n\n\n\n", i+1);
        while(temp!=NULL){
            printf("%d %s %f %s\n",temp->player.id , temp->player.name , temp->peformanceIndex , temp->player.role);
            temp=temp->next;
        }
    }
    // while(1){
    //     printf("==============================================\n\n");
    //     printf("ICC ODI Player Peformance Analyzer.\n\n");
    //     printf("==============================================\n\n");

    //     printf("1. Add Player to Team.\n");
    //     printf("2. Display Players of a Specific Team");
    //     printf("3. Display Teams by Average Batting Strike Rate.\n");
    //     printf("4. Display Top K Players of a Specific Team by Role.\n");
    //     printf("5. Display all Players of specific role Across All Teams by performance index.\n");
    //     printf("6. Exit\n\n");
    //     printf("==============================================\n\n");
    //     priintf("Enter your choice:");

    //     scanf("%d",&choice);

    //     switch(choice){
    //         case 1:{
    //             addPlayer(&head);
    //             break;
    //         }
    //         case 2:{

    //         }
    //         case 3:{

    //         }
    //         case 4:{

    //         }
    //         case 5:{

    //         }
    //         case 6:{
    //             exit(1);
    //         }
    //     }

    // }
}

MyPlayer* createPlayer(Player* player){
    MyPlayer* myPlayer = (MyPlayer*)malloc(sizeof(MyPlayer));
    myPlayer->player=*player;
    myPlayer->next=NULL;

    if(strcmp(player->role , "Batsman")==0){
        myPlayer->peformanceIndex = (player->battingAverage * player->strikeRate)/100;
    }else if(strcmp (player->role,"Bowler")==0){
        myPlayer->peformanceIndex = (player->wickets *2) + (100 - player->economyRate);
    }else{
        myPlayer->peformanceIndex =((player->battingAverage* player->strikeRate)/100) + (player->wickets*2);
    }
    return myPlayer;
}


void insertIntoList(Player* player , MyPlayer** head){

    MyPlayer* newPlayer=createPlayer(player);

    if(*head==NULL){
        *head=newPlayer;
    }else{
        MyPlayer* prev=NULL;
        MyPlayer* curr= *head;

        while(curr!=NULL && curr->peformanceIndex > newPlayer->peformanceIndex ){
            prev=curr;
            curr=curr->next;
        }

        if(prev==NULL){
            newPlayer->next=*head;
            *head=newPlayer;
        }else{
            prev->next=newPlayer;
            newPlayer->next=curr;
        }
    }

}

// void addPlayer(MyPlayer** head){
//     Player* newPlayer=(Player*)malloc(sizeof(Player));
//     printf("Enter ")
// }