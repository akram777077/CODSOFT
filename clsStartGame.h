#include"clsScreens.h"
#include"clsValidation.h"
#include"clsResult.h"
#include"clsGame.h"
enum enChois{ex=0,startGame,showHighScore};
std::string clsResult::fileName="test1.txt";
class clsStartGame
{
    private:
        static std::string feedBack(enRemark remark)
        {
            if(remark==enRemark::found)
                return "Found !";
            if(remark==enRemark::high)
                return "Too High !";
            return "Too Low !";
        }

        static int getInputUser()
        {
            int input = 0;
            bool result;
            do
            {
                std::cout<<"[Enter] -> ";
                result = clsValidation::IsBetween(input,0,100);
                if(!result)
                    std::cout<<"[System] -> enter valid number please [0,100]\n";
            }while(!result);
            return input;
        }
        static void showScore(clsResult result)
        {
            clsScreens::clearScreen();
            clsResult* highScore = clsResult::load();
            bool isHighScore =!highScore || (result.numberRound < highScore->numberRound);
            clsScreens::showHighScore(0,&result);
            if(isHighScore && result.save())
                std::cout<<"[System] -> New High Score is saved...\n";
            
            clsScreens::pressEnter();
            
        }
        static void startGame()
        {
            clsGame game;
            enRemark remark;
            int count = 0;
            do 
            {
                remark = game.getRemark(getInputUser());
                std::cout<<"[Game "<<++count<<" ] -> "<<feedBack(remark)<<"\n";
                
            }while(remark!=enRemark::found);
            std::cout<<"[Game] -> You found the number "<<game.getNumber()<<" after "<<count<<" time(s)\n";
            clsResult result(game.getNumber(),count,0,100);
            clsScreens::pressEnter();
            showScore(result);
        }
        static void showHighScoreScreen()
        {
           clsScreens::showHighScore(1,clsResult::load());
           clsScreens::pressEnter();
        }
        static void doWithChois(enChois chois)
        {
            clsScreens::clearScreen();
            switch(chois)
            {
                case enChois::ex:
                    exit(0);
                    break;
                case enChois::startGame:
                    startGame();
                    break;
                case enChois::showHighScore:
                    showHighScoreScreen();
                    break;
            }
        }
        static void NewGame()
        {
            do
            {
                int chois=0;
                bool result = 1;
                clsScreens::clearScreen();
                clsScreens::showMain();
                do
                {
                    std::cout<<"[Chois] -> ";
                    result = clsValidation::IsBetween(chois,0,2);
                    if(!result)
                        std::cout<<"[System] -> enter valid number please [0,2]\n";
                }while (!result);
                doWithChois((enChois)chois);
            }while(1);
        }
    public:
        static void start()
        {
            NewGame();
        }
};