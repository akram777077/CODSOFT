#include <iostream>
#include <conio.h> // For _getch()
#include <string>
#include <vector>
class clsScreen
{
    static void displayMenu(const std::string& title,const std::vector<std::string>& options, int selected) {
        std::cout<<"------------------------------------------------"<<std::endl;
        std::cout<<"           "<<title+'\n';
        for (int i = 0; i < options.size(); i++) {
            if (i == selected) {
                std::cout << "> " << options[i] << " <" << std::endl;
            } else {
                std::cout << "  " << options[i] << std::endl;
            }
        }
        std::cout<<"------------------------------------------------"<<std::endl;
    }
public:
    static int getOptions(std::vector<std::string> menuOptions)
    {
        int selected = 0;
        while (true) {
            system("cls"); // Clear the console
            displayMenu("Library Main ",menuOptions, selected);
            char ch = _getch(); // Capture key press
            if (ch == 72) { // Up arrow
                selected = (selected == 0) ? menuOptions.size() - 1 : selected - 1;
            } else if (ch == 80) { // Down arrow
                selected = (selected == menuOptions.size() - 1) ? 0 : selected + 1;
            } else if (ch == 13) { // Enter key
                system("cls");
                return selected+1;
                // You can add specific functionality here based on the selection
                break;
            }
        }
    }
    static char pressKey()
    {
        return _getch();
    }


};