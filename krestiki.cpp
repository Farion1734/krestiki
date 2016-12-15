#include <iostream>  // "O" = 2 . "X" = 1
#include <string>

int COMPUTER_INDEX = 2;
int PLAYER_INDEX = 1;
int ThreeInARow[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};


int WeHaveAWinner(int board[])
{
    if ((board[0] == 2 && board[1] == 2 && board[2] == 2) ||
            (board[3] == 2 && board[4] == 2 && board[5] == 2) ||
            (board[6] == 2 && board[7] == 2 && board[8] == 2) ||
            (board[0] == 2 && board[3] == 2 && board[6] == 2) ||
            (board[1] == 2 && board[4] == 2 && board[7] == 2) ||
            (board[2] == 2 && board[5] == 2 && board[8] == 2) ||
            (board[0] == 2 && board[4] == 2 && board[8] == 2) ||
            (board[2] == 2 && board[4] == 2 && board[6] == 2))
    {
        return  2;
    }
    
    if ((board[2] == 1 && board[4] == 1 && board[6] == 1) ||
            (board[0] == 1 && board[1] == 1 && board[2] == 1) ||
            (board[3] == 1 && board[4] == 1 && board[5] == 1) ||
            (board[6] == 1 && board[7] == 1 && board[8] == 1) ||
            (board[0] == 1 && board[3] == 1 && board[6] == 1) ||
            (board[1] == 1 && board[4] == 1 && board[7] == 1) ||
            (board[2] == 1 && board[5] == 1 && board[8] == 1) ||
            (board[0] == 1 && board[4] == 1 && board[8] == 1))
    {
        return 1;
    }
    return -1;
}

int ComputerHasTwo(int board[])
{
    for(int i = 0; i <= 7; i++)
    {
        int missing = 0;
        int missingSpot = 0;
        
        for(int j = 0; j <= 2; j++)
        {
            if (board[ThreeInARow[i][j]] != COMPUTER_INDEX)
            {
                missing += 1;
                missingSpot = ThreeInARow[i][j] ;
            }
        }
        if (missing == 1 && board[missingSpot] != PLAYER_INDEX)
            return missingSpot;
    }
    return -1;
}

int PlayerHasTwo(int board[])
{
    for(int i = 0; i <= 7; i++)
    {
        int missing = 0;
        int missingSpot = 0;
        
        for(int j = 0; j <= 2; j++)
        {
            if (board[ThreeInARow[i][j]] != PLAYER_INDEX)
            {
                missing += 1;
                missingSpot = ThreeInARow[i][j] ;
            }
        }
        if (missing == 1 && board[missingSpot] != COMPUTER_INDEX)
            return missingSpot;
    }
    return -1;
}

int CenterIsEmpty(int board[])
{
    if (board[4] == 0) return 4;
    return -1;
}

int AMove(int board[])
{
    for (int i = 0; i <= 8; i++)
        if (board[i] == 0)
            return i;
    return -1;
}


void ComputerMakesAMove(int board[])
{
    if (ComputerHasTwo(board) != -1) board[ComputerHasTwo(board)] = COMPUTER_INDEX;
    else if (PlayerHasTwo(board) != -1) board[PlayerHasTwo(board)] = COMPUTER_INDEX;
    else if (CenterIsEmpty(board) != -1) board[CenterIsEmpty(board)] = COMPUTER_INDEX;
    else if (AMove(board) != -1) board[AMove(board)] = COMPUTER_INDEX;
}

void PlayerMakesAMove(int board[])
{
    bool haveInput = false;
    int spot = -1, row = -1 , column = -1;
    
    while (!haveInput)
    {
        std::cout << "Give me a row!(1,2,3) \n";
        std::cin >> row;
        std::cout << "Give me a coulumn!(1,2,3) \n";
        std::cin >> column;
        
        spot = (row - 1) * 3 + column -1;
        
        if (board[spot] == 0)
        {
            board[spot] = PLAYER_INDEX;
            haveInput = true;
        }
        else std::cout << ("You can't go there! \n");
    }
}

void indexToSymbol(int index)
{
    if (index == 1) std::cout<< "X";
    else if (index == 2) std::cout << "O";
    else std::cout << ".";
}

void TableShow(int board[])
{
    std::cout << "  | 1   2   3 \n";
    std::cout << "--+---------- \n";
    
    for(int i = 0; i <= 2; i++)
    {
        std::cout << i + 1;
        std::cout << " | ";
        indexToSymbol(board[i*3]);
        std::cout << " | ";
        indexToSymbol(board[i*3+1]);
        std::cout << " | ";
        indexToSymbol(board[i*3+2]);
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main()
{
    int board[9] = {0,0,0,0,0,0,0,0,0};
    int turn = 1;
    bool gameIsOn = true;
    
    while (gameIsOn)
    {
        TableShow(board);
        
        if (turn == 1)
            PlayerMakesAMove(board);
        else
            ComputerMakesAMove(board);
        
        if (WeHaveAWinner(board) == 1)
        {
            std::cout << "Player has Won ! \n";
            TableShow(board);
            gameIsOn = false;
        }
        else if (WeHaveAWinner(board) == 2)
        {
            std::cout<<"Computer has Won! \n";
            TableShow(board);
            gameIsOn = false;
        }
        if (AMove(board) == -1)
        {
            std::cout<< "It's a draw! \n";
            TableShow(board);
            gameIsOn = false;
        }
        turn = (turn % 2) + 1;
    }
    
}