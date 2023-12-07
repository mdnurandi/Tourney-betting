#include "HighScore.h"
#include "Manager.h"
#include <iostream>
#include <iomanip>

using namespace std;

// default constructor
HighScore::HighScore()
{
  setName("");
  setHighScore(0);
  setHS_Placement(0);
}

HighScore::HighScore(string name) 
{ 
  setName(name); 
  setHighScore(0);
  setHS_Placement(0);
}

HighScore::HighScore(string name, int num) : Names{name}, highScore{num}
{
  setHS_Placement(0);
}

// destructor
HighScore::~HighScore() {}

void HighScore::printScoreInfo() 
{ 
  cout << setw(10) << Names << ": " << highScore << endl; 
}