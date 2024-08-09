#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <regex>
#include<fstream>

class clsCalculater
{
    double num1;
    double num2;
    char mathOperator;
    double result;

    double calculation()
    {
        switch (mathOperator)
        {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0)
            {
                throw std::invalid_argument("Division by zero is not allowed.");
            }
            return num1 / num2;
        default:
            throw std::invalid_argument("Invalid mathematical operator.");
        }
    }
    std::string calcToLine()
    {
        return std::to_string(num1)+mathOperator+std::to_string(num2)+"="+std::to_string(getResult());
    }
public:
    static std::string fileName;
    clsCalculater(double num1, double num2, char mathOperator,double result=0)
    {
        this->num1 = num1;
        this->num2 = num2;
        this->mathOperator = mathOperator;
        this->result=result;
    }

    static bool isDataValide(std::string& data)
    {
        std::regex pattern(R"((\d+(\.\d+)?)\s*([+\-*/])\s*(\d+(\.\d+)?))");
        return std::regex_match(data, pattern);
    }

    static clsCalculater getInfromationFromString(std::string& data)
    {
        std::istringstream iss(data);
        double num1, num2;
        char mathOperator;

        iss >> num1 >> mathOperator >> num2;
            if (num1 < -std::numeric_limits<double>::max() || num1 > std::numeric_limits<double>::max() ||
                num2 < -std::numeric_limits<double>::max() || num2 > std::numeric_limits<double>::max())
            {
                throw std::overflow_error("Overflow or underflow detected in numeric input.");
            }
        return clsCalculater(num1, num2, mathOperator);
    }

    double getResult()
    {
        result=calculation();
        return result;
    }

    static clsCalculater lineToCalc(std::string& line)
    {
        double num1,num2,result;
        char mathOperator;
        std::istringstream iss(line);
        iss >> num1 >> mathOperator >> num2 >> std::ws && iss.peek() == '=' && iss.ignore() >> result;
        return clsCalculater(num1,num2,mathOperator,result);
    }
    void print()
    {
        std::cout<<"-> "<<num1<<mathOperator<<num2<<"="<<result<<std::endl;
    }
    void save()
    {
        std::fstream file;
        file.open(fileName,std::ios::out | std::ios::app);
        if(!file)
            return;
        std::string result = calcToLine();
        file<<result<<std::endl;
        file.close();
    }
    static bool load()
    {
        std::fstream file(fileName);
        if(!file.is_open())
            return 0;
        std::string line;
        bool result = 0;
        while(std::getline(file,line))
        {
            lineToCalc(line).print();
            result = 1;
        }
        return result;
    }
};