#ifndef _PLAYER__
#define _PLAYER__

#include "lua.hpp"
class Player
{
      private:
      double x, y;
      int lives;
      int score;
      int bombs;
      int power;
      int sprite1;
      int sprite2;
      int spriteinvincible;
      int bgsprite;
      bool invincible;
      double radius;
      double speed;
      double recoila;
      double recoilb;
      double rotation;
      double rotationspeed;
      double rotationmax;
      
      
      public:
      Player(char* charfile);
      ~Player();
      int invincibletime;
      //int invinciblesprite;
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
      
      //int getSprite();
      //void setSprite(int newsprite);
      
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
      
      double getRotation();
      void setRotation(double newroation);

      double getRotationSpeed();
      void setRotationSpeed(double newrotationspeed);

      double getRotationMax();
      void setRotationMax(double newrotationmax);
      
      int getSprite1();
      int getSprite2();
      int getSpriteInvincible();
      int getBGSprite();
      
      static int l_setSprite1( lua_State* luaVM);
      static int l_setSprite2( lua_State* luaVM);
      static int l_setSpriteInvincible( lua_State* luaVM);
      static int l_setBGSprite( lua_State* luaVM);
      
};
#endif
