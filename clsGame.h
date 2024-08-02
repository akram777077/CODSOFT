#include <cstdlib> 
#include <ctime>
enum enRemark{low=1,found,high};
class clsGame
{
    private:
        int number;
        int getRandom(int start,int end)
        {
            return rand()%(end-start)+start;
        }
    public:
        clsGame()
        {
            number = getRandom(0,100);
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
        
};