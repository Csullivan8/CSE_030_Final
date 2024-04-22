#include <iostream>
#include <istream>
#include <string>
#include <system_error>
#include <cctype>
#include "GameState.h"
#include "EnemyAI.h"
#include "GameFunctions.h"

using namespace std;

int main()
{
    system("clear");
    GameState game;

    
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
                cout << "It is tic tac toe!" << endl;
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
                cout << "Goodbye!";
                looping = false;
                break;
            default:
                cout << "Error. Enter a valid input";
                break;
        }
    }
    
    return 0;
}
