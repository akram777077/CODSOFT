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
    static void displayRules()
    {
        std::cout << "      Welcome to Calculator\n";
        std::cout << "------------------------------------\n";
        std::cout << "Rules:\n";
        std::cout << "1. Syntax: number1 operator number2\n";
        std::cout << "2. Operators: +, -, *, /\n";
        std::cout << "3. Numbers should be of type double\n";
        std::cout << "4. Interval for numbers: ["<<std::numeric_limits<double>::min()<<","<<std::numeric_limits<double>::max()<<"]\n";
        std::cout << "5. Type 'clear' to clear the screen.\n";
        std::cout << "6. Type 'exit' to return to the main menu.\n";
        std::cout << "------------------------------------\n";
    }
};