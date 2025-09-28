#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enGameChoice{ Stone = 1, Paper = 2, Scissors = 3};
enum enWinner{ Player1 = 1, Computer = 2, Draw = 3};

struct stRoundInfo
{
    int RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName = "";
};
struct stGameResult
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};
int RandomNumber(int from, int to)
{
    return rand() % (to - from + 1) + from;
}
enGameChoice ReadPlayer1Choice()
{
    short Player1Choice = 0;

    do
    {
        cout << "\nYour Choice:\n";
        cout << "[1]:Stone, [2]:Paper, [3]:Scissors\n";
        cout << "Enter your choice: ";
        cin >> Player1Choice;

    } while (Player1Choice < 1 || Player1Choice > 3);
    
    return static_cast<enGameChoice>(Player1Choice);
}
enGameChoice ReadComputerChoice()
{
    return static_cast<enGameChoice>(RandomNumber(1,3));
}
enWinner HowWinTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch(RoundInfo.Player1Choice)
    {
        case enGameChoice::Stone:

            if (RoundInfo.ComputerChoice == enGameChoice::Paper)
            {
                return enWinner::Computer;
            }

            break;

        case enGameChoice::Paper:

            if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
            {
                return enWinner::Computer;
            }    
        
            break;

        case enGameChoice::Scissors:

            if (RoundInfo.ComputerChoice == enGameChoice::Stone)
            {
                return enWinner::Computer;
            }

            break;
    }
    
    return enWinner::Player1;
}
enWinner HowWinTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes == ComputerWinTimes) return enWinner::Draw;

    return Player1WinTimes > ComputerWinTimes  ?   enWinner::Player1 : enWinner::Computer;
}

string WinnerName(enWinner Winner)
{
    string arr[3] = {"Player1","Computer","No Winner"};
    return arr[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
    string arr[3] = {"Stone", "Paper", "Scissors"};
    return arr[Choice - 1];
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice : " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;
}

void SetScreenColor(enWinner winner)
{
    switch (winner)
    {
        case enWinner::Player1:
            system("color 2F"); // Green
            break;
        case enWinner::Computer:
            system("color 4F");  // Red
            break;
        case enWinner::Draw:
            system("color 6F"); // Yollow
            break;
    }
}

stGameResult FillGameResult(short Rounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResult GameResult;

    GameResult.GameRounds = Rounds;
    GameResult.ComputerWinTimes = ComputerWinTimes;
    GameResult.Player1WinTimes = Player1WinTimes;
    GameResult.DrawTimes = DrawTimes;
    GameResult.GameWinner = HowWinTheGame(Player1WinTimes,ComputerWinTimes);
    GameResult.WinnerName = WinnerName(GameResult.GameWinner);

    return GameResult;
}

stGameResult PlayGame(short GameRounds)
{
    stRoundInfo RoundInfo;

    short ComputerWinTimes = 0, Player1WinTimes = 0, DrawTimes = 0;

    for(short GameRound = 1; GameRound <= GameRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = ReadComputerChoice();
        RoundInfo.Winner = HowWinTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes ++;

        else if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes ++;

        else
            DrawTimes ++;

        PrintRoundResult(RoundInfo);
    }

    return FillGameResult(GameRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";

    for (int i = 0; i < NumberOfTabs; i++)
    {
        t += "\t";
    }
    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << "------------------------------------------------------" << endl;
    cout << Tabs(2) << "               + + + G A M E  O V E R + + +           " << endl;
    cout << Tabs(2) << "------------------------------------------------------\n\n" << endl;

}

short ReadHowManyRounds()
{
    short GameRounds = 1;

    do
    {
        cout << "How Many Rounds 1 to 10 ?\n";
        cin >> GameRounds;

    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;
    
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void PrintGameResult(stGameResult GameResult)
{
    cout << Tabs(2) << "--------------------[Game Results]-------------------" << endl;
	cout << Tabs(2) << "Game Rounds        : " << GameResult.GameRounds << endl;
	cout << Tabs(2) << "Player Won Times   : " << GameResult.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer Won Times : " << GameResult.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times         : " << GameResult.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResult.WinnerName << endl;
    cout << Tabs(2) << "------------------------------------------------------" << endl;
}

void StartGame()
{
    char PlayAgain = 'y';

    do
    {
        ResetScreen();
        stGameResult GameResult = PlayGame(ReadHowManyRounds());
        SetScreenColor(GameResult.GameWinner); 
        ShowGameOverScreen();
        PrintGameResult(GameResult);

        cout << "\nDo You Want To Play Again? (Y)/(N) "; 
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
    
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}
