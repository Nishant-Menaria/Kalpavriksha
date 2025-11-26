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
    if(myPlayer==NULL){
        printf("Memory alocation fails.\n");
        exit(1);
    }
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

    for(int teamIndex=0 ; teamIndex<teamCount ; teamIndex++){
        if(strcmp(player->player.team , teams[teamIndex])==0){
            seperatingByRole(player, teamIndex);
            break;
        }
    }
}

void seperatingByRole(MyPlayer* player, int teamID){

    gTeams[teamID]->playerCount++;

    if(strcmp( player->player.role, "Batsman")==0){
        addToTeam(  player , &(gTeams[teamID]->role[0]) );
    }else if(strcmp(player->player.role, "Bowler")==0){
        addToTeam( player , &(gTeams[teamID]->role[1]) );
    }else{
        addToTeam( player , &(gTeams[teamID]->role[2]) );
    }

    if(strcmp( player->player.role, "Batsman")==0 || strcmp( player->player.role, "All-rounder")==0)
        gTeams[teamID]->averageBattingStrikeRate = ( ( gTeams[teamID]->averageBattingStrikeRate * (gTeams[teamID]->playerCount -1) ) + player->player.strikeRate ) /  gTeams[teamID]->playerCount;
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

    for(int roleIndex = 0 ; roleIndex < 3 ; roleIndex++){
        teamNode* temp = gTeams[teamID-1]->role[roleIndex];
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

    int numberOfPlayers;
    printf("Enter number of players:");
    scanf("%d",&numberOfPlayers);

    teamNode* temp=gTeams[teamID-1]->role[role-1];

    while(temp!=NULL && numberOfPlayers>0){
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
        numberOfPlayers--;
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
    int sizeOfFirstHalf=mid-low + 1;
    int sizeOfSecondHalf=high - mid;
    Team** arr1=(Team**)malloc(sizeof(Team*)*sizeOfFirstHalf);
    Team** arr2=(Team**)malloc(sizeof(Team*)*sizeOfSecondHalf);

    for(int index = 0 ; index< sizeOfFirstHalf ;index++){
        arr1[index] = teamList[low+index];
    }

    for(int index = 0 ; index< sizeOfSecondHalf ;index++){
        arr2[index] = teamList[mid+index+1];
    }

    int arr1Index=0;
    int arr2Index =0;
    int mergeArrayIndex=low;

    while(arr1Index<sizeOfFirstHalf && arr2Index<sizeOfSecondHalf){

        if( arr1[arr1Index]->averageBattingStrikeRate  >= arr2[arr2Index]->averageBattingStrikeRate){
           teamList[mergeArrayIndex] = arr1[arr1Index];
            arr1Index++;
        }else{
            teamList[mergeArrayIndex] = arr2[arr2Index];
            arr2Index++;
        }
        mergeArrayIndex++;
    }

    while(arr1Index<sizeOfFirstHalf){
        teamList[mergeArrayIndex] = arr1[arr1Index];
        arr1Index++;
        mergeArrayIndex++;
    }

    while(arr2Index<sizeOfSecondHalf){
        teamList[mergeArrayIndex] = arr2[arr2Index];
        arr2Index++;
        mergeArrayIndex++;
    }
    free(arr1);
    free(arr2);
}

void printTeams(Team** teamList){

    printf("Teams Sorted by Average Batting Strike Rate.\n");
    printf("==========================================================================\n\n");
    printf("ID\tTeamName\t\tAvg Bat SR\t\tTotal Players\n");
    printf("==========================================================================\n\n");

    for(int teamIndex = 0 ; teamIndex< 10 ; teamIndex++){
        printf("%d\t%s\t\t%.1f\t%d\n",teamList[teamIndex]->teamID,teamList[teamIndex]->teamName,teamList[teamIndex]->averageBattingStrikeRate,teamList[teamIndex]->playerCount);
    }
}