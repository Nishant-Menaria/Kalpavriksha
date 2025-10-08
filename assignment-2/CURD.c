#include<stdio.h>

void addUser();
void readFile();
void modifyUser();
void removeUser();

int main(){
    int choice;

    do{
        printf("Enter Your Choice :\n 1 for Add a user \n 2 for Read The Entire File \n 3 for Modiefy a User \n 4 for Remove a User \n 5 for exit \n choice : ");
        scanf("%d",&choice);
        printf("_________________________________________________\n");
        switch(choice){
            case 1:{
                addUser();
                continue;
            }
            case 2:{
                readFile();
                continue;
            }
            case 3:{
                modifyUser();
                continue;
            }
            case 4:{
                removeUser();
                continue;
            }

            default:
                break;
        }
    }while(choice!=5);
    return 0;
}

void addUser(){

    FILE* fp=fopen("users.txt","a+");
    int ID;
    char name[20];
    int age;
    printf("Enter The ID : ");
    scanf("%d",&ID);
    printf("Enter The Age : ");
    scanf("%d",&age);
    while (getchar() != '\n');  
    printf("Enter The Name : ");
    fgets(name,sizeof(name),stdin);
    fprintf(fp,"%d %d %s",ID,age,name);
    fclose(fp);
    printf("_________________________________________________");
}

void readFile(){

    FILE* fp=fopen("users.txt","r");
    char line[100];

    while(fgets(line,sizeof(line),fp)){
        printf("%s",line);
    }
    printf("_________________________________________________\n");
    fclose(fp);
}

void modifyUser(){

    FILE* fp=fopen("users.txt","r");
    FILE* tmp=fopen("temp.txt","a+");
    int ID,age,searchID;
    char name[20],line[40];
    printf("Enter The ID :");
    scanf("%d",&searchID);
    int flag=0;

    while(fgets(line,sizeof(line),fp)){
        sscanf(line,"%d %d %[^\n]",&ID,&age,name);
        if(ID==searchID){
            printf("Please enter the Updated Details :\n");
            while (getchar() != '\n');
            printf("Name:");
            fgets(name,sizeof(name),stdin);
            printf("Age:");
            scanf("%d",&age);
            fprintf(tmp,"%d %d %s",ID,age,name);
            flag=1;
        }else{
            fprintf(tmp,"%s",line);
        }
    }

    if(flag)
        printf("User Updated Successfully\n");
    else 
        printf("User not Found\n");

    remove("users.txt");
    rename("temp.txt","users.txt");
    printf("_________________________________________________");
    fclose(fp);
    fclose(tmp);
}

void removeUser(){
    FILE* fp=fopen("users.txt","r");
    FILE* tmp=fopen("tmp.txt","a+");

    int searchID,ID,flag=0;
    char line[50];
    printf("Enter the ID of User You want to Remove :");
    scanf("%d",&searchID);

     while(fgets(line,sizeof(line),fp)){
        sscanf(line,"%d",&ID);
        if(ID==searchID){
            flag=1;
            continue;
        }else{
            fprintf(tmp,"%s",line);
        }
    }

    if(flag)
        printf("User removed Successfully\n");
    else 
        printf("User not Found\n");

    remove("users.txt");
    rename("tmp.txt","users.txt");

    printf("_________________________________________________");
    fclose(fp);
    fclose(tmp);
}