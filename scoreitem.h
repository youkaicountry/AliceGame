#ifndef _SCOREITEM__
#define _SCOREITEM__

#include "player.h"
#include "item.h"

class ScoreItem : public Item
{
    public:
        ScoreItem(double sx, double sy, double sxvel, double syvel, double sxaccel, double syaccel); //position only one needed. other physics
                                       //values are always the same
        ~ScoreItem();
        void onPickup(Player* pl);     //this is run on pickup
};

#endif
