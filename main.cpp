#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Manager.h"

using namespace std;

int main() 
{
  Manager mgr;
  string choice;
  //int cash = 0;
  int replay = 0;

  mgr.loadFromFile(); // mgr.initializeTeam();
  mgr.loadHighScore(); // mgr.initializeHighScore()
  mgr.startshowTeam(); // show teams available to choose

  // get user input on team to choose
  cout << "\nChoose a National Team to start: ";
  cin >> choice;

  // loop if user choice is not in the list
  while (!mgr.teamSelect(choice)) 
  {
    cout << "\033[2J\033[1;1H"; // clear console
    cout << "** There is no such Team! **" << endl << endl; // show error
    mgr.startshowTeam(); // show teams avail again
    cout << "\nChoose a National Team to start: "; // get user input on team to choose
    cin >> choice;
  }

  cout << "\033[2J\033[1;1H"; // clear console

  // confirmation of choice
  cout << "You have chosen " << choice
       << " as your starting team. Do you wish to proceed or choose another "
          "team? \n(Proceed: 0 || Change team: 1)\n"; // get user input on confirmation of choice
  cin >> replay;

  // loop if user choice is not 0 or 1
  while (replay > 1 || replay < 0) {
    cout << "\033[2J\033[1;1H"; // clear console
    cout << "Invalid choice!" << endl << endl; // show error
    cout << "You have chosen " << choice
         << " as your starting team. Do you wish to proceed or choose another "
            "team? \n(Proceed: 0 || Change team: 1)\n"; // get user input on confirmation of choice
    cin >> replay;
    cout << "\033[2J\033[1;1H"; // clear console
  }

  replay = 0; // reset replay to 0

  cout << "You have $1000 to start betting to get the highest score! Good "
          "Luck!\n"
       << endl;
  cout << "Double your score if your team wins the World Cup!!\n" << endl;

  // run quaterfinals 
  cout << "\n--------QUARTER FINAL--------\n" << endl;
  mgr.qFinal();

  // run semifinals
  cout << "\n---------SEMI FINAL---------\n" << endl;
  mgr.sFinal();

  // run finals
  cout << "\n-----------FINAL-----------\n" << endl;
  mgr.Final();

  // check if final score makes it to the top 10 highscores
  mgr.checkHighScores();

  // end of game, check if replay or end program
  cout << "Thank you for playing!\n"
       << "To replay, enter 0 || To exit, enter 1" << endl;
  cin >> replay;

  // loop if user choice is not 0 or 1
  while (replay > 1 || replay < 0) {
    cout << "\033[2J\033[1;1H"; // clear console
    cout << "Invalid choice!" << endl << endl;
    cout << "Thank you for playing!\n"
         << "To replay, enter 0 || To exit, enter 1" << endl;
    cin >> replay;
    cout << "\033[2J\033[1;1H"; // clear console
  }

  // if user selects 0, run codes from beginning 
  if (replay == 0) {
    cout << "\033[2J\033[1;1H"; // clear console
    main();
  }

  // else, clear screen and display good bye 
  cout << "\033[2J\033[1;1H"; // clear console
  cout << "Thank you for playing...\nGood Bye";

  return 0;
}