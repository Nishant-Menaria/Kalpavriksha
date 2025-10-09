#include<stdio.h>

typedef struct Student{
    int rollNumber;
    char name[20];
    int physics;
    int mathematics;
    int chemistry;
}Student;


void quickSort(Student *students , int lowIndex , int highIndex);
int partation(Student *students , int lowIndex , int highIndex);


int main(){
    int studentCount;
    scanf("%d",&studentCount);

    Student students[studentCount];

    for(int studentIndex=0 ; studentIndex<studentCount ; studentIndex++)
    {
        scanf("%d %s %d %d %d",&students[studentIndex].rollNumber,
                               &students[studentIndex].name,
                               &students[studentIndex].physics,
                               &students[studentIndex].mathematics,
                               &students[studentIndex].chemistry);
    }

    quickSort(students , 0 , studentCount-1);

    for(int studentIndex=0 ; studentIndex<studentCount ; studentIndex++)
    {
        printf("\nRoll Number: %d\n",students[studentIndex].rollNumber);
        printf("Name: %s\n",students[studentIndex].name);
        int totalMarks=students[studentIndex].physics + students[studentIndex].mathematics
                         + students[studentIndex].chemistry ;
        float averageMarks= totalMarks / 3;

        printf("Total: %d\n",totalMarks);
        printf("Average: %.2f\n",averageMarks );

        if(averageMarks >= 85){
            printf("Grade: A\n");
            printf("Peformance: *****\n");
        }else if(averageMarks >= 70){
            printf("Grade: B\n");
            printf("Peformance: ****\n");
        }else if(averageMarks >= 50){
            printf("Grade: c\n");
            printf("Peformance: ***\n");
        }else if(averageMarks >= 35){
            printf("Grade: D\n");
            printf("Peformance: **\n");
        }else{
            printf("Grade: F\n");
        }

        printf("\n");
    }

    for(int studentIndex=0 ; studentIndex < studentCount ; studentIndex++){
        printf("%d\t",students[studentIndex].rollNumber);
    }

    return 0;
}

int partation(Student *students , int lowIndex , int highIndex){
    int pivot=highIndex;
    int elementSmallerThanPivot=-1;

    Student tmp;

    for(int studentIndex=0 ; studentIndex < highIndex ; studentIndex++){
        if(students[studentIndex].rollNumber < students[pivot].rollNumber){
            elementSmallerThanPivot++;
            tmp=students[studentIndex];
            students[studentIndex]=students[elementSmallerThanPivot];
            students[elementSmallerThanPivot]=tmp;
        }
    }

    elementSmallerThanPivot++;
    tmp=students[pivot];
    students[pivot]=students[elementSmallerThanPivot];
    students[elementSmallerThanPivot]=tmp;

    return elementSmallerThanPivot;
}


void quickSort(Student *students , int lowIndex , int highIndex){
    if(lowIndex<highIndex){
        int pivot=partation(students,lowIndex,highIndex);

        quickSort(students , lowIndex , pivot-1);
        quickSort(students , pivot+1 , highIndex);
    }
}