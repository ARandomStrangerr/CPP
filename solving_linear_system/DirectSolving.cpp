#import <iostream>

class DirectSolving;

class DirectSolving{
private:
    void swapRow(long*, int, int);
public:
    DirectSolving();
    void gaussianElimination(long*, int);
    void partialPivot(long*, int);

};
DirectSolving::DirectSolving(){}
void DirectSolving::gaussianElimination(long* matrix, int dimention){
    for(int row = 0; row < dimention; row++){ // pivot row, from top to bottom ~ n iteration
        // insert row swapping here if pivot column is 0
        for(int reduceRow = row + 1; reduceRow < dimention; reduceRow++){ // reduce row, from pivot row + 1 to bottom ~ n * (n - 1) / 2 iteration
            int coef = matrix[reduceRow * dimention + row] / matrix[row * dimention + row];
            for(int col = row; col < dimention; col++){ // reduce cell, from pivot column to right
                matrix[reduceRow * dimention + col] -= coef * matrix[row * dimention + col];
            }
        }
    }
}

void DirectSolving::swapRow(long* matrix, int dimention, int r1, int r2){
    for (int col = 0; col < dimention){
        long temp = matrix[r1 * dimention + col];
        matrix[r1 * dimention + col] = matrix[r2 * dimention + col];
        matrix[r2 * dimention + col] = temp;
    }
}

void printMatrix(long* arr, int dimention){
    for(int i = 0; i < dimention; i++){
        for (int j = 0; j < dimention; j++){
            std::cout << arr[i * dimention + j] << " ";
        }
        std::cout << "\n";
    }
}
int main(int argc, char const *argv[]) {
    DirectSolving matrixSolver;
    long* matrix = new long[9];
    for (int i = 0; i < 9; i++){
        matrix[i] = i+1;
    }
    matrixSolver.gaussianElimination(matrix, 3);
    printMatrix(matrix, 3);
    return 0;
}
