#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
class clsResult
{
    private:
        int targetNumber;
        int numberRound;
        int start;
        int end;
        std::string toLine() const {
            std::ostringstream oss;
            oss << targetNumber << " " << numberRound << " " << start << " "<<end;
            return oss.str();
        }
    public:
        void print()
        {
            std::cout<<"target Number: "<<targetNumber;
            std::cout<<"number rounds: "<<numberRound;
            std::cout<<"start: "<<start;
            std::cout<<"end: "<<end;
        }
        static std::string fileName;
        clsResult(int targetNumber,int numberRound,int start,int end)
        {
            this->targetNumber=targetNumber;
            this->numberRound=numberRound;
            this->start=start;
            this->end=end;
        }
        bool save()
        {
            std::fstream file;
            file.open(fileName,std::ios::out);
            if(!file)
                return 0;
            file<<toLine();
            file.close();
            return 1;
        }
        static clsResult* load()
        {
            std::string line="";
            std::fstream file;
            file.open(fileName);
            if(!file)
                return nullptr;
            std::getline(file,line);
            file.close();
            int arr[4];
            std::istringstream iss(line);
            iss >> arr[0] >> arr[1] >> arr[2] >> arr[3];
            return new clsResult(arr[0],arr[1],arr[2],arr[3]);
        }
        int getTargetNumber()
        {
            return targetNumber;
        }
        int getStart()
        {
            return start;
        }
        int getEnd()
        {
            return end;
        }
        int getNumberOfRound()
        {
            return numberRound;
        }
};