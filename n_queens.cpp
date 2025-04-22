#include <iostream>
#include <iomanip> // for setw to format output
using namespace std;

#define N 5

// Function to check if it's safe to place a queen at board[row][col]
bool isSafe(int board[N][N], int row, int col)
{
    // Check all rows above the current row in the same column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    // If all checks pass, it's safe to place the queen
    return true;
}

// Recursive function to solve the N-Queens problem
bool solveNQueens(int board[N][N], int row)
{
    // Base case: all queens are placed
    if (row >= N)
        return true;

    // Try placing a queen in each column of the current row
    for (int col = 0; col < N; col++)
    {
        if (isSafe(board, row, col))
        {
            board[row][col] = row + 1; // Place queen with a label (Q1, Q2, etc.)

            // Recur to place the rest of the queens
            if (solveNQueens(board, row + 1))
                return true;

            board[row][col] = 0; // Backtrack if placing queen here doesn't work
        }
    }
    return false; // No valid position found in this row
}

// Function to print the board with Q1, Q2, ... and '.' for empty cells
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 0)
                cout << setw(3) << '.'; // Print dot for empty cell
            else
                cout << " Q" << board[i][j]; // Label queen as Q1, Q2, etc.
        }
        cout << endl;
    }
}

int main()
{
    int board[N][N] = {0}; // Initialize board with 0s

    if (solveNQueens(board, 0))
        printSolution(board); // Print one valid solution
    else
        cout << "Solution does not exist\n";

    return 0;
}
