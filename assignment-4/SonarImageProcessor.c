#include <stdio.h>
#include <stdlib.h>

void generateRandomValues(int ***matrix, int matrixSize);
void printMatrix(int ***matrix, int matrixSize);
void rotateMatrix(int ***matrix, int matrixSize);
void smoothingFilter(int ***matrix , int matrixSize);

int main()
{
    int matrixSize;
    do
    {
        scanf("%d", &matrixSize);
        if (matrixSize < 2 || matrixSize > 10)
        {
            printf("Please Enter Matrix Size Between 2-10\n");
        }
    } while (matrixSize < 2 || matrixSize > 10);

    int ***matrix = (int ***)malloc(sizeof(int **) * matrixSize);
    if (matrix == NULL)
    {
        printf("Memory allocation fail for row \n");
        exit(1);
    }
    for (int row = 0; row < matrixSize; row++)
    {
        matrix[row] = (int **)malloc(sizeof(int *) * matrixSize);
        if (matrix[row] == NULL)
        {
            printf("Memory allocation fail for column\n");
            exit(1);
        }
    }

    for (int row = 0; row < matrixSize; row++)
    {
        for (int column = 0; column < matrixSize; column++)
        {
            matrix[row][column] = (int *)malloc(sizeof(int));
            if (matrix[row][column] == NULL)
            {
                printf("Memory allocation to individual element fail\n");
                exit(1);
            }
        }
    }

    generateRandomValues(matrix, matrixSize);
    printMatrix(matrix, matrixSize);
    printf("______________________________\n\n");
    rotateMatrix(matrix, matrixSize);
    printMatrix(matrix , matrixSize);
    printf("______________________________\n\n");
    smoothingFilter(matrix ,matrixSize);

    printMatrix(matrix, matrixSize);
}

void generateRandomValues(int ***matrix, int matrixSize)
{
    for (int row = 0; row < matrixSize; row++)
    {
        for (int column = 0; column < matrixSize; column++)
        {
            *(matrix[row][column]) = rand() % 256;
        }
    }
}

void printMatrix(int ***matrix, int matrixSize)
{
    for (int row = 0; row < matrixSize; row++)
    {
        for (int column = 0; column < matrixSize; column++)
        {
            printf("%d\t", *(matrix[row][column]));
        }
        printf("\n");
    }
}

void rotateMatrix(int ***matrix, int matrixSize)
{

    for (int row = 0; row < matrixSize; row++)
    {
        for (int column = row; column < matrixSize; column++)
        {
            int *tmp = *(*(matrix + row) + column);
            *(*(matrix + row) + column) = *(*(matrix + column) + row);
            *(*(matrix + column) + row) = tmp;
        }
    }

    for (int row = 0; row < matrixSize; row++)
    {
        for (int low = 0, high = matrixSize - 1; low < high; low++, high--)
        {
            int *tmp = *(*(matrix + row) + low);
            *(*(matrix + row) + low) = *(*(matrix + row) + high);
            *(*(matrix + row) + high) = tmp;
        }
    }
}

void smoothingFilter(int ***matrix , int matrixSize){

    int copyMatrix[matrixSize][matrixSize];

    for(int rowIndex = 0 ; rowIndex<matrixSize ; rowIndex++){
        for(int columnIndex=0 ; columnIndex<matrixSize ; columnIndex++){
          copyMatrix[rowIndex][columnIndex] = *(matrix[rowIndex][columnIndex]);  
        }
    }

    for(int rowIndex = 0 ; rowIndex < matrixSize ; rowIndex++){
        for(int columnIndex = 0 ; columnIndex < matrixSize ; columnIndex++){

            int averageSum = copyMatrix[rowIndex][columnIndex];
            int divideCount=1;

            //Top
            if(rowIndex>0){
                averageSum+=copyMatrix[rowIndex-1][columnIndex];
                divideCount++;
            }

            //Bottom
            if(rowIndex < matrixSize-1){
                averageSum+=copyMatrix[rowIndex+1][columnIndex];
                divideCount++;
            }

            //right
            if(columnIndex < matrixSize-1){
                averageSum+=copyMatrix[rowIndex][columnIndex+1];
                divideCount++;
            }

            //left
            if(columnIndex>0){
                averageSum+=copyMatrix[rowIndex][columnIndex-1];
                divideCount++;
            }

            //top-Left
            if(rowIndex>0 && columnIndex>0){
                averageSum+=copyMatrix[rowIndex-1][columnIndex-1];
                divideCount++;
            }

            //top-right
            if(rowIndex>0 && columnIndex<matrixSize-1){
                averageSum+=copyMatrix[rowIndex-1][columnIndex+1];
                divideCount++;
            }

            //Bottom-left
            if(rowIndex<matrixSize-1 && columnIndex>0){
                averageSum+=copyMatrix[rowIndex+1][columnIndex-1];
                divideCount++;
            }

            //Bottom-right
            if(rowIndex<matrixSize-1 && columnIndex<matrixSize-1){
                averageSum+=copyMatrix[rowIndex+1][columnIndex+1];
                divideCount++;
            }
            *(matrix[rowIndex][columnIndex])=(int)averageSum/divideCount;
        }
    }
}