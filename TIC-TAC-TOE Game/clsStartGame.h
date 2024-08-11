#include"clsGame.h"
#include"clsScreens.h"
#include"../Number Guessing Game/clsValidation.h"
class clsStartGame
{
    private:
        static std::string resultToString(enResult r)
        {
            switch(r)
            {
            case enResult::draw:
                return "Draw";
            case enResult::player1:
                return "Player 1 win";
            case enResult::player2:
                return "Player 2 win";
            default:
                return "";
            }
            
        }
        static enResult oneGame(char player1,char player2,short& count,clsBoard& board)
        {
            clsGame  game(player1,player2);
            enResult result;
            bool isValid=1;
            int slot;
            do
            {
                system("cls");
                game.printBoard();
                if(!isValid)
                    std::cout<<"[System] -> slot "<<slot<<" is not empty..\n";
                bool isNumber=1;
                do
                {
                    std::cout<<"-> Player "<<((game.isFirstPlayerTurn())?"1":"2")<<" : ";
                    isNumber=clsValidation::IsBetween(slot,1,9);
                    if(!isNumber)
                    {
                        system("cls");
                        game.printBoard();
                        std::cout<<"[System] -> Enter valid number between 1 and 9\n";
                    }
                }while(!isNumber);
                isValid=game.markInTheBoard(slot);
                if(isValid)
                    count++;
                result=game.checkGame();
            } while (result==enResult::Continue);
            system("cls");
            game.printBoard();
            board=game.getBoard();
            return result;
        }
        static void getMarkPlayers(char& player1,char& player2)
        {
            system("cls");
            int mod = 0;
            bool isValid=1;
            clsScreens::selectMarks();
            do
            {
                std::cout<<"[Mod] -> ";
                isValid=clsValidation::IsBetween(mod,1,2);
                system("cls");
                clsScreens::selectMarks();
                if(!isValid)
                    std::cout<<"[System] -> enter valid mod 1 or 2\n";
                else
                    std::cout<<"[System] -> the mod is "<<mod;
            }while(!isValid);
            if(mod==1)
            {
                player1='X';
                player2='O';
            }
            else if(mod==2)
            {
                player1='O';
                player2='X';
            }
            std::cout<<"\nStart Game...\n";
            clsScreens::pressEnter();

        }
        static void showResult(enResult resultGame,short numberMoves,clsBoard board)
        {
            system("cls");
            std::cout<<"Game Result\n";
            std::cout<<"------------\n";
            board.print();
            std::cout<<"Result game is: "<<resultToString(resultGame)<<std::endl;
            std::cout<<"total moves: "<<numberMoves<<"/9\n";
        }
        static void pStart()
        {
            short count = 0;
            char player1,player2;
            char again;
            do
            {
                system("cls");
                getMarkPlayers(player1,player2);
                clsBoard board;
                enResult result = oneGame(player1,player2,count,board);
                clsScreens::pressEnter();
                showResult(result,count,board);
                clsScreens::moreGame();
                again=std::cin.get();
            }while(again!='n');
            system("cls");
        }
    public:
        static void start()
        {
            pStart();
        }

};