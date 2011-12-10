#ifndef _PLAYER__
#define _PLAYER__
class Player
{
      private:
      double x, y;
      int lives;
      int score;
      int bombs;
      int power;
      int sprite;
      bool invincible;
      double radius;
      double speed;
      double recoila;
      double recoilb;
      
      
      public:
      Player();
      ~Player();
      int invincibletime;
      int invinciblesprite;
      double xvel;
      double yvel;
      
      
      double getX();
      void setX(double newx);
      
      double getY();
      void setY(double newy);
      
      int getLives();
      void setLives(int newlives);
      
      int getScore();
      void setScore(int newscore);
      
      int getBombs();
      void setBombs(int newbombs);
      
      int getPower();
      void setPower(int newpower);
      
      int getSprite();
      void setSprite(int newsprite);
      
      bool getInvincible();
      void setInvincible(bool newinvincible); 
      
      double getRadius();
      void setRadius(double newradius);
      
      double getSpeed();
      void setSpeed(double newspeed);
      
      double getRecoilA();
      void setRecoilA(double newrecoila);
      
      double getRecoilB();
      void setRecoilB(double newrecoilb);
};
#endif
