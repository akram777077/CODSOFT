#include<iostream>
#include<limits>
class clsValidation
{
    public:
        static bool getValidNumber(int& result)
        {
            std::cin >> result;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return 0;
            }

            return 1;
        }
        static bool IsBetween(int& result,int start,int end)
        {
            if(!getValidNumber(result))
                return 0;
            return result>=start && result<=end;

        }
};