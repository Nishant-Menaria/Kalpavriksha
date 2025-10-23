#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void generateRandomValues(int **matrix, int matrixSize);
void printMatrix(int **matrix, int matrixSize);
void rotateMatrix(int **matrix, int matrixSize);
void smoothingFilter(int **matrix , int matrixSize);

int main()
{
    int matrixSize;
    printf("Enter Matrix Size (2-10) :");
    do
    {
        if(scanf("%d", &matrixSize) != 1){
            printf("matrix size input fails\n");
            exit(1);
        }
        if (matrixSize < 2 || matrixSize > 10)
        {
            printf("Please Enter Matrix Size Between 2-10\n");
        }
    } while (matrixSize < 2 || matrixSize > 10);

    int **matrix = (int **)malloc(sizeof(int *) * matrixSize);
    if (matrix == NULL)
    {
        printf("Memory allocation fail for row \n");
        exit(1);
    }
    for (int row = 0; row < matrixSize; row++)
    {
        *(matrix + row ) = (int *)malloc(sizeof(int) * matrixSize);
        if ( *(matrix + row) == NULL)
        {
            printf("Memory allocation fail for column\n");
            exit(1);
        }
    }

    generateRandomValues(matrix, matrixSize);
    printf("Original Randomly Generated Matrix:\n");
    printMatrix(matrix, matrixSize);
    printf("______________________________\n\n");
    rotateMatrix(matrix, matrixSize);
    printf("Matrix after 90 degree rotation \n");
    printMatrix(matrix , matrixSize);
    printf("______________________________\n\n");
    smoothingFilter(matrix ,matrixSize);
    printf("Matrix after Applying 3×3 Smoothing Filter:\n");
    printMatrix(matrix, matrixSize);
}

void generateRandomValues(int **matrix, int matrixSize)
{
    srand(time(0));
    for (int row = 0; row < matrixSize; row++)
    {
        for (int column = 0; column < matrixSize; column++)
        {
            *(*(matrix+row) + column )= rand() % 256;
        }
    }
}

void printMatrix(int **matrix, int matrixSize)
{
    for (int row = 0; row < matrixSize; row++)
    {
        for (int column = 0; column < matrixSize; column++)
        {
            printf("%d\t", *(*(matrix + row) + column));
        }
        printf("\n");
    }
}

void rotateMatrix(int **matrix, int matrixSize)
{

    for (int row = 0; row < matrixSize; row++)
    {
        for (int column = row; column < matrixSize; column++)
        {
            int tmp = *(*(matrix + row) + column);
            *(*(matrix + row) + column) = *(*(matrix + column) + row);
            *(*(matrix + column) + row) = tmp;
        }
    }

    for (int row = 0; row < matrixSize; row++)
    {
        for (int low = 0, high = matrixSize - 1; low < high; low++, high--)
        {
            int tmp = *(*(matrix + row) + low);
            *(*(matrix + row) + low) = *(*(matrix + row) + high);
            *(*(matrix + row) + high) = tmp;
        }
    }
}

void smoothingFilter(int **matrix , int matrixSize){

    for(int rowIndex = 0 ; rowIndex < matrixSize ; rowIndex++){
        for(int columnIndex = 0 ; columnIndex < matrixSize ; columnIndex++){

            int lower16 = *(*(matrix+rowIndex) + columnIndex) & 0xFFFF;

            int averageSum = lower16;
            int divideCount=1;

            //Top
            if(rowIndex>0){
                averageSum+= *(*(matrix + rowIndex - 1) + columnIndex) & 0xFFFF;
                divideCount++;
            }

            //Bottom
            if(rowIndex < matrixSize-1){
                averageSum+=*(*(matrix + rowIndex + 1) + columnIndex) & 0xFFFF;
                divideCount++;
            }

            //right
            if(columnIndex < matrixSize-1){
                averageSum+= *(*(matrix + rowIndex) + columnIndex + 1) & 0xFFFF;
                divideCount++;
            }

            //left
            if(columnIndex>0){
                averageSum+= *(*(matrix + rowIndex) + columnIndex - 1) & 0xFFFF;
                divideCount++;
            }

            //top-Left
            if(rowIndex>0 && columnIndex>0){
                averageSum+= *(*(matrix + rowIndex - 1) + columnIndex - 1) & 0xFFFF;
                divideCount++;
            }

            //top-right
            if(rowIndex>0 && columnIndex<matrixSize-1){
                averageSum+= *(*(matrix + rowIndex - 1) + columnIndex + 1) & 0xFFFF;
                divideCount++;
            }

            //Bottom-left
            if(rowIndex<matrixSize-1 && columnIndex>0){
                averageSum+= *(*(matrix + rowIndex + 1) + columnIndex - 1) & 0xFFFF;
                divideCount++;
            }

            //Bottom-right
            if(rowIndex<matrixSize-1 && columnIndex<matrixSize-1){
                averageSum+= *(*(matrix + rowIndex + 1) + columnIndex + 1) & 0xFFFF;
                divideCount++;
            }

            averageSum=averageSum/divideCount;

            *(*(matrix + rowIndex) + columnIndex) = ( *(*(matrix + rowIndex) + columnIndex) & 0x0000FFFF) | ((int32_t)(averageSum) << 16); 
        }
    }

    for(int rowIndex = 0 ; rowIndex < matrixSize ; rowIndex++){
        for(int columnIndex = 0 ; columnIndex < matrixSize ; columnIndex++){
            *(*(matrix + rowIndex) + columnIndex) = *(*(matrix + rowIndex) + columnIndex) >> 16;
        }
    }
}