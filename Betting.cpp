#include <iostream>
#include <vector>
#include <math.h>

#include "Betting.h"
#include "Match.h"
#include "Manager.h"

using namespace std;

//  Default constructor:
Betting::Betting()
{
  odds_Home = 1.0;
  odds_Away = 1.0;
}

Betting::Betting(Match* game)
{
  BettingMatch = game;
}

// Destructor:
Betting::~Betting()
{
  // cout << "\nThe bet destructor was called" << endl;
}

//  To start betting
void Betting::startBet(Match * game , float wallet)
{
  //  Calculate the odds for home and away teams using their probability
  //  odd = 1 + 
  odds_Home = 1.0 + (game->getAwayProbability() / (game->getHomeProbability()));
  odds_Away = 1.0 + (game->getHomeProbability() / (game->getAwayProbability()));

  //  However, if wallet balance is $0, the user is unable to make a bet due to insufficient funds
  if (wallet == 0)
  {
    cout << "\033[31m" << "Insufficient Funds to Bet!!\n" << "\033[0m" << endl;
    betAmount = 0.0;  //  Fixing the bet amount to 0
    return;
  }

  bool success;
  do 
  {
    //  To let the user choose between the teams in the match to bet on while showing the odds of winning
    success = true;
    cout << game->get_myTeam().getTeamName() << " is playing against " << game->get_Opponent().getTeamName() << endl;
    cout << "Odds are: " << odds_Home << "   :   " << odds_Away << endl;
    cout << "\nWho are you betting on?: ";
    cin >> bet_TeamName;

    //  If there is no matching team name in the match, the program will prompt again
    if (bet_TeamName != game->get_myTeam().getTeamName() && bet_TeamName != game->get_Opponent().getTeamName())
    {
      cout <<  "\nERROR: No such team in this match!!\n" << endl;
      success = false;
    }
   //  Therefore, the do-while loop will continue as long as the user chooses the correct team
  }while (!success);

  do
  {
    //  After choosing a team to bet, ...
    //  an amount to bet must be selected by the player
    success = true;
    cout << "How much are you betting?: $";
    cin >> betAmount;

    //  This is to prevent the player to bet more than the wallet amount ...
    //  and to prevent the player to bet a negetive amount
    if (wallet - betAmount < 0 || betAmount < 0)
    {
        cout <<  "\nERROR: Insufficient wallet ($" << wallet << ") amount!!\n" << endl;
        success = false;
    }

  //  Do-While loop will continue as long as the correct input is selected
  }while(!success);

  cout << endl;

  return;
}

float Betting::getodds_Home()
{
  return odds_Home;  
}

float Betting::getodds_Away()
{
  return odds_Away;
}

float Betting::getProfits(string name)
{
  //  This is to check which team the player betted on
  if (name == BettingMatch.get_myTeam().getTeamName())
    return betAmount*odds_Home; //  Whether it is the home team...
  return betAmount*odds_Away;  // or the away team as the winning amount would ...
                              //  would be different
}

float Betting::getBetAmount()
{
  return betAmount;
}

string Betting::getBet_TeamName()
{
  return bet_TeamName;
}