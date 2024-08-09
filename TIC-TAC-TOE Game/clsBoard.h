#include<iostream>
class clsBoard
{
    private:
        char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
        short validAccount;
    public:
        clsBoard()
        {
            validAccount=0;
        }
        bool placeMarker(int slot,char currentMarker) 
        {
            int row = (slot - 1) / 3;
            int col = (slot - 1) % 3;

            if (board[row][col] != 'X' && board[row][col] != 'O'){
                board[row][col] = currentMarker;
                validAccount++;
                return 1;
            }
            return 0;
        }
        void print() {
            std::cout << "Tic-Tac-Toe Board:" << std::endl;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    std::cout << board[i][j];
                    if (j < 2) std::cout << " | ";
                }
                if (i < 2) std::cout << "\n---------\n";
            }
            std::cout << std::endl;
        }
        char checkWinner() {
            for (int i = 0; i < 3; i++) {
                // Check rows
                if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
                    return board[i][0];
                // Check columns
                if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
                    return board[0][i];
            }
            // Check diagonals
            if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
                return board[0][0];
            if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
                return board[0][2];
            return 0;
        }
        bool isEmptyPlaces()
        {
            return validAccount!=9;
        }

};