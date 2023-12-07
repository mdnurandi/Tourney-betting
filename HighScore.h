#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>

class HighScore {
public:
  HighScore();
  HighScore(std::string name);
  HighScore(std::string, int);
  ~HighScore();

  void setName(std::string name)
  {
    name = Names;
  }
  void setHighScore(int score)
  {
    score=highScore;
  }
  void setHS_Placement(int placement)
  {
    placement = HS_Placement;
  }

  std::string getName()
  {
    return Names;
  }
  int getHighScore()
  {
    return highScore;
  }
  int getHS_Placement()
  {
    return HS_Placement;
  }

  void printScoreInfo();

private:
  std::string Names;
  int highScore;
  int HS_Placement;
};

#endif