#include "spritenote.h"

SpriteNote::SpriteNote(int sx, int sy, int ssprite)
{
    x = sx;
    y = sy;
    sprite = ssprite;
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
