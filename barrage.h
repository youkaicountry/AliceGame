#ifndef _BARRAGE__
#define _BARRAGE__
#include <vector>
#include <list>
#include "bullet.h"
#include "player.h"

using namespace std;
//a barrage is a list of bullets with positions relative to the origin
//this class includes some utility method for setting up the barrage

//BUL_FOLLOW makes the bullets aim AT the player when created
enum {BUL_FOLLOW = 1};

class Barrage
{
private:
vector<Bullet> bulletvector;
vector<int> bulletinfo;
public:
Barrage();
~Barrage();

//adds a single bullet
void addBullet(Bullet b, int info);

//adds a circle that shoots outward
void addOutCircle(double circleradius, int n, double angleoffset,
                   double acceleration, double velocity, int sprite,
                   double bulletradius, int info);
                   
//adds a circle that shoots outward and has rotation
//Oh god looks at this mess! Here's what it all means...
//circleradius is the radius of the circle of bullets to be created
//n is the number of bullets to go into this circle
//angleoffset is the initial angle of the first bullet
//acceleration and velocity are the INITIAL OUTWARD FACING velocity (not radial)
//arclengthrotation determines whether flat arc length or angle is used for rotational velocity
//rcenterx and rcentery determine the center of rotation. try moving this to strange places for cool results.
//racceleration and rvelocity are the rotational velocity and acceleration
//radialaccel and radialvel are the radial acceleration (they always face out from rcenter)
//sprite is the sprite number to use. see main for the sprites.
//bulletradius is the physical radius of the bullets, to be used for collisions
//info is not used yet, but will be used for effects such as player seeking bullets and such
void addOutCircleRotate(double circleradius, int n, double angleoffset,
                   double acceleration, double velocity, Bullet b, int info);

//adds a circle with the given characteristics
void addCircle(double radius, double x, double y, double xvel, double yvel,
              double xaccel, double yaccel, int sprite, int info);

//adds a line with the given characteristics
void addLine(double x1, double y1, double x2, double y2, int n, double xvel,
             double yvel, double xaccel, double yaccel,int sprite, int info);
             
//adds the barrage bullets to the passed vector pointer
void getBarrage(list<Bullet>* bv, double x, double y, double xvel, double yvel, Player* p);

};


#endif
