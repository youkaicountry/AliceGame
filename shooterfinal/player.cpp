#include "player.h"

Player::Player()
{
    x = 400;
    y = 550;
    lives = 3;
    bombs = 3;
    score = 0;
    power = 0;
    sprite = 1;
    invincible = false;
    radius = 4;
    speed = 4;
    recoila = 0;
    recoilb = 0;
    invincibletime = 0;
    invinciblesprite = 9;
    xvel = 0;
    yvel = 0;
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

int Player::getSprite()
{
    return sprite;
}

void Player::setSprite(int newsprite)
{
    sprite = newsprite;
    return;
}

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
