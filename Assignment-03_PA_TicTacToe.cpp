#include <iostream>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);

int main() {
    //
    //	PLEASE DO NOT CHANGE function main
    //
    char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
    displayBoard(board);

    while (true) {
        // The first player makes a move
        //move(board, 'X');
        makeAMove(board, 'X');
        displayBoard(board);

        if (isWon('X', board)) {
            cout << "X player won" << endl;
            exit(0);
        }
        else if (isDraw(board)) {
            cout << "No winner" << endl;
            exit(0);
        }

        // The second player makes a move
        makeAMove(board, 'O');
        displayBoard(board);

        if (isWon('O', board)) {
            cout << "O player won" << endl;
            exit(0);
        }
        else if (isDraw(board)) {
            cout << "No winner" << endl;
            exit(0);
        }
    }

    return 0;
}

/*
 * returns true if the char "player" shows 3 in a row
 * returns false if that is not the case
 */
bool isWon(char player, char board[3][3])
{
    if(board[0][0] == player && board[0][0] == board[0][1] && board[0][0] == board[0][2])
        return true;
    else if(board[0][0] == player && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return true;
    else if(board[0][0] == player && board[0][0] == board[1][0] && board[0][0] == board[2][0])
        return true;
    else if(board[1][0] == player && board[1][0] == board[1][1] && board[1][0] == board[1][2])
        return true;
    else if(board[2][0] == player && board[2][0] == board[2][1] && board[2][0] == board[2][2])
        return true;
    else if(board[0][1] == player && board[0][1] == board[1][1] && board[0][1] == board[2][1])
        return true;
    else if(board[0][2] == player && board[0][2] == board[1][2] && board[0][2] == board[2][2])
        return true;
    else if(board[0][2] == player && board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return true;
    else
        return false;
}

/*
 * returns true if all spots in the board are full, but there aren't any winners
 * returns false if the board isn't full
 * returns false if the board is full and there is a winner
 */
bool isDraw(char board[3][3])
{
    bool full = true;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != 'X' && board[i][j] != 'O')
                full = false;
        }
    }

    if(!full)
        return false;
    else if(isWon('X',board))
        return false;
    else if(isWon('O', board))
        return false;
    else
        return true;
}

/*
 * iterates through the board and returns a visual of the 2D array
 */
void displayBoard(char board[3][3])
{
    cout << "-------------" << endl;
    cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |" << endl;
    cout << "-------------" << endl;
    cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |" << endl;
    cout << "-------------" << endl;
    cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |" << endl;
    cout << "-------------" << endl;
}

/*
 *
 */
void makeAMove(char board[3][3], char player) {
    int row, col;
    cout << "Enter a row (0, 1, 2) for player " << player << ": ";
    cin >> row;

    cout << "Enter a column (0, 1, 2) for player " << player << ": ";
    cin >> col;

    if (board[row][col] != 'X' && board[row][col] != 'O')
    {
        board[row][col] = player;
    }
    else {
        cout << "This cell is already occupied. Try a different cell." << endl;
        makeAMove(board, player);
    }
}