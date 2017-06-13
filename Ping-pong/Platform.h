#ifndef H_PLATFORM
#define H_PLATFORM

class Platform {
 public:
  int getlength() const { return length; };
  void setlength(int x);
  int getxCoordinate() const { return xCoordinate; };
  void setxCoordinate(int x);

 protected:
  int length;
  int xCoordinate;
};

class PlatformPlayer : public Platform  // Дочерний класс игрока/игроков
{
 public:
  PlatformPlayer(int length, int yCoordinate);
  void MoveUp();
  void MoveDown(int x_playing_field);
};
class PlatformAI : public Platform  // Дочерний класс ИИ
{
 protected:
  int difficulty;

 public:
  PlatformAI(int length, int yCoordinate, int difficulty);
  void SetDifficulty(int difficulty);
  int Move(int x_playing_field, int y_playing_field, int BallX, int BallY);
};
#endif