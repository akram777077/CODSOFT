class clsPlayers
{
    char player1;
    char player2;
    bool isFirstPlayer;
    public:
        clsPlayers(char player1,char player2)
        {
            this->player1=player1;
            this->player2=player2;
            this->isFirstPlayer=1;
        }
        void switchPlayer()
        {
            isFirstPlayer=!isFirstPlayer;
        }
        char markPlayer1()
        {
            return player1;
        }
        char markPlayer2()
        {
            return player2;
        }
        bool isMarkOfPlayer1(char mark)
        {
            return player1==mark;
        }
        bool isTurnOfPlayer1()
        {
            return isFirstPlayer;
        }
};