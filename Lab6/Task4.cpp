#include <iostream>
#include <vector>
using namespace std;

int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool isSafe(vector<vector<int>>& board, int n, int row, int col)
{
    return row >= 0 && row < n &&
           col >= 0 && col < n &&
           board[row][col] == -1;
}

bool solveKnightTour(vector<vector<int>>& board, int n,
                     int row, int col, int moveNumber)
{
    board[row][col] = moveNumber;

    if (moveNumber == n * n)
        return true;

    // Try all eight possible knight moves
    for (int i = 0; i < 8; i++)
    {
        int nextRow = row + dx[i];
        int nextCol = col + dy[i];

        if (isSafe(board, n, nextRow, nextCol))
        {
            if (solveKnightTour(board, n, nextRow, nextCol,
                                moveNumber + 1))
                return true;
        }
    }

    // Undo the move when it leads to a dead end
    board[row][col] = -1;
    return false;
}

void displayBoard(vector<vector<int>>& board, int n)
{
    cout << "\nKnight's Tour Board:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout.width(4);
            cout << board[i][j];
        }

        cout << endl;
    }
}

int main()
{
    int n, startRow, startCol;

    cout << "Enter chessboard size N: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid board size." << endl;
        return 1;
    }

    if (n > 100)
    {
        cout << "Board size is too large for this program." << endl;
        return 1;
    }

    cout << "Enter starting row (0 to " << n - 1 << "): ";
    cin >> startRow;

    cout << "Enter starting column (0 to " << n - 1 << "): ";
    cin >> startCol;

    if (cin.fail() || startRow < 0 || startRow >= n ||
        startCol < 0 || startCol >= n)
    {
        cout << "Invalid starting position." << endl;
        return 1;
    }

    vector<vector<int>> board(n, vector<int>(n, -1));

    if (solveKnightTour(board, n, startRow, startCol, 1))
    {
        displayBoard(board, n);
    }
    else
    {
        cout << "No Knight's Tour found for this search."
             << endl;
    }

    return 0;
}