#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "EnemyAI.h"
#include "GameState.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string input, char splitChar) {
  vector<string> output;
  string current = "";
  for (int i = 0; i < input.length(); i++) {
    if (input[i] != splitChar) {
      current += input[i];
    } else {
      output.push_back(current);
      current = "";
    }
  }
  output.push_back(current);
  return output;
}

void PressEnter(int num = 0) {
  std::cout << "\n\npress Enter: ";
  if (num == 1) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  cin.clear();
  cin.get();
  system("clear");
}

void Menu() {
  cout << endl << endl;
  cout << "1: Instructions" << endl;
  cout << "2: pvp mode" << endl;
  cout << "3: weak AI" << endl;
  cout << "4: strong AI" << endl;
  cout << "5: Wins Collected" << endl;
  cout << "6: Erase Wins Data" << endl;
  cout << "7: quit" << endl << endl;
  cout << "Choose an Option to Continue." << endl;
}

string Storepoints(string playerFile) {
  int point = 1;

  ofstream file;
  file.open(playerFile, ios::app);
  if (file.is_open()) {
    file << point << endl;
    file.close();
    return "";
  } else {
    return "file can't open\n";
  }
}

int ReadPoints(string playerFile) {
  int Total_points = 0;
  int num;

  ifstream file;
  file.open(playerFile, ios::in);
  if (file.is_open()) {
    while (file >> num) {
      if (num == 1) {
        Total_points += num;
      } else {
        break;
      }
    }
    file.close();
  }
  return Total_points;
}
// adds points according to specific files and players
void points(bool gameActive, bool player, string file) {
  if (gameActive == false && player) {
    Storepoints(file);
  }
}
int DisplayPoints(string file) { return ReadPoints(file); }
void PointOption() {
  cout << "           player 1       player 2";
  cout << "\n\nPvP mode:    " << DisplayPoints("player1") << "               "
       << DisplayPoints("player2");
  cout << "\n\nEasy mode:   " << DisplayPoints("Easyplayer1")
       << "               " << DisplayPoints("Easyplayer2");
  cout << "\n\nHard mode:   " << DisplayPoints("HardPlayer1")
       << "               " << DisplayPoints("HardPlayer2") << "\n";
}
void ClearPoints() {
  ofstream file;
  ofstream file1;
  ofstream file2;
  ofstream file3;
  ofstream file4;
  ofstream file5;
  file.open("player1", ios::out);
  file1.open("player2", ios::out);
  file2.open("Easyplayer1", ios::out); ////////fix
  file3.open("Easyplayer2", ios::out);
  file4.open("HardPlayer1", ios::out);
  file5.open("HardPlayer1", ios::out);
  if (file.is_open()) {
    file << "";
    if (file1.is_open()) {
      file1 << "";
      if (file2.is_open()) {
        file2 << "";
        if (file3.is_open()) {
          file3 << "";
          if (file4.is_open()) {
            file4 << "";
            if (file5.is_open()) {
              file5 << "";
            }
          }
        }
      }
    }
  }

  else {
    cout << "files refuse to open";
  }
  file.close();
  file1.close();
  file2.close();
  file3.close();
  file4.close();
  file5.close();
}
void ClearpointsOption() {
  ClearPoints();
  PointOption();
  cout << "\n\nAll Data Has Been Erased";
}
void pvp(int sizeBoard, bool gameActive) {
  system("clear");
  if (sizeBoard < 1) {
    cout << "Error. Enter a valid input";
  } else {
    GameState pvpGame(sizeBoard);
    string temp;
    getline(cin, temp);
    time_t loopStartTime = time(0);
    time_t moveStartTime = loopStartTime;
    while (gameActive) {
      bool acceptedInput = false;
      vector<string> splitInput;
      int x;
      int y;

      while (!acceptedInput) {
        cout << pvpGame << endl;
        cout << "Player " << 1 + pvpGame.currentTurn << "'s turn" << endl;
        if (moveStartTime != loopStartTime) {
          cout << "The last player took " << difftime(time(0), moveStartTime)
               << " seconds." << endl;
        }
        cout << "Enter where you would like to go in \"row, column\" format!"
             << endl;
        string theMove;
        getline(cin, theMove);
        system("clear");
        splitInput = split(theMove, ',');
        if (splitInput.size() > 1) {
          try {
            x = stoi(splitInput[0]);
            y = stoi(splitInput[1]);

            acceptedInput = true;
          } catch (exception &err) {
            cout << "Please enter a valid input!" << endl;
          }
        } else {
          cout << "Please enter a valid input!" << endl;
        }
      }
      moveStartTime = time(0);
      pvpGame.play(x, y);
      if (pvpGame.done == true) {
        gameActive = false;
        if (pvpGame.hasWon(0)) {
          cout << pvpGame << endl;
          cout << "Player " << 1 << " has won!";
        } else if (pvpGame.hasWon(1)) {
          cout << pvpGame << endl;
          cout << "Player " << 2 << " has won!";
        } else {
          cout << "It is a draw." << endl;
        }
        points(gameActive, pvpGame.hasWon(0), "player1");
        points(gameActive, pvpGame.hasWon(1), "player2");
      }
    }
    cout << "The game took a combined " << difftime(time(0), loopStartTime)
         << " seconds." << endl;
  }
}

void EasyAi(int sizeBoard, bool gameActive) {
  system("clear");
  if (sizeBoard < 1) {
    cout << "Error. Enter a valid input";
  } else {
    GameState pveEasyGame(sizeBoard);
    string temp;
    int playerNum;
    // ask if player wants to go first
    cout << "Would you like to be player 1 or 2? (1 or 2)" << endl;
    cin >> playerNum;
    system("clear");
    if (playerNum == 2) {
      pveEasyGame = EnemyPlayRandomMove(pveEasyGame);
      system("clear");
    }
    getline(cin, temp);
    time_t loopStartTime = time(0);
    time_t moveStartTime = loopStartTime;
    while (gameActive) {
      bool acceptedInput = false;
      vector<string> splitInput;
      int x;
      int y;

      while (!acceptedInput) {
        cout << pveEasyGame << endl;
        cout << "Your turn!" << endl;
        if (moveStartTime != loopStartTime) {
          cout << "The last player took " << difftime(time(0), moveStartTime)
               << " seconds." << endl;
        }
        cout << "Enter where you would like to go in \"row, column\" format!"
             << endl;
        string theMove;
        getline(cin, theMove);
        system("clear");
        splitInput = split(theMove, ',');
        if (splitInput.size() > 1) {
          try {
            x = stoi(splitInput[0]);
            y = stoi(splitInput[1]);

            acceptedInput = true;
          } catch (exception &err) {
            cout << "Please enter a valid input!" << endl;
          }
        } else {
          cout << "Please enter a valid input!" << endl;
        }
      }
      moveStartTime = time(0);
      pveEasyGame.play(x, y);
      if (pveEasyGame.done == true) {
        gameActive = false;
        if (pveEasyGame.hasWon(1)) {
          system("clear");
          cout << pveEasyGame << endl;
          cout << "Player 2 has won!" << endl;
        } else if (pveEasyGame.hasWon(0)) {
          system("clear");
          cout << pveEasyGame << endl;
          cout << "Player 1 has won!" << endl;
        } else {
          system("clear");
          cout << "It is a draw." << endl;
        }
      }
      if (pveEasyGame.turnCount % 2 == (playerNum) % 2) {
        if (pveEasyGame.done == false) {
          pveEasyGame = EnemyPlayRandomMove(pveEasyGame);
        } else if (pveEasyGame.hasWon(1)) {
          gameActive = false;
          system("clear");
          cout << pveEasyGame << endl;
          cout << "Player 2 has won!";
        } else if (pveEasyGame.hasWon(0)) {
        } else {
          gameActive = false;
          system("clear");
          cout << "It is a draw." << endl;
        }
        if (pveEasyGame.hasWon(1)) {
          gameActive = false;
          system("clear");
          cout << pveEasyGame << endl;
          cout << "Player 2 has won!" << endl;
        }
        if (pveEasyGame.hasWon(0)) {
          gameActive = false;
          system("clear");
          cout << pveEasyGame << endl;
          cout << "Player 1 has won!" << endl;
        }
      }
      points(gameActive, pveEasyGame.hasWon(0), "Easyplayer1");
      points(gameActive, pveEasyGame.hasWon(1), "Easyplayer2");
    }
    cout << "The game took a combined " << difftime(time(0), loopStartTime)
         << " seconds." << endl;
  }
}
void HardAi(int sizeBoard, bool gameActive) {
  system("clear");
  if (sizeBoard < 1) {
    cout << "Error. Enter a valid input";
  } else {
    GameState pveHardGame(sizeBoard);
    string temp;
    int playerNum;
    // ask if player wants to go first
    cout << "Would you like to player 1 or 2? (1 or 2)" << endl;
    cin >> playerNum;
    system("clear");
    if (playerNum == 2) {
      pveHardGame = EnemyPlayBestMove(pveHardGame);
      system("clear");
    }
    getline(cin, temp);
    time_t loopStartTime = time(0);
    time_t moveStartTime = loopStartTime;
    while (gameActive) {
      bool acceptedInput = false;
      vector<string> splitInput;
      int x;
      int y;

      while (!acceptedInput) {
        cout << pveHardGame << endl;
        cout << "Your turn! EXETREME VERSION" << endl;
        if (moveStartTime != loopStartTime) {
          cout << "The last player took " << difftime(time(0), moveStartTime)
               << " seconds." << endl;
        }
        cout << "Enter where you would like to go in \"row, column\" format!"
             << endl;
        string theMove;
        getline(cin, theMove);
        splitInput = split(theMove, ',');
        if (splitInput.size() > 1) {
          try {
            x = stoi(splitInput[0]);
            y = stoi(splitInput[1]);

            acceptedInput = true;
          } catch (exception &err) {
            cout << "Please enter a valid input!" << endl;
          }
        } else {
          cout << "Please enter a valid input!" << endl;
        }
      }
      moveStartTime = time(0);
      pveHardGame.play(x, y);
      // std::cout << "NO SEGEMENTATION FAULT HERE.";
      if (pveHardGame.done == true) {
        system("clear");
        gameActive = false;
        if (pveHardGame.hasWon(1)) {
          cout << pveHardGame << endl;
          cout << "Player 2 has won!" << endl;
        } else if (pveHardGame.hasWon(0)) {
          cout << pveHardGame << endl;
          cout << "Player 1 has won!" << endl;
        } else {
          cout << "It is a draw." << endl;
        }
      }
      // std::cout << "NO SEGEMENTATION FAULT HERE.";
      if (pveHardGame.turnCount % 2 == (playerNum) % 2) {
        if (pveHardGame.done == false) {
          pveHardGame = EnemyPlayBestMove(pveHardGame);
          system("clear");
        } else if (pveHardGame.hasWon(1)) {
          system("clear");
          gameActive = false;
          cout << pveHardGame << endl;
          cout << "Player 2 has won!" << endl;
        } else if (pveHardGame.hasWon(0)) {
          system("clear");
          gameActive = false;
          cout << pveHardGame << endl;
          cout << "Player 1 has won!" << endl;
        } else {
          system("clear");
          cout << "It is a draw." << endl;
          gameActive = false;
        }
        if (pveHardGame.hasWon(1)) {
          system("clear");
          gameActive = false;
          cout << pveHardGame << endl;
          cout << "Player 2 has won!" << endl;
        }
        if (pveHardGame.hasWon(0)) {
          system("clear");
          gameActive = false;
          cout << pveHardGame << endl;
          cout << "Player 1 has won!" << endl;
        }
        points(gameActive, pveHardGame.hasWon(0), "HardPlayer1");
        points(gameActive, pveHardGame.hasWon(1), "HardPlayer2");
      }
    }
    cout << "The game took a combined " << difftime(time(0), loopStartTime)
         << " seconds." << endl;
  }
}

#endif
