#include<iostream>
#include<limits>
class clsScreens
{
    public:
    static void showMain() {
        std::cout << "Welcome to the Simple Calculator!\n";
        std::cout << "------------------------------------\n";
        std::cout << "[1] start Calculator.\n";
        std::cout << "[2] show history.\n";
        std::cout << "[3] delete history.\n";
        std::cout << "[0] Exit.\n";
    }
    static void pressEnter()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"Press Any Key to continue...";
        getchar();
    }
};