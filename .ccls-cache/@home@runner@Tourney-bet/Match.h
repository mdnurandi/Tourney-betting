#ifndef MATCH_H
#define MATCH_H

#include "Team.h"
#include <vector>
#include <string>

class Match {
public:
  Match();
  Match(Team & , Team &);
  Match(Match &);
  ~Match();

  void printMatch(std::string , std::string);
  void startMatch();

  void findProbability(int , int);
  float getHomeProbability();
  float getAwayProbability();

  Team getWinner();
  Team getLoser();
  Team get_myTeam() const;
  Team get_Opponent() const;

  Match & operator=(const Match* );  

private:
  Team myTeam;
  Team Opponent;
  Team Winner;
  Team Loser;
  float myTeam_Probability;
  float Opponent_Probability;
};

#endif