#include <iostream>
#include <random>

#include "Team.h"
#include "Match.h"
#include "Betting.h"

#define PROBABILITY 10.0

using namespace std;

Match::Match()
{
  myTeam = Team();
  Opponent = Team();
  myTeam_Probability = 0;
  Opponent_Probability = 0;
}

Match::Match(Team & team1 , Team & team2)
{
  myTeam = team1;
  Opponent = team2;
  findProbability(team1.getRanking(), team2.getRanking());
}

Match::Match(Match & game)
{
  myTeam = game.get_myTeam();
  Opponent = game.get_Opponent();
}

Match::~Match()
{
}

void Match::startMatch()
{
  printMatch(myTeam.getTeamName() , Opponent.getTeamName());// 
  random_device rd;
  uniform_int_distribution<int> dist(1,PROBABILITY);
  int winningNum = dist(rd);
  // cout << "\nThe winning number was: " << winningNum << endl;
  if (winningNum >= myTeam_Probability)
  {
    Winner = Opponent;
    Loser = myTeam;
  }
  else
  {
    Winner = myTeam;
    Loser = Opponent;
  }
}

Team Match::getWinner()
{
  return Winner;
}

Team Match::getLoser()
{
  return Loser;
}
void Match::printMatch(string Team1 , string Team2)
{
  cout << Team1 << " VS " << Team2 << endl;
}

void Match::findProbability(int myTeam_rank , int Opponent_rank)
{
  //  Probability = 10 - (team1 / (team1 + team2)) x 10
  myTeam_Probability = PROBABILITY - ((float)(myTeam_rank * PROBABILITY) / (myTeam_rank + Opponent_rank));
  Opponent_Probability = PROBABILITY - myTeam_Probability;
  // cout << "Probabilities:\n" << "\tHome: " << myTeam_Probability << "\tAway: " << Opponent_Probability << endl;
  // cout << "\nRankings:\n" << "\tMy Team: " << myTeam_rank << "\tOpponent: " << Opponent_rank << endl;
}

float Match::getHomeProbability()
{
  return myTeam_Probability;
}

float Match::getAwayProbability()
{
  return Opponent_Probability;
}
Team Match::get_myTeam() const
{
  return myTeam;
}

Team Match::get_Opponent() const
{
  return Opponent;
}

Match & Match::operator=(const Match* copy)
{
  this->myTeam = copy->get_myTeam();
  this->Opponent = copy->get_Opponent();

  return *this;
}