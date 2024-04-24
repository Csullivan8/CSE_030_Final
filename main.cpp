#include <iostream>
#include <istream>
#include <string>
#include <system_error>
#include <cctype>
#include "GameState.h"
#include "EnemyAI.h"
#include "GameFunctions.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

using namespace std;

void printInstructions(){
    GameState instGame;
    cout <<
    "-----------------------------------------------------------------------------------------------------------\n"
    "Player 1 is " << RED << "X" << RESET << ", and will go first.\n";
    instGame.play(0,0);
    cout << instGame << endl;
    cout << "Player 2 is " << GREEN << "O" << RESET << ", and will go after player 2.\n\n";
    instGame.play(1,1);
    cout << instGame << endl;
    cout <<
    "Players will continue to make moves after each other until one of the players wins or the board is filled.\n" <<
    "A player wins when they get a string of their marks the size of the board.\n" <<
    "The string of marks can be vertical, horizontal, or diagonal.\n\n" <<
    "    0   1   2        0   1   2        0   1   2 \n" << 
    "   --- --- ---      --- --- ---      --- --- ---\n" <<
    "0 |   | " << RED << "X" << RESET << " |   |    | " << RED << "X" << RESET << " | " << RED << "X" << RESET << " | " << RED << "X" << RESET << " |    |   |   | " << RED << "X" << RESET << " |\n" <<
    "   --- --- ---      --- --- ---      --- --- ---\n" <<
    "1 |   | " << RED << "X" << RESET << " |   |    |   |   |   |    |   | " << RED << "X" << RESET << " |   |\n" <<
    "   --- --- ---      --- --- ---      --- --- ---\n" <<
    "2 |   | " << RED << "X" << RESET << " |   |    |   |   |   |    | " << RED << "X" << RESET << " |   |   |\n" <<
    "   --- --- ---      --- --- ---      --- --- ---\n\n" <<
    "The game will end in a tie if the board is filled with marks and neither player achieves the win condition.\n\n" <<
    "    0   1   2\n" <<
    "   --- --- ---\n" <<
    "0 | " << RED << "X" << RESET << " | " << GREEN << "O" << RESET << " | " << RED << "X" << RESET << " |\n" <<
    "   --- --- ---\n" <<
    "1 | " << GREEN << "O" << RESET << " | " << GREEN << "O" << RESET << " | " << RED << "X" << RESET << " |\n" <<
    "   --- --- ---\n" <<
    "2 | " << GREEN << "O" << RESET << " | " << RED << "X" << RESET << " | " << GREEN << "O" << RESET << " |\n" <<
    "   --- --- ---\n" <<
    

    "-----------------------------------------------------------------------------------------------------------\n";
}

int main()
{
    system("clear");
    GameState game;
    game.play(0, 0);
    game.play(1, 1);
    cout << game << endl;
    cout << "EXTREME TIC TAC TOE!!!!";
    bool looping = true;
    while(looping == true)
    {
        
        Menu();
        int input;
        cin >> input;
        system("clear");
        cout << endl << endl;
        int sizeBoard;
        bool gameActive = true;
        
        switch(input)
        {
            case 1:
                system("clear");
                // cout << "It is tic tac toe!" << endl;
                printInstructions();
                PressEnter(1);
                  /// enter button
                break;
            case 2:
                cout << "What size board would you like!" << endl;
                cin >> sizeBoard;
                pvp(sizeBoard, gameActive);
                PressEnter();/// continue
                break;
            case 3:
                cout << "What size board would you like!" << endl;
                cin >> sizeBoard;
                EasyAi(sizeBoard, gameActive);
                PressEnter();
                break;
            case 4: //If Ai first will always win or tie
                cout << "What size board would you like!" << endl;
                cin >> sizeBoard;
                HardAi(sizeBoard, gameActive);
                PressEnter();
                break;
            case 5:
                PointOption();
                PressEnter(1);
                break;
            case 6:
                ClearpointsOption();
                PressEnter(1);
                break;
            case 7:
                cout << "Goodbye!\n\n";
                looping = false;
                break;
            default:
                cout << "Error. Enter a valid input";
                break;
        }
    }
    
    return 0;
}
