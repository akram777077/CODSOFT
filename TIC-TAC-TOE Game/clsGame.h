#include"clsBoard.h"
#include"clsPlayers.h"
enum enResult{player1 = 1,player2,draw,Continue};
class clsGame
{
    private:
        clsBoard board;
        clsPlayers* players;

    public:
        clsGame(char player1,char player2)
        {
            players = new clsPlayers(player1,player2);
        }
        void printBoard()
        {
            board.print();
        }
        bool markInTheBoard(short slot)
        {
            char currentMark = (players->isTurnOfPlayer1())?players->markPlayer1():players->markPlayer2();
            if(board.placeMarker(slot,currentMark))
            {
                players->switchPlayer();
                return 1;
            }
            return 0;
        }
        enResult checkGame()
        {
            
            if(players->isMarkOfPlayer1(board.checkWinner()))
                return enResult::player1;
            if(players->isMarkOfPlayer2(board.checkWinner()))
                return enResult::player2;
            if(!board.isEmptyPlaces())
                return enResult::draw;
            return enResult::Continue;
        }
        bool isFirstPlayerTurn()
        {
            return players->isTurnOfPlayer1();
        }

};