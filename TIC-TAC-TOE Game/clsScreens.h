#include<iostream>
#include<limits>
class clsScreens
{
    public:
    static void pressEnter()
    {
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"Press Any Key to continue...";
        std::cin.get();
    }
    static void selectMarks()
    {
        std::cout<<"              Select Mod\n";
        std::cout<<"----------------------------------------\n";
        std::cout<<"[1] player 1 with 'X' player 2 with 'O'.\n";
        std::cout<<"[2] player 1 with 'O' player 2 with 'x'.\n";
        std::cout<<"----------------------------------------\n";
    }
    static void moreGame()
    {
        std::cout<<"Do you want more game ? \n";
        std::cout<<"press [n] for No and any char for Yes";
    }
    static void mainScreen()
    {
        std::cout << "                        TIC-TAC-TOE Game\n";
        std::cout << "------------------------------------------------------------------------\n";
        std::cout << "This is a simple Tic-Tac-Toe game where two players take turns\n";
        std::cout << "marking a space in a 3x3 grid with their respective symbols (X or O).\n";
        std::cout << "The goal is to place three of your marks in a horizontal, vertical,\n";
        std::cout << "or diagonal row before your opponent does. If all spaces are filled\n";
        std::cout << "without either player achieving three in a row, the game ends in a draw.\n";
        std::cout << "Have fun!\n";
        std::cout << "-----------------------------------------------------------------------\n";
        std::cout<<"press [n] for No and any char for Yes";
    }
    static void displayRules()
    {
        std::cout << "      Welcome to The game\n";
        std::cout << "------------------------------------\n";
        std::cout << "Rules:\n";
        std::cout << "1. Enter the number of slot\n";
        std::cout << "2. slot should be empty\n";
        std::cout << "3. Enter valid number\n";
        std::cout << "------------------------------------\n";
    }
};