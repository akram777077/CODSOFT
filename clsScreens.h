#pragma once
#include <iostream>
#include<iomanip>
class clsScreens
{
    private:
        static std::string line()
        {
            return "---------------------------------------------------------------------------------------";
        }
    public:
    static void showMain() {
        std::cout << "Welcome to the Number Guessing Game!\n";
        std::cout << "------------------------------------\n";
        std::cout << "Try to guess the secret number between 1 and 100.\n";
        std::cout << "You will be prompted if your guess is too high or too low.\n";
        std::cout << "Good luck!\n";
        std::cout << "[1] start game.\n";
        std::cout << "[2] show high score.\n";
        std::cout << "[0] Exit.\n";

    }
    static void showHighScore(bool isHigh,clsResult* result = nullptr)
    {
        std::string title = (isHigh)?"High":"Your";
        title+=" Score\n";
        std::cout << "           "<<title;
        std::cout << "------------------------------------\n";
        if(!result)
            std::cout<<"Please play game first to show High Score...\n";
        std::cout<<line()<<"\n";
        std::cout<<"|"<<std::setw(20)<<std::left<<"\tTarget Number"<<"|";
        std::cout<<std::setw(20)<<std::left<<"\tnumber of rounds"<<"|";
        std::cout<<std::setw(15)<<std::left<<"\t  start"<<"|";
        std::cout<<std::setw(15)<<std::left<<"\t   end"<<"|";
        std::cout<<"\n"<<line()<<"\n";
        std::string input = "\tNULL";
        if(result)
            input="\t"+std::to_string(result->getTargetNumber());
        std::cout<<"|"<<std::setw(20)<<std::left<<input<<"|";
        if(result)
            input="\t"+std::to_string(result->getNumberOfRound());
        std::cout<<std::setw(20)<<std::left<<input<<"|";
        if(result)
            input="\t"+std::to_string(result->getStart());
        std::cout<<std::setw(15)<<std::left<<input<<"|";
        if(result)
            input="\t"+std::to_string(result->getEnd());
        std::cout<<std::setw(15)<<std::left<<input<<"|";
        std::cout<<"\n"<<line()<<"\n";

    }
    static void clearScreen()
    {
        system("cls");
    }

};