#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Players_data.h"


typedef struct MyPlayer {
    Player player;
    float peformanceIndex;
    struct MyPlayer* next;
} MyPlayer;

typedef struct teamNode{
    MyPlayer* player;
    struct teamNode* next;
}teamNode;

typedef struct Team{
    int teamID;
    const char* teamName;
    int playerCount;
    float averageBattingStrikeRate;
    teamNode* role[3];
} Team;



Team* gTeams[10];

MyPlayer* createPlayer(Player player);
void merge(int low ,int mid , int high , Team** teamList);
teamNode* createTeamNode(MyPlayer* player);
void insertIntoList(MyPlayer* newPlayer , MyPlayer** head);
Team* createTeam(int teamID,const char* name);
void initilizeTeams();
void insertIntoTeamsList(MyPlayer* player);
void seperatingByRole(MyPlayer* player, int teamID);
void addToTeam(MyPlayer* player , teamNode** head);
void addPlayer(MyPlayer** head);
void displayAllPlayersOfSpecificTeam();
void displayTopPlayerOfSpecificTeam();
void displayAllPlayersOfSpecificRole(MyPlayer** head);
void sortTeams(int low , int high , Team** teamList);
void printTeams(Team** teamList);

int main(){
    initilizeTeams();
    MyPlayer* head[3]={NULL};
    Team* sortedTeams[10]={NULL};
    int choice;

    for(int playerIndex = 0 ;playerIndex < playerCount ; playerIndex++ ){
        if(strcmp(players[playerIndex].role, "Batsman")==0){

            insertIntoList(createPlayer(players[playerIndex]) , &head[0]);

        }else if(strcmp(players[playerIndex].role, "Bowler")==0){
            insertIntoList(createPlayer(players[playerIndex]) , &head[1]);
        }else{
            insertIntoList(createPlayer(players[playerIndex]) , &head[2]);
        }
    }

    for(int role = 0 ;role < 3 ; role++){
        MyPlayer* temp =  head[role];
        while(temp!=NULL){
            insertIntoTeamsList(temp);
            temp=temp->next;
        }
    }

    for(int team = 0 ; team < 10 ; team++ ){
        sortedTeams[team]= gTeams[team];
    }
    sortTeams(0,9,&sortedTeams[0]);

    while(1){
        printf("==============================================\n\n");
        printf("ICC ODI Player Peformance Analyzer.\n\n");
        printf("==============================================\n\n");

        printf("1. Add Player to Team.\n");
        printf("2. Display Players of a Specific Team\n");
        printf("3. Display Teams by Average Batting Strike Rate.\n");
        printf("4. Display Top K Players of a Specific Team by Role.\n");
        printf("5. Display all Players of specific role Across All Teams by performance index.\n");
        printf("6. Exit\n\n");
        printf("==============================================\n\n");
        printf("Enter your choice:");

        scanf("%d",&choice);

        switch(choice){
            case 1:{
                addPlayer(&head[0]);
                sortTeams(0,9,&sortedTeams[0]);
                break;
            }
            case 2:{
                displayAllPlayersOfSpecificTeam();
                break;
            }
            case 3:{
                printTeams(&sortedTeams[0]);
                break;
            }
            case 4:{
                displayTopPlayerOfSpecificTeam();
                break;
            }
            case 5:{
                displayAllPlayersOfSpecificRole(&head[0]);
                break;
            }
            case 6:{
                exit(1);
            }
        }

    }
}

MyPlayer* createPlayer(Player player){
    MyPlayer* myPlayer = (MyPlayer*)malloc(sizeof(MyPlayer));
    myPlayer->player=player;
    myPlayer->next=NULL;

    if(strcmp(player.role , "Batsman")==0){
        myPlayer->peformanceIndex = (player.battingAverage * player.strikeRate)/100;
    }else if(strcmp (player.role,"Bowler")==0){
        myPlayer->peformanceIndex = (player.wickets *2) + (100 - player.economyRate);
    }else{
        myPlayer->peformanceIndex =((player.battingAverage* player.strikeRate)/100) + (player.wickets*2);
    }
    return myPlayer;
}


void insertIntoList(MyPlayer* newPlayer , MyPlayer** head){

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

Team* createTeam(int teamID , const char* name){

    Team* team=(Team*)malloc(sizeof(Team));
    if(team==NULL){
        printf("Memory allocation fails.\n");
        exit(1);
    }
    team->teamID=teamID;
    team->teamName=name;
    team->playerCount=0;
    team->averageBattingStrikeRate=0;
    team->role[0]=NULL;
    team->role[1]=NULL;
    team->role[2]=NULL;

    return team;
}

void initilizeTeams(){
    for(int teamIndex = 0 ; teamIndex < teamCount ; teamIndex++){
        gTeams[teamIndex]=createTeam(teamIndex+1 , teams[teamIndex]);
    }
}

teamNode* createTeamNode(MyPlayer* player){
    teamNode* node=(teamNode*)malloc(sizeof(teamNode));
    node->player=player;
    node->next=NULL;
    return node;
}

void insertIntoTeamsList(MyPlayer* player){

    if(strcmp(player->player.team , "Afghanistan")==0){
        seperatingByRole(player , 1);
    }
    else if(strcmp(player->player.team , "Australia")==0){
        seperatingByRole(player ,2);
    }
    else if(strcmp(player->player.team , "Bangladesh")==0){
        seperatingByRole(player ,3);
    }
    else if(strcmp(player->player.team , "England")==0){
        seperatingByRole(player ,4);
    }
    else if(strcmp(player->player.team , "India")==0){
        seperatingByRole(player ,5);
    }
    else if(strcmp(player->player.team , "New Zealand")==0){
        seperatingByRole(player ,6);
    }
    else if(strcmp(player->player.team , "Pakistan")==0){
        seperatingByRole(player ,7);
    }
    else if(strcmp(player->player.team , "South Africa")==0){
        seperatingByRole(player ,8);
    }
    else if(strcmp(player->player.team , "Sri Lanka")==0){
        seperatingByRole(player ,9);
    }
    else if(strcmp(player->player.team , "West Indies")==0){
        seperatingByRole(player ,10);
    }

}

void seperatingByRole(MyPlayer* player, int teamID){

    gTeams[teamID-1]->playerCount++;

    if(strcmp( player->player.role, "Batsman")==0){
        addToTeam(  player , &(gTeams[teamID-1]->role[0]) );
    }else if(strcmp(player->player.role, "Bowler")==0){
        addToTeam( player , &(gTeams[teamID-1]->role[1]) );
    }else{
        addToTeam( player , &(gTeams[teamID-1]->role[2]) );
    }

    gTeams[teamID-1]->averageBattingStrikeRate = ( ( gTeams[teamID-1]->averageBattingStrikeRate * (gTeams[teamID-1]->playerCount -1) ) + player->player.strikeRate ) /  gTeams[teamID-1]->playerCount;
}

void addToTeam(MyPlayer* player , teamNode** head){

    teamNode* node= createTeamNode(player);

    if(*head==NULL){
        *head=node;
    }else{
        teamNode* prev=NULL;
        teamNode* curr= *head;

        while(curr!=NULL && curr->player->peformanceIndex > node->player->peformanceIndex ){
            prev=curr;
            curr=curr->next;
        }

        if(prev==NULL){
            node->next=*head;
            *head=node;
        }else{
            prev->next=node;
            node->next=curr;
        }
    }
}


void addPlayer(MyPlayer** head){
    int teamID;
    Player newPlayer;
    do{
        printf("Enter Team ID to add player:");
        scanf("%d",&teamID);
        if(teamID < 1 || teamID >10)
            printf("Enter a valid Team ID.\n");
    }while(teamID < 1 || teamID >10);

    switch(teamID){
        case 1:{
            newPlayer.team="Afghanistan";
            break;
        }
        case 2:{
            newPlayer.team="Australia";
            break;
        }
        case 3:{
            newPlayer.team="Bangladesh";
            break;
        }
        case 4:{
            newPlayer.team="England";
            break;
        }
        case 5:{
            newPlayer.team="India";
            break;
        }
        case 6:{
            newPlayer.team="New Zealand";
            break;
        }
        case 7:{
            newPlayer.team="Pakistan";
            break;
        }
        case 8:{
            newPlayer.team="South Africa";
            break;
        }
        case 9:{
            newPlayer.team="Sri Lanka";
            break;
        }
        case 10:{
            newPlayer.team="West Indies";
            break;
        }
    }

    printf("Enter Player Details:\n");
    do{
        printf("Player ID:");
        scanf("%d",&newPlayer.id);
        if(newPlayer.id<0)
            printf("Enter a ID greater than zero.\n");
    }while(newPlayer.id < 0);

    // while(getchar()!='\n');
    char* name=(char*)malloc(50);
    printf("Name:");
    scanf(" %[^\n]",name);
    newPlayer.name=name;

    int role;
    do{
        printf("Role (1-Batsman, 2-Bowler, 3-All-rounder):");
        scanf("%d",&role);
        if(role <1 || role>3)
            printf("Enter a Valid Role.\n");
    }while(role < 1 || role>3);

    if(role==1)
        newPlayer.role="Batsman";
    else if(role==2){
        newPlayer.role="Bowler";
    }else   
        newPlayer.role="All-rounder";

    do{
        printf("Total Runs:");
        scanf("%d",&newPlayer.totalRuns);
        if(newPlayer.totalRuns < 0)
            printf("Enter a Valid Runs.\n");
    }while(newPlayer.totalRuns<0);

    do{
        printf("Batting Average:");
        scanf("%f",&newPlayer.battingAverage);
        if(newPlayer.battingAverage < 0)
            printf("Enter a Valid batting Average.\n");
    }while(newPlayer.battingAverage<0);

    do{
        printf("Strike Rate:");
        scanf("%f",&newPlayer.strikeRate);
        if(newPlayer.strikeRate < 0)
            printf("Enter a Valid strike Rate.\n");
    }while(newPlayer.strikeRate<0);

    do{
        printf("Wickets:");
        scanf("%d",&newPlayer.wickets);
        if(newPlayer.wickets < 0)
            printf("Enter a Valid wickets.\n");
    }while(newPlayer.wickets<0);

    do{
        printf("Economy Rate:");
        scanf("%f",&newPlayer.economyRate);
        if(newPlayer.economyRate < 0)
            printf("Enter a Valid economy Rate.\n");
    }while(newPlayer.economyRate<0);


    MyPlayer* playerPtr=createPlayer(newPlayer);

    if(strcmp(newPlayer.role, "Batsman")==0){
        insertIntoList(  playerPtr  , (head+0));

    }else if(strcmp(newPlayer.role, "Bowler")==0){
        insertIntoList(   playerPtr , (head+1));
    }else{
        insertIntoList(  playerPtr , (head+2));
    }

    insertIntoTeamsList(playerPtr);
    printf("Player added successfully to Team %s\n",gTeams[teamID-1]->teamName);
}


void displayAllPlayersOfSpecificTeam(){
    int teamID;
    do{
        printf("Enter Team ID to Display player:");
        scanf("%d",&teamID);
        if(teamID < 0 || teamID >10)
            printf("Enter a valid Team ID.\n");
    }while(teamID < 0 || teamID >10);

    printf("Players Of Team %s\n",gTeams[teamID-1]->teamName);
    printf("================================================\n\n");
    printf("ID\tName\t\tRole\t\tRuns\tAvg\tSR\tWkts\tER\tperf.Index\n\n");
    printf("================================================\n\n");

    for(int i = 0 ; i < 3 ; i++){
        teamNode* temp = gTeams[teamID-1]->role[i];
        while(temp!=NULL){
            printf("%d\t%s\t\t%s\t\t%d\t%.1f\t%.1f\t%d\t%.1f\t%.2f\n",
                temp->player->player.id,
                temp->player->player.name,
                temp->player->player.role,
                temp->player->player.totalRuns,
                temp->player->player.battingAverage,
                temp->player->player.strikeRate,
                temp->player->player.wickets,
                temp->player->player.economyRate,
                temp->player->peformanceIndex);
            
            temp=temp->next;
        }
    }
     printf("================================================\n\n");
     printf("Total Players: %d\n",gTeams[teamID-1]->playerCount);
     printf("Average Batting Strike Rate: %.1f\n\n",gTeams[teamID-1]->averageBattingStrikeRate);
}

void displayTopPlayerOfSpecificTeam(){
    int teamID;
    do{
        printf("Enter Team ID to Display player:");
        scanf("%d",&teamID);
        if(teamID < 0 || teamID >10)
            printf("Enter a valid Team ID.\n");
    }while(teamID < 0 || teamID >10);

    int role;
    do{
        printf("Enter Role (1-Batsman, 2-Bowler, 3-All-rounder):");
        scanf("%d",&role);
        if(role <1 || role>3)
            printf("Enter a Valid Role.\n");
    }while(role < 1 || role>3);

    int k;
    printf("Enter number of players:");
    scanf("%d",&k);

    teamNode* temp=gTeams[teamID-1]->role[role-1];

    while(temp!=NULL && k>0){
    printf("%d\t%s\t\t%s\t\t%d\t%.1f\t%.1f\t%d\t%.1f\t%.2f\n",
            temp->player->player.id,
            temp->player->player.name,
            temp->player->player.role,
            temp->player->player.totalRuns,
            temp->player->player.battingAverage,
            temp->player->player.strikeRate,
            temp->player->player.wickets,
            temp->player->player.economyRate,
            temp->player->peformanceIndex);
            
        temp=temp->next;
        k--;
    }

}

void displayAllPlayersOfSpecificRole(MyPlayer** head){
    int role;
    do{
        printf("Enter Role (1-Batsman, 2-Bowler, 3-All-rounder):");
        scanf("%d",&role);
        if(role <1 || role>3)
            printf("Enter a Valid Role.\n");
    }while(role < 1 || role>3);

    MyPlayer* temp=NULL;
    if(role==1){
        temp= *(head+0);
    }else if(role==2)
        temp= *(head+1);
    else
        temp = *(head+2);

    while(temp!=NULL){
    printf("%d\t%s\t\t%s\t\t%d\t%.1f\t%.1f\t%d\t%.1f\t%.2f\n",
            temp->player.id,
            temp->player.name,
            temp->player.role,
            temp->player.totalRuns,
            temp->player.battingAverage,
            temp->player.strikeRate,
            temp->player.wickets,
            temp->player.economyRate,
            temp->peformanceIndex);
        if(temp!=NULL)  
            temp=temp->next;
    }
}

void sortTeams(int low , int high , Team** teamList){
    if(low<high){
        int mid = low + (high - low)/2;
        sortTeams(low , mid, &teamList[0]);
        sortTeams(mid + 1 , high , &teamList[0]);
        merge(low , mid , high , &teamList[0] );
    }
}

void merge(int low ,int mid , int high , Team** teamList){
    int n1=mid-low + 1;
    int n2=high - mid;
    printf("\n");
    Team** arr1=(Team**)malloc(sizeof(Team*)*n1);
    Team** arr2=(Team**)malloc(sizeof(Team*)*n2);

    for(int i = 0 ; i< n1 ;i++){
        arr1[i] = teamList[low+i];
    }

    for(int i = 0 ; i< n2 ;i++){
        arr2[i] = teamList[mid+i+1];
    }

    int i=0;
    int j =0;
    int k=low;

    while(i<n1 && j<n2){

        if( arr1[i]->averageBattingStrikeRate  >= arr2[j]->averageBattingStrikeRate){
           teamList[k] = arr1[i];
            i++;
        }else{
            teamList[k] = arr2[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        teamList[k] = arr1[i];
        i++;
        k++;
    }

    while(j<n2){
        teamList[k] = arr2[j];
        j++;
        k++;
    }
    free(arr1);
    free(arr2);
}

void printTeams(Team** teamList){

    printf("Teams Sorted by Average Batting Strike Rate.\n");
    printf("==========================================================================\n\n");
    printf("ID\tTeamName\t\tAvg Bat SR\t\tTotal Players\n");
    printf("==========================================================================\n\n");

    for(int i = 0 ; i< 10 ; i++){
        printf("%d\t%s\t\t%.1f\t%d\n",teamList[i]->teamID,teamList[i]->teamName,teamList[i]->averageBattingStrikeRate,teamList[i]->playerCount);
    }

}