#include <cstdlib>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <stdlib.h>

#include "Team.h"
#include "Manager.h"
#include "Match.h"
#include "Betting.h"

using namespace std;

int getRandomNumber(int , int); // initialise to get random numbers

//  Default constructor:
Manager::Manager() {}

//  Destructor:
Manager::~Manager() {}

// retrieve the World Cup csv file into the program
void Manager::loadFromFile()
{
  string line, word;

  fstream file("WorldCup.csv", ios::in);
  if (file.is_open()) 
  {
    while (getline(file, line)) 
    {
      stringstream str(line);

      std::string countryName = "";
      int countryScore = 0;
      size_t count = 0; // keep track of token count

      while (getline(str, word, ',')) 
      {
        if (count == 0) // 0 Means its reading country now
          countryName = word;
        else if (count == 1) // 1 means its reading the score now
        { 
          // read score = end of line = u got all the required info
          countryScore = std::stoi(word); // convert string to int

          // create Team here and push into container
          TeamList_.push_back(Team(countryName, countryScore));
          count = 0;
        }
        count++;
      }
    }
  }
  else
    cout << "Could not open the file\n";
}

// retrieve the current Highscore csv file
void Manager::loadHighScore()
{
  string line, word;

  fstream file("HighScore.csv", ios::in);
  if (file.is_open()) 
  {
    while (getline(file, line)) 
    {
      stringstream str(line);

      std::string hsName = "";
      int hsScore = 0;
      size_t count = 0; // keep track of token count


      while (getline(str, word, ',')) 
      {
        if (count == 0) // 0 Means its reading country now
          hsName = word;
        else if (count == 1) // 1 means its reading the score now
        { 
          // read score = end of line = u got all the required info
          hsScore = std::stoi(word); // convert string to int

          // create highscore and push into container
          HighScore_.push_back(HighScore(hsName, hsScore));
          count = 0;
        }
        count++;
      }
    }
  }
  else
    cout << "Could not open the file\n";
}

// uploading the updated Highscore board onto the csv file
void Manager::writeFile()
{
    // create an output filestream object
    std::ofstream highscorefile("HighScore.csv");

    // send data to the stream
    for (HighScore HighScore : HighScore_)
    {
        // write the data to the output file
        highscorefile << HighScore.getName() << ", " << HighScore.getHighScore() << endl;
    }

    // close the file
    highscorefile.close();
}

// // delete all elements in file
// void Manager::deleteHS()
// {
//   std::ofstream ofs;
//   ofs.open("HighScore.csv", std::ofstream::out | std::ofstream::trunc);
//   ofs.close();
// }

// Updating the Highscore board for the console
void Manager::checkHighScores()
{
  const unsigned displayLimit = 10; // set max limit for num of rows in the vector to 10
  string username = "";
  int counter=0;

  // check if user highscore is larger than any value in current highscore
  for (HighScore HighScore : HighScore_)
  {
    if (wallet>HighScore.getHighScore())
      counter++; // if it is higher than a highscore, counter will increase
  }

  // if counter is higher than 0 (means user score is higher than current than highscore), then add it to highscore list, sort depending on score number, delete last line (if list hasnt reached 10 names) and write to highscore.csv
  if (counter>0)
  {
    //deleteHS();
    cout << "\n\nCongratulations! You are in the top 10!";
    cout << "\nPlease Enter your name: ";
    cin >> username; // get user name
    HighScore_.push_back(HighScore(username, wallet)); // add user name and score to HighScore vector

    sort_Vector_Dec(HighScore_); // sort highscore list in decending of score

    // if list is larger than 10 rows, delete last line
    if (HighScore_.size()>displayLimit)
    {
      HighScore_.pop_back();
    }

    writeFile(); // write highscore vector to highscore.csv
    showHighScores(); // show highscores
  }
  else 
    showHighScores(); // show highscores
}

//  To display the updated Highscore board onto the console
void Manager::showHighScores()
{
  cout << "Highscores: \n" << endl;
  int colour = 0;
  for (HighScore HighScore : HighScore_)
  {
    if (colour == 0)
      cout << "\033[93m";
    else if (colour == 1)
      cout << "\033[90m";
    else if (colour == 2)
      cout << "\033[33m";
    HighScore.printScoreInfo();

    cout << "\033[0m";
    colour++;
  }
  cout << endl;
}

//  Start the program by displaying all the teams that are available to be picked
void Manager::startshowTeam()
{
  cout << "Available Teams: \n" << endl;
  for (Team Team : TeamList_)
  {
    Team.printTeamInfo();
  }
  cout << endl;
}

//  Subsequently, this diplays not only the availble teams, it also shows the eliminated teams
void Manager::showTeam()
{
  //  Start by printing the available teams first...
  cout << "Available: " << endl;
  for (Team Team : TeamList_)
  {
    Team.printTeamInfo();
  }
  cout << endl;

  //  then continue to print the teams that are eliminated in red.
  cout << "\033[31m" << "Eliminated:" << endl;

  //  Comparing to the vector which includes all the team that has lost
  for (Team team : TeamListlost_)  
  {
    team.printTeamInfo();
  }
  cout << "\033[0m"; // Resetting the font colour to the original
  cout << endl;
}

//  Returns the position of a specific team in the vector
int Manager::searchTeam(string name, vector<Team>& List)
{
  int vectorPlacement = 0;
  for (Team team : List) // Search thoughout the whole vector
  {
    //  If the name of the team in the list is the same, return the position
    if (name == team.getTeamName())  
      return vectorPlacement; //  returns the position (int)

    vectorPlacement++;
  }

  //  Use the value -1 to represent that there is no such team in the list
  vectorPlacement = -1; 
  return vectorPlacement; // Returns -1 if the team is not found in the list
}

//  Initialise the objects according to the team selected
bool Manager::teamSelect(string name)
{
  bool success = false;

  shuffleList(TeamList_);  //  This is to shuffle the TeamList_ so that the matches would be random
  //showTeam();  //  Displays all the 
  teamPlace = searchTeam(name, TeamList_);

  if (teamPlace != -1)
  {
    TeamList_[teamPlace].printTeamInfo();
    teamSelected = TeamList_[teamPlace];
    success = true;
  }
  cout << teamPlace;

  return success;
}

void Manager::qFinal()
{
  int counter = 0;
  int bet = 0;
  Matches.clear();
  for (int i = 0; i < TeamList_.size() / 2; i++)
  {
    Matches.push_back(new Match(TeamList_[counter], TeamList_[counter + 1]));

    if (TeamList_[counter].getTeamName() == teamSelected.getTeamName() || TeamList_[counter + 1].getTeamName() == teamSelected.getTeamName())
    {
      bet = i;
    }
    counter += 2;
  }

  Betting Game(Matches[bet]);    // Creating a bet on the match
  Game.startBet(Matches[bet] , wallet);  

  startMatches(Matches);    // To start the matches in the quater final
  showTeam();
  wallet += CheckElimination(TeamList_, Game);
  cout << "Your current wallet balance is: $" << "\033[92m" << wallet << "\033[0m" << endl;

  return;
}

void Manager::sFinal()
{
  Matches.clear();
  int counter = 0;
  int bet = -1;
  for (int i = 0; i < TeamList_.size() / 2; i++)
  {
    Matches.push_back(new Match(TeamList_[counter], TeamList_[counter + 1]));
    if (TeamList_[counter].getTeamName() == teamSelected.getTeamName() || TeamList_[counter + 1].getTeamName() == teamSelected.getTeamName())
    {
      bet = i;
    }
    else if ((i == TeamList_.size()/2 - 1) && (bet == -1))
    {
      //  Randomly selects match to bet if the original team selected was eliminated
      bet = getRandomNumber(0, (TeamList_.size() / 2) - 1);
    }
    counter += 2;
  }

  Betting Game(Matches[bet]);
  Game.startBet(Matches[bet] , wallet);

  startMatches(Matches); 
  showTeam();
  wallet += CheckElimination(TeamList_, Game);
  cout << "Your current wallet balance is: $" << "\033[92m" << wallet << "\033[0m" << endl;
}

void Manager::Final()
{
  Matches.clear();
  Matches.push_back(new Match(TeamList_[0], TeamList_[1]));

  Betting Game(Matches[0]);
  Game.startBet(Matches[0] , wallet);
  Matches[0]->startMatch();
  Eliminate(Matches[0]->getLoser());
  wallet += CheckElimination(TeamList_, Game);

  cout << "\n!!Winner of the World Cup 2022 is : " << "\033[93m" << Matches[0]->getWinner().getTeamName() << "\n" << "\033[0m" << endl;
  if (Matches[0]->getWinner().getTeamName() == teamSelected.getTeamName())
  {
    cout << "Congratulations!! Your team has won the 2022 World Cup!!\n" << endl;
    wallet *= 2.0;
  }
  cout << "Your current wallet balance is: $" << "\033[92m" << wallet << "\033[0m" << endl;
}

void Manager::startMatches(vector<Match*> Games)
{
    for (Match* game : Games)
  {
    game->startMatch();
    cout << "Winner: " << game->getWinner().getTeamName() << "\n" << endl;
    Eliminate(game->getLoser());
  }
}

float Manager::CheckElimination(vector<Team>& List , Betting & Bet)
{
  for (Team teams : List)
  {
    if (teams.getTeamName() == Bet.getBet_TeamName())
      return Bet.getProfits(Bet.getBet_TeamName());
  }
  cout << "You lost your bet!!" << endl;
  return -Bet.getBetAmount();
}

void Manager::Eliminate(Team loser)
{
  Team loserTeam = loser;
  //int placement = loser.getTeamPlacement();
  int counter = 0;
  TeamListlost_.push_back(loserTeam);

  for (Team check : TeamList_)
  {
    if (loser.getTeamName() == check.getTeamName())
      TeamList_.erase(TeamList_.begin() + counter);

    counter++;
  }
}

template <typename T>
 void Manager::sort_Vector_Dec(std::vector<T> & List)
{
   sort(List.begin() , List.end() , [](T& lhs , T& rhs){
     return lhs.getHighScore() > rhs.getHighScore();});
}

template <typename T>
void Manager::shuffleList(vector<T> & List)
{
  random_device rd;
  std::shuffle(List.begin(), List.end(), rd);
  // cout << "Shuffle is called here\n";
}

int getRandomNumber(int min , int max)
{
  random_device rd;
  uniform_int_distribution<int> dist(min , max);
  return dist(rd);
}