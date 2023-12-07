// Prevent multiple inclusion:
#ifndef MANAGER_H
#define MANAGER_H

#include "Team.h"
#include "Match.h"
#include "Betting.h"
#include "HighScore.h"
#include <vector>
#include <map>

class Manager {
public:
  Manager();
  ~Manager();

  void loadFromFile();
  void writeFile();
  void deleteHS();
  void loadHighScore();
  void showHighScores();

  template <typename T>
  void sort_Vector_Dec(std::vector<T> &);
  template <typename T>
  void shuffleList(std::vector<T> &);

  void showTeam();
  int searchTeam(std::string , std::vector<Team>& );
  void startshowTeam();
  bool teamSelect(std::string);
  void checkHighScores();

  float CheckElimination(std::vector<Team> & , Betting &);
  void Eliminate(Team);

  void qFinal();
  void sFinal();
  void Final();
  void startMatches(std::vector<Match*> );

  void setWallet(float amount)
  {
    wallet = amount;
  }

  int getWallet()
  {
    return wallet;
  }

protected:
  float wallet = 1000.00;

private:
  std::vector<Team> TeamList_;
  std::vector<Team> TeamListlost_;
  std::vector<Team> TeamDiscard_;
  std::vector<HighScore> HighScore_;
  std::vector<HighScore> T10HighScore_;
  std::vector<Match*> Matches;
  std::vector<size_t> results;
  Team teamSelected;
  int teamPlace;
};

#endif // MANAGER_H