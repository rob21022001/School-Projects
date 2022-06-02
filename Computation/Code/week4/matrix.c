#include <stdio.h>
#include <string.h>
#define MAXSIZE 10

void print (float matrix[MAXSIZE][MAXSIZE], int rows, int columns, char name){
    printf("Matrix %c (%d X %d):\n", name ,rows, columns);
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < columns; x++){
            printf("%7.3f", matrix[y][x]);
        }
        printf("\n");
    }
}

void mult (
float matrixA[MAXSIZE][MAXSIZE], int rowsA, int columnsA,
float matrixB[MAXSIZE][MAXSIZE], int rowsB, int columnsB,
float matrixC[MAXSIZE][MAXSIZE], int rowsC, int columnsC) {
    printf("%d%d", rowsC, columnsC);
    int value;
    for(int k = 0; k < rowsA; k++){
        for(int j = 0; j < columnsB; j++){
            value = 0;
            for(int i = 0; i < columnsA; i++){
                value = value +matrixA[k][i] * matrixB[i][j];
                matrixC[k][j] = value;
            }
        }
    }
}

int main (void){
    float MatrixA[MAXSIZE][MAXSIZE] = {{0}};
    float MatrixB[MAXSIZE][MAXSIZE] = {{0}};
    float MatrixC[MAXSIZE][MAXSIZE] = {{0}};
    float MatrixT[MAXSIZE][MAXSIZE] = {{0}};
    char cmd;
    
    int rowsA = 1, rowsB = 1, rowsC = 1;
    int columnsA = 1, columnsB = 1, columnsC = 1;
    int rowsT = 1;
    int columnsT = 1;
    int y, x;
    do{
        printf("Command [qIabcAB+t*md]? ");
        scanf(" %c", &cmd);
        switch(cmd){
            case '*':
                rowsC = rowsA;
                columnsC = columnsB;
                mult(MatrixA, rowsA, columnsA, MatrixB, rowsB, columnsB, MatrixC, rowsC, columnsC);
            break;
            case 'q':
                printf("Bye!\n");
            break;
            case 't':
                for(y = 0; y < MAXSIZE; y++){
                    for(x = 0; x < MAXSIZE; x++){
                        MatrixT[x][y] = MatrixA[y][x];
                    }
                }
                for(y = 0; y < MAXSIZE; y++){
                    for(x = 0; x < MAXSIZE; x++){
                        MatrixA[y][x] = MatrixT[y][x];
                    }
                }
                rowsT = rowsA;
                columnsT = columnsA;
                rowsA = columnsT;
                columnsA = rowsT;
            break;
            case '+':
                if (rowsA == rowsB && columnsA == columnsB){
                    rowsC = rowsA;
                    columnsC = columnsA;
                    for(y = 0; y < MAXSIZE; y++){
                        for(x = 0; x < MAXSIZE; x++){
                            MatrixC[y][x] = MatrixA[y][x] + MatrixB[y][x];
                        }
                    }
                }
                else{
                    printf("Dimensions of A & B do not match\n");
                }
            break;
            case 'A':
                printf("Size of matrix A (rows columns)? ");
                scanf("%d %d", &rowsT, &columnsT);
                if(rowsT < 1 || rowsT > 10 || columnsT > 10 || columnsT < 1){
                    printf("Rows & columns must be between 1 and 10\n");
                }
                else{
                    rowsA = rowsT;
                    columnsA = columnsT;
                    for(y = 0; y < rowsA; y++){
                        printf("row%2d ", y);
                        for( x = 0; x < columnsA; x++){
                            scanf(" %f", &MatrixA[y][x]);
                        }
                    }
                }

            break;
            case 'b':
                print(MatrixB, rowsB, columnsB, 'B');
            break;
            case 'c':
                print(MatrixC, rowsC, columnsC, 'C');
            break;
            case 'B':
                rowsB = rowsA;
                columnsB = columnsA;
                 for(y = 0; y < MAXSIZE; y++){
                    for(x = 0; x < MAXSIZE; x++){
                        MatrixB[y][x] = MatrixA[y][x];
                    }
                 }
            break;
            case 'I':
                printf("Size of matrix A (rows columns)? ");
                scanf("%d %d", &rowsT, &columnsT);
                if(rowsT != columnsT || rowsT < 1 || rowsT > 10){
                    printf("Rows & columns must be equal and between 1 and 10\n");
                }
                else{
                    rowsA = rowsT;
                    columnsA = columnsT;
                    for(int i = 0; i < MAXSIZE; i++){
                        for(int j = 0; j < MAXSIZE; j++){
                            MatrixA[i][j] = 0;
                        }
                    }
                    for( x = 0; x < rowsA; x++){
                        MatrixA[x][x] = 1.000;
                        rowsA = rowsT;
                        columnsA = columnsT;
                    }
                }
            break;
            case 'a':
                print(MatrixA, rowsA, columnsA, 'A');
            break;
            default:
                printf("Invalid command! \'%c\'\n", cmd);
            break;
    
        
        }
    
    }while(cmd != 'q');
}
