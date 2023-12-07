#ifndef BETTING_H
#define BETTING_H

#include "Match.h"

class Betting : public Match{
public:
  Betting();
  Betting(Match*);
  ~Betting();

  float getodds_Home();
  float getodds_Away();

  void startBet(Match* , float);
  std::string getBet_TeamName();
  float getProfits(std::string);
  float getBetAmount();

private:
  float betAmount;
  float odds_Home;
  float odds_Away;
  //float profit;
  Match BettingMatch;
  std::string bet_TeamName;
};


#endif