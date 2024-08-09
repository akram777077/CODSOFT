#include"clsScreens.h"
#include"../Number Guessing Game/clsValidation.h"
#include"clsCalculator.h"
std::string clsCalculater::fileName = "calculator.txt";
enum enOption {ex=0,startCalculator,showHistory,deleteHistory};
class clsStartCalculator
{
    static void start()
    {
        do
        {
            system("cls");
            clsScreens::showMain();
            int chois = getInputUser(0,3);
            selectOption((enOption)chois);
        }while(1);
       
    }
    static void selectOption(enOption option)
    {
        switch (option)
        {
            case enOption::ex:
                exit(0);
                break;
            case enOption::startCalculator:
                calculator();
                break;
            case enOption::deleteHistory:
                deleteHistory();
                break;
            case enOption::showHistory:
                showHistory();
                break;
        }
    }
    static void deleteHistory()
    {
        system("cls");
        if (std::remove(clsCalculater::fileName.c_str()) == 0) {
            std::cout << "[System] -> The Calculation history is deleted..\n";
        } else {
            std::cout << "[System] -> Error: Unable to open the file.\n";
        }
        clsScreens::pressEnter();
    }
    static void showHistory()
    {
        system("cls");
        bool result = clsCalculater::load();
        if(!result)
            std::cout<<"[System] -> No Calculations found !!\n";
        clsScreens::pressEnter();
    }
    static void calculator()
    {
            system("cls");
            clsScreens::displayRules();
            clsScreens::pressEnter();
            system("cls");
            std::string input="";
            do
            {
                std::cout<<"Enter: ";
                std::getline(std::cin>>std::ws,input);
                if(input == "clear")
                {
                    system("cls");
                    continue;
                }
                else if(input == "exit")
                    return;
                std::cout<<" -> ";
                bool test = 1;
                try
                {
                    test = clsCalculater::isDataValide(input);
                }
                catch(const std::exception& e)
                {
                    std::cout<<"Error: "<<e.what();
                }
                
                if(test)
                {
                    try
                    {
                    auto temp = clsCalculater::getInfromationFromString(input);
                    std::cout<<temp.getResult();
                    temp.save();
                    }
                    catch (const std::invalid_argument& e)
                    {
                        std::cout<<"Error: "<<e.what();
                    }
                }
                else
                    std::cout<<"Error syntax";
                std::cout<<std::endl;
            }while(1);
    }
    static int getInputUser(int start,int end)
    {
        int input = 0;
        bool result;
        do
        {
            std::cout<<"[Enter] -> ";
            result = clsValidation::IsBetween(input,start,end);
            if(!result)
                std::cout<<"[System] -> enter valid number please ["<<start<<","<<end<<"]\n";
        }while(!result);
        return input;
    }
    public: // hada brk public 
        static void startCalculator()
        {
            start();
        }
};