#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <conio.h>

using namespace std;

const int N = 9;
vector<vector<int>> grid(N, vector<int>(N, 0));

void printGrid() {
    for (int i = 0; i < N; i++) {
        if (i % 3 == 0 && i != 0) cout << "- - - - - - - - - - - -\n";
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0 && j != 0) cout << "| ";
            if (grid[i][j] == 0)
                cout << ". ";
            else
                cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(int row, int col, int num) {
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;
    
    return true;
}

bool solveSudoku() {
    int row, col;
    bool isEmpty = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) break;
    }
    if (!isEmpty) return true;
    
    for (int num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku()) return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

void generatePuzzle() {
    srand(time(0));
    for (int i = 0; i < 20; i++) {
        int row = rand() % N;
        int col = rand() % N;
        int num = rand() % 9 + 1;
        if (isSafe(row, col, num) && grid[row][col] == 0)
            grid[row][col] = num;
        else
            i--;
    }
}

bool isComplete() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (grid[i][j] == 0)
                return false;
    return true;
}

int main() {
    generatePuzzle();
    
    while (true) {
        system("cls");
        printGrid();
        if (isComplete()) {
            if (solveSudoku()) {
                cout << "Congratulations! You solved the puzzle!\n";
                break;
            } else {
                cout << "The current solution is incorrect. Keep trying!\n";
            }
        }
        
        int row, col, num;
        cout << "Enter row (1-9), column (1-9), and number (1-9) or 0 0 0 to quit: ";
        cin >> row >> col >> num;
        
        if (row == 0 && col == 0 && num == 0) break;
        
        if (row < 1 || row > 9 || col < 1 || col > 9 || num < 1 || num > 9) {
            cout << "Invalid input. Please try again.\n";
            continue;
        }
        
        row--; col--;  // Convert to 0-based index
        
        if (grid[row][col] != 0) {
            cout << "That cell is already filled. Try another one.\nPress any key to continue\n";
            getch();
            continue;
        }
        
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
        } else {
            cout << "That number can't be placed there. Try again.\nPress any key to continue\n";
            getch();
        }
    }
    
    cout << "Thanks for playing!\n";
    return 0;
}