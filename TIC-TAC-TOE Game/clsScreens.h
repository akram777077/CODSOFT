#include<iostream>
#include<limits>
class clsScreens
{
    public:
    static void pressEnter()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"Press Any Key to continue...";
        getchar();
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
        std::cout<<"press [n] for No and any char for Yes\n";
    }
};