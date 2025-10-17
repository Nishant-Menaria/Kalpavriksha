#include <stdio.h>

typedef struct Student
{
    int rollNumber;
    char name[20];
    float physics;
    float mathematics;
    float chemistry;
} Student;

void quickSort(Student *students, int lowIndex, int highIndex);
int partation(Student *students, int lowIndex, int highIndex);
int calculatingTotalMarks(Student student);
void printRollNumber(Student *students, int studentCount, int currentStudent);

int main()
{
    int studentCount;
    scanf("%d", &studentCount);

    Student students[studentCount];

    int studentIndex = 0;
    while (studentIndex < studentCount)
    {
        if (scanf("%d %s %f %f %f", &students[studentIndex].rollNumber,
                  &students[studentIndex].name,
                  &students[studentIndex].physics,
                  &students[studentIndex].mathematics,
                  &students[studentIndex].chemistry) != 5)
        {

            printf("Please Enter , Valid Roll Number , Name and Marks\n");
            while(getchar()!='\n');
            continue;
        }

        if (students[studentIndex].rollNumber <= 0)
        {
            printf("Please Enter a Valid Roll Number\n");
            continue;
        }

        if ( (students[studentIndex].chemistry < 0 || students[studentIndex].chemistry >100 )  || (students[studentIndex].physics < 0 || students[studentIndex].physics >100 ) || (students[studentIndex].chemistry < 0 || students[studentIndex].physics >100 ))
        {
            printf("Please Enter marks in valid range(0-100)\n");
            continue;
        }

        studentIndex++;
    }

    quickSort(students, 0, studentCount - 1);

    for (int studentIndex = 0; studentIndex < studentCount; studentIndex++)
    {
        printf("\nRoll Number: %d\n", students[studentIndex].rollNumber);
        printf("Name: %s\n", students[studentIndex].name);
        int totalMarks = calculatingTotalMarks(students[studentIndex]);
        float averageMarks = totalMarks / 3;

        printf("Total: %d\n", totalMarks);
        printf("Average: %.2f\n", averageMarks);

        if (averageMarks >= 85)
        {
            printf("Grade: A\n");
            printf("Peformance: *****\n");
        }
        else if (averageMarks >= 70)
        {
            printf("Grade: B\n");
            printf("Peformance: ****\n");
        }
        else if (averageMarks >= 50)
        {
            printf("Grade: C\n");
            printf("Peformance: ***\n");
        }
        else if (averageMarks >= 35)
        {
            printf("Grade: D\n");
            printf("Peformance: **\n");
        }
        else
        {
            printf("Grade: F\n");
        }

        printf("\n");
    }

    printRollNumber(students, studentCount, 0);

    return 0;
}

int partation(Student *students, int lowIndex, int highIndex)
{
    int pivot = highIndex;
    int elementSmallerThanPivot = -1;

    Student tmp;

    for (int studentIndex = 0; studentIndex < highIndex; studentIndex++)
    {
        if (students[studentIndex].rollNumber < students[pivot].rollNumber)
        {
            elementSmallerThanPivot++;
            tmp = students[studentIndex];
            students[studentIndex] = students[elementSmallerThanPivot];
            students[elementSmallerThanPivot] = tmp;
        }
    }

    elementSmallerThanPivot++;
    tmp = students[pivot];
    students[pivot] = students[elementSmallerThanPivot];
    students[elementSmallerThanPivot] = tmp;

    return elementSmallerThanPivot;
}

void quickSort(Student *students, int lowIndex, int highIndex)
{
    if (lowIndex < highIndex)
    {
        int pivot = partation(students, lowIndex, highIndex);

        quickSort(students, lowIndex, pivot - 1);
        quickSort(students, pivot + 1, highIndex);
    }
}

int calculatingTotalMarks(Student student)
{
    return student.physics + student.mathematics + student.chemistry;
}

void printRollNumber(Student *students, int studentCount, int currentStudent)
{
    if (currentStudent == studentCount)
        return;

    printf("%d\t", students[currentStudent].rollNumber);
    printRollNumber(students, studentCount, currentStudent + 1);
}