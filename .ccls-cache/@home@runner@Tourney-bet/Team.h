#ifndef TEAM_H
#define TEAM_H

#include <string>


class Team {
public:
  Team();
  Team(std::string);
  Team(std::string, int);

  ~Team();

  void setTeamName(std::string);
  void setRanking(int);
  void setTeamPlacement(int);

  std::string getTeamName();
  int getTeamPlacement();
  int getRanking();
  void printTeamInfo();

  // Assignment operator overload:
  Team & operator=(const Team &);
  Team & operator=(const Team* );

private:
  std::string TeamName_;
  int Rank_;
  int teamPlacement_;
};

#endif