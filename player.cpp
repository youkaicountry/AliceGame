#include "player.h"
#include "lua.hpp"

Player::Player(char* charfile)
{
    x = 250;
    y = 550;
    lives = 3;
    bombs = 3;
    score = 0;
    power = 0;
    //sprite = 1;
    invincible = false;
    radius = 4;
    speed = 4;
    recoila = 0;
    recoilb = 0;
    invincibletime = 0;
    //invinciblesprite = 9;
    xvel = 0;
    yvel = 0;
    rotation = 0;
    rotationspeed = 1.8;
    rotationmax = 10;
    lua_State* LStat = luaL_newstate();
    luaL_openlibs(LStat);


   //loadLuaLib("lib", LStat);

   int s = luaL_loadfile(LStat, charfile);

   //TreeTexture::registerOperations(LStat);

   //WAYPOINT STUFF
   lua_pushstring(LStat, "setSprite1");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setSprite1, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "setSprite2");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setSprite2, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "setSpriteInvincible");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setSpriteInvincible, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "setBGSprite");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setBGSprite, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);

    s = lua_pcall(LStat, 0, 0, 0);

   lua_getfield(LStat, LUA_GLOBALSINDEX, "setupPlayer");          /* function to be called */
   lua_pushnumber(LStat, 69);
   lua_pcall(LStat, 1, LUA_MULTRET, 0);
    
    return;
}

Player::~Player()
{
    return;
}

double Player::getX()
{
    return x;
}

void Player::setX(double newx)
{
    x = newx;
    return;
}

double Player::getY()
{
    return y;
}

void Player::setY(double newy)
{
    y = newy;
    return;
}

int Player::getLives()
{
    return lives;
}

void Player::setLives(int newlives)
{
    lives = newlives;
    return;
}

int Player::getScore()
{
    return score;
}

void Player::setScore(int newscore)
{
    score = newscore;
    return;
}

int Player::getBombs()
{
    return bombs;
}

void Player::setBombs(int newbombs)
{
    bombs = newbombs;
    return;
}

int Player::getPower()
{
    return power;
}

void Player::setPower(int newpower)
{
    power = newpower;
    return;
}

//int Player::getSprite()
//{
//    return sprite;
//}

//void Player::setSprite(int newsprite)
//{
 //   sprite = newsprite;
 //   return;
//}

bool Player::getInvincible()
{
    return invincible;
}

void Player::setInvincible(bool newinvincible)
{
    invincible = newinvincible;
    return;
}

double Player::getRadius()
{
    return radius;
}

void Player::setRadius(double newradius)
{
    radius = newradius;
    return;
}

double Player::getSpeed()
{
    return speed;
}

void Player::setSpeed(double newspeed)
{
    speed = newspeed;
    return;
}

double Player::getRecoilA()
{
    return recoila;
}

void Player::setRecoilA(double newrecoila)
{
    recoila = newrecoila;
    return;
}

double Player::getRecoilB()
{
    return recoilb;
}

void Player::setRecoilB(double newrecoilb)
{
    recoilb = newrecoilb;
    return;
}

double Player::getRotation()
{
    return rotation;
}

void Player::setRotation(double newrotation)
{
    rotation = newrotation;
    return;
}

double Player::getRotationSpeed()
{
    return rotationspeed;
}

void Player::setRotationSpeed(double newrotationspeed)
{
    rotationspeed = newrotationspeed;
    return;
}

double Player::getRotationMax()
{
    return rotationmax;
}

void Player::setRotationMax(double newrotationmax)
{
    rotationmax = newrotationmax;
    return;
}

int Player::getSprite1()
{
   return this->sprite1;
}

int Player::getSprite2()
{
   return this->sprite2;
}

int Player::getSpriteInvincible()
{
   return this->spriteinvincible;
}

int Player::getBGSprite()
{
   return this->bgsprite;
}

int Player::l_setSprite1( lua_State* luaVM)
{
   Player* pl = (Player*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int sp1 = (int) lua_tonumber(luaVM, -1); //handle 2
   pl->sprite1 = sp1;
   lua_pushnumber(luaVM, 1);
   return 1;
}

int Player::l_setSprite2( lua_State* luaVM)
{
   Player* pl = (Player*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int sp2 = (int) lua_tonumber(luaVM, -1); //handle 2
   pl->sprite2 = sp2;
   lua_pushnumber(luaVM, 1);
   return 1;
}

int Player::l_setSpriteInvincible( lua_State* luaVM)
{
   Player* pl = (Player*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int spi = (int) lua_tonumber(luaVM, -1); //handle 2
   pl->spriteinvincible = spi;
   lua_pushnumber(luaVM, 1);
   return 1;
}

int Player::l_setBGSprite( lua_State* luaVM)
{
   Player* pl = (Player*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int bgsp = (int) lua_tonumber(luaVM, -1); //handle 2
   pl->bgsprite = bgsp;
   lua_pushnumber(luaVM, 1);
   return 1;
}
