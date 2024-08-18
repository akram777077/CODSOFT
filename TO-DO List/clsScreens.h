#include<iostream>
#include<conio.h>
class clsScreens
{
    public:
        static void showMain()
        {
            std::cout << "Welcome to TO-Do List!\n";
            std::cout << "------------------------\n";
            std::cout << "[1] View Tasks.\n";
            std::cout << "[2] Add Task.\n";
            std::cout << "[3] Complete task.\n";
            std::cout << "[4] Remove task.\n";
            std::cout << "[0] Exit.\n";
            std::cout << "------------------------\n";
        }
        static void pressEnter()
        {
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Press Any Key to continue...";
            _getch();
        }
};