#include "player.h"
#include "scoreitem.h"

ScoreItem::ScoreItem(double sx, double sy, double sxvel, double syvel, double sxaccel, double syaccel)
{
    x = sx;
    y = sy;
    xvel = sxvel;
    yvel = syvel;
    xaccel = sxaccel;
    yaccel = syaccel;
    sprite = 16;
    radius = 10;
    return;
}

ScoreItem::~ScoreItem()
{
    return;
}

void ScoreItem::onPickup(Player* pl)
{
    
    pl->setScore((int)(pl->getScore()+((600-pl->getY())*2)+300));
    return;
}
