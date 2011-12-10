#include "spritenote.h"

SpriteNote::SpriteNote(int sx, int sy, int ssprite)
{
    x = sx;
    y = sy;
    sprite = ssprite;
    pitch = 0;
    roll = 0;
    yaw = 0;
    return;
}

SpriteNote::SpriteNote(int sx, int sy, float npitch, float nroll, float nyaw, int ssprite)
{
    x = sx;
    y = sy;
    sprite = ssprite;
    pitch = npitch;
    roll = nroll;
    yaw = nyaw;
    return;
}

SpriteNote::~SpriteNote()
{
    return;
}

int SpriteNote::getX()
{
    return x;
}

void SpriteNote::setX(int newx)
{
    x = newx;
    return;
}

int SpriteNote::getY()
{
    return y;
}

void SpriteNote::setY(int newy)
{
    y = newy;
    return;
}

int SpriteNote::getSprite()
{
    return sprite;
}

void SpriteNote::setSprite(int newsprite)
{
    sprite = newsprite;
    return;
}

float SpriteNote::getPitch()
{
   return pitch;
}
   
void SpriteNote::setPitch(float npitch)
{
   pitch = npitch;
   return;
}

float SpriteNote::getRoll()
{
   return roll;
}

void SpriteNote::setRoll(float nroll)
{
   roll = nroll;
   return;
}

float SpriteNote::getYaw()
{
   return yaw;
}

void SpriteNote::setYaw(float nyaw)
{
   yaw = nyaw;
   return;
}
