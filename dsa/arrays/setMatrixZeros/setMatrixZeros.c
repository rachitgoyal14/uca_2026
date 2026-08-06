#include <stdio.h>

void setZeroesI(int *matrix, int numRows, int numCols);
void setZeroesII(int *matrix, int numRows, int numCols);

void setZeroesI(int *matrix, int numRows, int numCols) {
    int rowsTracker[numRows];
    int colsTracker[numCols];

    // initialize tracker arrays to 0
    for (int i = 0; i < numRows; i++)
        rowsTracker[i] = 0;

    for (int i = 0; i < numCols; i++)
        colsTracker[i] = 0;

    // first pass => record which rows and columns contain a zero
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (matrix[i * numCols + j] == 0) {
                rowsTracker[i] = 1;
                colsTracker[j] = 1;
            }
        }
    }

    // Second pass: set required cells to zero
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (rowsTracker[i] == 1 || colsTracker[j] == 1) {
                matrix[i * numCols + j] = 0;
            }
        }
    }
}

void setZeroesII(int *matrix, int numRows, int numCols) {

    int firstRowZero = 0;
    int firstColumnZero = 0;

    // check first row
    for (int j = 0; j < numCols; j++) {
        if (matrix[j] == 0) {
            firstRowZero = 1;
            break;
        }
    }

    // check first column
    for (int i = 0; i < numRows; i++) {
        if (matrix[i * numCols] == 0) {
            firstColumnZero = 1;
            break;
        }
    }


    // iterate the entire matrix once to alot the values in the trackers
    // trackers? => first row and first column in this case

    for (int i = 1; i < numRows; i++) {
        for (int j = 1; j < numCols; j++) {
            if (matrix[i * numCols + j] == 0) {
                matrix[i * numCols] = 0;
                matrix[j] = 0;
            }
        }
    }

    // reiterate over the rows and allot zero
    for (int i = 1; i < numRows; i++) {
        for (int j = 1; j < numCols; j++) {
            if (matrix[i * numCols] == 0)
                matrix[i * numCols + j] = 0;
        }
    }

    // reiterate over the columns and allot zero        
    for (int i = 1; i < numRows; i++) {
        for (int j = 1; j < numCols; j++) {
            if (matrix[j] == 0)
                matrix[i * numCols + j] = 0;
        }
    }

    // handle first row zero cases
    if (firstRowZero) {
        for (int i = 0; i < numCols; i++) {
            matrix[i] = 0;
        }
    }

    // handle first column zero cases
    if (firstColumnZero) {
        for (int i = 0; i < numRows; i++) {
            matrix[i * numCols] = 0;
        }
    }

}


void printMatrix(int *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

int main() {
    int rows = 3, cols = 4;

    int sample[3][4] = {
        {1, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1}
    };

    int matrix[12];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] = sample[i][j];
        }
    }

    printf("Original matrix:\n");
    printMatrix(matrix, rows, cols);

    setZeroesII(matrix, rows, cols);

    printf("\nAfter setZeroes:\n");
    printMatrix(matrix, rows, cols);

    return 0;
}