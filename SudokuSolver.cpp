#include <iostream>
#include <vector>

using namespace std;

const int N = 9;

class SudokuSolver {
private:
    int grid[N][N];

    // Check if it's safe to place a number in a specific cell
    bool isSafe(int row, int col, int num) {
        // Check row and column
        for (int x = 0; x < N; x++) {
            if (grid[row][x] == num || grid[x][col] == num) {
                return false;
            }
        }

        // Check 3x3 subgrid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    // Recursive backtracking function to solve the puzzle
    bool solveSudokuRec(int row, int col) {
        // Reached end of grid
        if (row == N - 1 && col == N) {
            return true;
        }

        // Move to next row if column reaches N
        if (col == N) {
            row++;
            col = 0;
        }

        // Skip cells that already have numbers
        if (grid[row][col] != 0) {
            return solveSudokuRec(row, col + 1);
        }

        // Try numbers from 1 to 9
        for (int num = 1; num <= 9; num++) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;

                if (solveSudokuRec(row, col + 1)) {
                    return true;
                }

                // Backtrack if it doesn't lead to a solution
                grid[row][col] = 0;
            }
        }

        return false;
    }

public:
    SudokuSolver(int inputGrid[N][N]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = inputGrid[i][j];
            }
        }
    }

    void solve() {
        if (solveSudokuRec(0, 0)) {
            cout << "\nSudoku Solved Successfully!\n";
            printGrid();
        } else {
            cout << "\nNo solution exists for the given Sudoku puzzle.\n";
        }
    }

    void printGrid() {
        cout << "-----------------------------------" << endl;
        for (int r = 0; r < N; r++) {
            for (int d = 0; d < N; d++) {
                cout << grid[r][d] << " ";
                if ((d + 1) % 3 == 0 && d < 8) cout << "| ";
            }
            cout << endl;
            if ((r + 1) % 3 == 0 && r < 8) {
                cout << "-----------------------------------" << endl;
            }
        }
        cout << "-----------------------------------" << endl;
    }
};

int main() {
    // Sample Sudoku puzzle (0 represents empty cells)
    int sampleGrid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "=== CodeAlpha C++ Task 3: Sudoku Solver ===" << endl;
    cout << "\nInitial Unsolved Sudoku Grid:" << endl;
    
    SudokuSolver solver(sampleGrid);
    solver.printGrid();

    // Solve using backtracking algorithm
    solver.solve();

    return 0;
}