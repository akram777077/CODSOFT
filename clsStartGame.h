#include"clsScreens.h"
#include"clsValidation.h"
#include"clsResult.h"
#include"clsGame.h"
enum enChois{ex=0,startGame,showHighScore};
std::string clsResult::fileName="test.txt";
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
            clsScreens::pressEnter();
        }
        static void doWithChois(enChois chois)
        {
            clsScreens::clearScreen();
            switch(chois)
            {
                case enChois::ex:
                    break;
                case enChois::startGame:
                    startGame();
                    break;
                case enChois::showHighScore:
                    break;
            }
        }
        static void NewGame()
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
        }
    public:
        static void start()
        {
            NewGame();
        }
};