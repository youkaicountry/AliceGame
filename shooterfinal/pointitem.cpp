#include "player.h"
#include "pointitem.h"

PowerItem::PowerItem(double sx, double sy, double sxvel, double syvel, double sxaccel, double syaccel)
{
    x = sx;
    y = sy;
    xvel = sxvel;
    yvel = syvel;
    xaccel = sxaccel;
    yaccel = syaccel;
    radius = 10;
    sprite = 15;
    return;
}

PowerItem::~PowerItem()
{
    return;
}

void PowerItem::onPickup(Player* pl)
{
    pl->setPower(pl->getPower()+10);
    return;
}
