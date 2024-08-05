#include <cstdlib> 
#include <ctime>
enum enRemark{low=1,found,high};
class clsGame
{
    private:
        int number;
        int getRandom(int start,int end)
        {
            srand(time(0));
            return rand()%(end-start)+start;
        }
    public:
        clsGame(int start,int end)
        {
            number = getRandom(start,end);
        }
        enRemark getRemark(int inputGuess)
        {
            if(inputGuess>number)
                return enRemark::high;
            else if(inputGuess<number)
                return enRemark::low;
            else
                return enRemark::found;
        }
        int getNumber()
        {
            return number;
        }
        
};