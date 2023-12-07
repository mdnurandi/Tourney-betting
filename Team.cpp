#include "Team.h"
#include "Manager.h"
#include <iostream>

using namespace std;

// default constructor
Team::Team()
{
  setTeamName("");
  setRanking(0);
  setTeamPlacement(0);
}

Team::Team(string name) 
{ 
  setTeamName(name); 
  setRanking(0);
  setTeamPlacement(0);
}

Team::Team(string name, int num) : TeamName_{name}, Rank_{num}
{
  setTeamPlacement(0);
}

// destructor
Team::~Team() {}

void Team::setTeamName(string name) 
{ 
  TeamName_ = name; 
}

void Team::setRanking(int num) 
{ 
  Rank_ = num;
}

string Team::getTeamName() 
{ 
  return TeamName_; 
}

int Team::getRanking()
{ 
  return Rank_;
}

void Team::printTeamInfo() 
{ 
  cout << TeamName_ << endl; 
}

Team & Team::operator=(const Team & copy)
{
  if (this != &copy)
  {
    this->setTeamName(copy.TeamName_);
    this->setRanking(copy.Rank_);
    this->setTeamPlacement(copy.teamPlacement_);
  }  
  return *this;
}

void Team::setTeamPlacement(int placement)
{
  teamPlacement_ = placement;
}

int Team::getTeamPlacement()
{
  return teamPlacement_;
}

Team & Team::operator=(const Team* copy)
{
  this->setTeamName(copy->TeamName_);
  this->setRanking(copy->Rank_);
  this->setTeamPlacement(copy->teamPlacement_);

  return *this;
}