//here is an example of how to make enemies

#include "myenemies.h"
#include <vector>
#include <list>
#include "twovector.h"
#include <math.h>
#include "barrage.h"

//------------------------------------------------------------------------------
//wall
//------------------------------------------------------------------------------
wall::wall(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p)
{
    
    activatecycles = sactivatecycles;
    active = false;
    dead = false;
    dissolve = false;
    sprite = 27;
    currentwaypoint = 0;
    //dir = direction;
    score = 1500;    

    
    Barrage ba;
    vbarrages.push_back(ba);
    vbarrages[0].addBullet(Bullet(0, 0, 0, 0, 0, 2.5, true, 0, 0, 0, 0, 0, 0, 9, 0, 24), 0);
    
    Barrage bb;
    vbarrages.push_back(bb);
    vbarrages[1].addBullet(Bullet(0, 0, 0, 0, 0, 2.5, true, 0, 0, 0, 0, 0, 0, 9, 0, 25), 0);
    
    Barrage bc;
    vbarrages.push_back(ba);
    vbarrages[2].addBullet(Bullet(0, 0, 0, 0, 0, 2.5, true, 0, 0, 0, 0, 0, 0, 9, 0, 26), 0);
    
    scoredropchance = .5;
    powerdropchance = .5;
    hp = 17;
    x = sx;
    y = sy;
    xvel = 0;
    yvel = 0;
    xaccel = 0;
    yaccel = 0;
    rotvel = 0;
    rotaccel = 0;
    radvel = 0;
    radaccel = 0;
    radius = 16;
    
    vwaypoints.push_back(new wpwallin());
    vwaypoints.push_back(new wpwallshoot());
    vwaypoints.push_back(new wpwallout());
    vwaypoints[currentwaypoint]->enter(this,bv, p);
    
    
    return;
}

wall::~wall()
{
    vector<Waypoint*>::iterator k;
    for(k=vwaypoints.begin(); k != vwaypoints.end(); k++)
    {
       delete (*k);
    }
   return;   
}

//wp
wpwallin::wpwallin()
{
    return;
}

wpwallin::~wpwallin()
{
    return;
}

int wpwallin::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->yvel = 6.0;
    e->yaccel = -.06;
    return 0;
}

int wpwallin::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpwallin::update(Enemy* e,list<Bullet>* bv, Player* p)
{
       if (e->yvel <= 0 )
       {
           return 1;
       }
       
       return 0;
}

//wp
wpwallshoot::wpwallshoot()
{
    return;
}

wpwallshoot::~wpwallshoot()
{
    return;
}

int wpwallshoot::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->vbarrages[0].getBarrage(bv, e->x+1, e->y+13, 0, 0, p);
    cyclesleft = 1600;
    e->yvel = 0;
    e->yaccel = 0;
    return 0;
}

int wpwallshoot::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpwallshoot::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft == 0) {return 1;}
    if (cyclesleft % 280 > 150)
    {
       if (cyclesleft % 5 == 0) {e->vbarrages[1].getBarrage(bv, e->x+1, e->y+13, 0, 0, p);}
    //if (cyclesleft % 117 == 0) {e->vbarrages[1].getBarrage(bv, e->x, e->y, 0, 0, p);}
    //if (cyclesleft % 55 == 0) {e->vbarrages[0].getBarrage(bv, e->x, e->y, 0, 0, p);}
    //if (cyclesleft % 190 == 0) {e->vbarrages[1].getBarrage(bv, e->x, e->y, 0, 0, p);}
    }
    if (cyclesleft % 280 == 150)
    {
        e->vbarrages[2].getBarrage(bv, e->x+1, e->y+9, 0, 0, p);
    }
    return 0;
}

//wp
wpwallout::wpwallout()
{
    return;
}

wpwallout::~wpwallout()
{
    return;
}

int wpwallout::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    //e->vbarrages[2].getBarrage(bv, e->x, e->y, 0, 0, p);
    cyclesleft = 200;
    e->yvel = 0;
    e->yaccel = -.12;
    return 0;
}

int wpwallout::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpwallout::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft == 0) {e->dead = true; e->dissolve = true;}
    return 0;
}

//------------------------------------------------------------------------------
//Ferret
//------------------------------------------------------------------------------
ferret::ferret(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p)
{
    
    activatecycles = sactivatecycles;
    active = false;
    dead = false;
    dissolve = false;
    sprite = 23;
    currentwaypoint = 0;
    //dir = direction;
    score = 1300;    

    
    Barrage ba;
    vbarrages.push_back(ba);
    vbarrages[0].addOutCircleRotate(15, 20, 0, 00, 00, Bullet(0, 0, 0, 0, 1.5, 1.5, true, 0, 0, 0, 0, 0, 0, 6, 1, 7),1);
    
    //Barrage bb;
    //vbarrages.push_back(bb);
    //vbarrages[1].addOutCircleRotate(.01, 20, 0, 00, 00, Bullet(0, 0, 0, 0, 0, 0, true, 0, 0, -.5, 0, 0, 1.6, 6, 1, 5),0);
    
    scoredropchance = .5;
    powerdropchance = .5;
    hp = 20;
    x = sx;
    y = sy;
    xvel = 0;
    yvel = 0;
    xaccel = 0;
    yaccel = 0;
    rotvel = 0;
    rotaccel = 0;
    radvel = 0;
    radaccel = 0;
    radius = 13;
    
    vwaypoints.push_back(new wpferretin());
    vwaypoints.push_back(new wpferretshoot());
    vwaypoints.push_back(new wpferretout());
    vwaypoints[currentwaypoint]->enter(this,bv, p);
    
    
    return;
}

ferret::~ferret()
{
    vector<Waypoint*>::iterator k;
    for(k=vwaypoints.begin(); k != vwaypoints.end(); k++)
    {
       delete (*k);
    }
   return;   
}

//wp
wpferretin::wpferretin()
{
    return;
}

wpferretin::~wpferretin()
{
    return;
}

int wpferretin::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->yvel = 2.9;
    e->yaccel = -.06;
    return 0;
}

int wpferretin::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpferretin::update(Enemy* e,list<Bullet>* bv, Player* p)
{
       if (e->yvel <= 0 )
       {
           return 1;
       }
       
       return 0;
}

//wp
wpferretshoot::wpferretshoot()
{
    return;
}

wpferretshoot::~wpferretshoot()
{
    return;
}

int wpferretshoot::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft = 1600;
    e->yvel = 0;
    e->yaccel = 0;
    return 0;
}

int wpferretshoot::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpferretshoot::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft == 0) {return 1;}
    if (cyclesleft % 280 == 0) {e->vbarrages[0].getBarrage(bv, e->x, e->y, 0, 0, p);}
    //if (cyclesleft % 117 == 0) {e->vbarrages[1].getBarrage(bv, e->x, e->y, 0, 0, p);}
    //if (cyclesleft % 55 == 0) {e->vbarrages[0].getBarrage(bv, e->x, e->y, 0, 0, p);}
    //if (cyclesleft % 190 == 0) {e->vbarrages[1].getBarrage(bv, e->x, e->y, 0, 0, p);}
    return 0;
}

//wp
wpferretout::wpferretout()
{
    return;
}

wpferretout::~wpferretout()
{
    return;
}

int wpferretout::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft = 200;
    e->yvel = 0;
    e->yaccel = -.1;
    return 0;
}

int wpferretout::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpferretout::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft == 0) {e->dead = true; e->dissolve = true;}
    return 0;
}

//------------------------------------------------------------------------------
//Sprayer
//------------------------------------------------------------------------------
sprayer::sprayer(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p, double direction)
{
    
    activatecycles = sactivatecycles;
    active = false;
    dead = false;
    dissolve = false;
    sprite = 22;
    currentwaypoint = 0;
    dir = direction;
    score = 2000;    

    
    Barrage ba;
    vbarrages.push_back(ba);
    vbarrages[0].addOutCircleRotate(.01, 20, 0, 00, 00, Bullet(0, 0, 0, 0, 0, 0, true, 0, 0, .5, 0, 0, 1.6, 7, 1, 13),0);
    
    Barrage bb;
    vbarrages.push_back(bb);
    vbarrages[1].addOutCircleRotate(.01, 20, 0, 00, 00, Bullet(0, 0, 0, 0, 0, 0, true, 0, 0, -.5, 0, 0, 1.6, 8, 1, 5),0);
    
    scoredropchance = .5;
    powerdropchance = .5;
    hp = 30;
    x = sx;
    y = sy;
    xvel = 0;
    yvel = 0;
    xaccel = 0;
    yaccel = 0;
    rotvel = 0;
    rotaccel = 0;
    radvel = 0;
    radaccel = 0;
    radius = 13;
    
    vwaypoints.push_back(new wpsprayin());
    vwaypoints.push_back(new wpsprayshoot());
    vwaypoints.push_back(new wpsprayout());
    vwaypoints[currentwaypoint]->enter(this,bv, p);
    
    
    return;
}

sprayer::~sprayer()
{
    vector<Waypoint*>::iterator k;
    for(k=vwaypoints.begin(); k != vwaypoints.end(); k++)
    {
       delete (*k);
    }
   return;   
}

//wp
wpsprayin::wpsprayin()
{
    return;
}

wpsprayin::~wpsprayin()
{
    return;
}

int wpsprayin::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->xvel = 7*e->dir;
    e->xaccel = -.1*e->dir;
    return 0;
}

int wpsprayin::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpsprayin::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    if (e->dir >= 0)
    {
       if (e->xvel <=0 )
       {
           return 1;
       }
    }
    else
    {
        if (e->xvel >= 0)
        {
            return 1;
        }
    }
    return 0;
}

//wp
wpsprayshoot::wpsprayshoot()
{
    return;
}

wpsprayshoot::~wpsprayshoot()
{
    return;
}

int wpsprayshoot::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft = 1600;
    e->xvel = 0;
    e->xaccel = 0;
    return 0;
}

int wpsprayshoot::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpsprayshoot::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft == 0) {return 1;}
    if (cyclesleft % 91 == 0) {e->vbarrages[0].getBarrage(bv, e->x, e->y, 0, 0, p);}
    if (cyclesleft % 137 == 0) {e->vbarrages[1].getBarrage(bv, e->x, e->y, 0, 0, p);}
    //if (cyclesleft % 55 == 0) {e->vbarrages[0].getBarrage(bv, e->x, e->y, 0, 0, p);}
    //if (cyclesleft % 190 == 0) {e->vbarrages[1].getBarrage(bv, e->x, e->y, 0, 0, p);}
    return 0;
}

//wp
wpsprayout::wpsprayout()
{
    return;
}

wpsprayout::~wpsprayout()
{
    return;
}

int wpsprayout::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft = 200;
    e->xvel = 0;
    e->xaccel = -(e->dir)*.1;
    return 0;
}

int wpsprayout::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpsprayout::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft == 0) {e->dead = true; e->dissolve = true;}
    return 0;
}



//------------------------------------------------------------------------------
//LEFTSPOUT
//------------------------------------------------------------------------------
spout::spout(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p, double direction)
{
    
    activatecycles = sactivatecycles;
    active = false;
    dead = false;
    dissolve = false;
    sprite = 12;
    currentwaypoint = 0;
    dir = direction;
    score = 1000;    

    vbarrages.push_back(Barrage());
    vbarrages[0].addBullet(Bullet(0, 0, 0, 0, 0, 2.0, true, 0, 0, 0, 0, 0, 0, 7, 0, 7), 0);
    vbarrages[0].addBullet(Bullet(-10, 5, .014, 0, -2, 2.0, true, 0, 0, 0, 0, 0, 0, 7, 0, 13), 0);    
    vbarrages[0].addBullet(Bullet(10, 5, -.014, 0, 2, 2.0, true, 0, 0, 0, 0, 0, 0, 7, 0, 14), 0);
    vbarrages.push_back(Barrage());
    vbarrages[1].addBullet(Bullet(0, 0, 0, 0, 1, 1, true, 0, 0, 0, 0, 0, 0, 16, 0, 0), 1);
    scoredropchance = .5;
    powerdropchance = .5;
    hp = 16;
    x = sx;
    y = sy;
    xvel = 0;
    yvel = 0;
    xaccel = 0;
    yaccel = 0;
    rotvel = 0;
    rotaccel = 0;
    radvel = 0;
    radaccel = 0;
    radius = 13;
    
    vwaypoints.push_back(new wpspoutin());
    vwaypoints.push_back(new wpspoutshoot());
    vwaypoints.push_back(new wpspoutout());
    vwaypoints[currentwaypoint]->enter(this,bv, p);
    
    
    return;
}

spout::~spout()
{
    vector<Waypoint*>::iterator k;
    for(k=vwaypoints.begin(); k != vwaypoints.end(); k++)
    {
       delete (*k);
    }
   return;   
}

//wp
wpspoutin::wpspoutin()
{
    return;
}

wpspoutin::~wpspoutin()
{
    return;
}

int wpspoutin::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->xvel = 7*e->dir;
    e->xaccel = -.1*e->dir;
    return 0;
}

int wpspoutin::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpspoutin::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    if (e->dir >= 0)
    {
       if (e->xvel <=0 )
       {
           return 1;
       }
    }
    else
    {
        if (e->xvel >= 0)
        {
            return 1;
        }
    }
    return 0;
}

//wp
wpspoutshoot::wpspoutshoot()
{
    return;
}

wpspoutshoot::~wpspoutshoot()
{
    return;
}

int wpspoutshoot::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft = 1600;
    e->xvel = 0;
    e->xaccel = 0;
    return 0;
}

int wpspoutshoot::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpspoutshoot::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft == 0) {return 1;}
    if (cyclesleft % 55 == 0) {e->vbarrages[0].getBarrage(bv, e->x, e->y, 0, 0, p);}
    if (cyclesleft % 190 == 0) {e->vbarrages[1].getBarrage(bv, e->x, e->y, 0, 0, p);}
    return 0;
}

//wp
wpspoutout::wpspoutout()
{
    return;
}

wpspoutout::~wpspoutout()
{
    return;
}

int wpspoutout::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft = 200;
    e->xvel = 0;
    e->xaccel = -(e->dir)*.1;
    return 0;
}

int wpspoutout::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpspoutout::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft == 0) {e->dead = true; e->dissolve = true;}
    return 0;
}

//------------------------------------------------------------------------------
//LEFTFODDER
//------------------------------------------------------------------------------
leftfodder::leftfodder(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p)
{
    
    activatecycles = sactivatecycles;
    active = false;
    dead = false;
    dissolve = false;
    sprite = 8;
    currentwaypoint = 0;
    score = 400;
    
    vbarrages.push_back(Barrage());
    vbarrages[0].addOutCircleRotate(.01, 16, 0, 00, 00, Bullet(0, 0, 0, 0, 0, 0, true, 0, 0, 1, 0, 0, 1.4, 8, 1, 5),0);
    
    scoredropchance = .6;
    powerdropchance = .6;
    hp = 4;
    x = sx;
    y = sy;
    xvel = 0;
    yvel = 0;
    xaccel = 0;
    yaccel = 0;
    rotvel = 0;
    rotaccel = 0;
    radvel = 0;
    radaccel = 0;
    radius = 15;
    
    vwaypoints.push_back(new wpleftfodderdown());
    vwaypoints.push_back(new wpleftfoddercircle());
    vwaypoints.push_back(new wpleftfodderright());
    vwaypoints[currentwaypoint]->enter(this,bv, p);
    
    
    return;
}

leftfodder::~leftfodder()
{
    vector<Waypoint*>::iterator k;
    for(k=vwaypoints.begin(); k != vwaypoints.end(); k++)
    {
       delete (*k);
    }
    return;
}

//wpleftfodderdown/////////////////////////////////////////////////////////
wpleftfodderdown::wpleftfodderdown()
{
    return;
}

wpleftfodderdown::~wpleftfodderdown()
{
    return;
}

int wpleftfodderdown::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->yvel = 2.8;
    cyclesleft = 50;
    return 0;
}

int wpleftfodderdown::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpleftfodderdown::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft < 0)
    {
        return 1;
    }
    return 0;
}

//wpleftfoddercircle/////////////////////////////////////////////////////////
wpleftfoddercircle::wpleftfoddercircle()
{
    return;
}

wpleftfoddercircle::~wpleftfoddercircle()
{
    return;
}

int wpleftfoddercircle::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->yvel = 0;
    e->rotvel = -2.8;
    e->rcenterx = e->x+80;
    e->rcentery = e->y;
    cyclesleft = 40;
    return 0;
}

int wpleftfoddercircle::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpleftfoddercircle::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft < 0)
    {
        return 1;
    }
    return 0;
}

//wpleftfodderright/////////////////////////////////////////////////////////
wpleftfodderright::wpleftfodderright()
{
    return;
}

wpleftfodderright::~wpleftfodderright()
{
    return;
}

int wpleftfodderright::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft = 110;
    double theta, tx, ty, txx;
    TwoVector v(e->x - e->rcenterx, e->y - e->rcentery);

    theta = e->rotvel / v.getLength();
    tx = e->x - e->rcenterx; ty = e->y - e->rcentery;
    txx = tx;
    tx = tx * cos(theta) - ty * sin(theta);
    ty = txx * sin(theta) + ty * cos(theta);
    e->xvel = tx + e->rcenterx - e->x; e->yvel = ty + e->rcentery - e->y;
    
    e->rotvel = 0;
    //cyclesleft = 200;
    return 0;
}

int wpleftfodderright::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wpleftfodderright::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft == 0)
    {
        e->vbarrages[0].getBarrage(bv, e->x, e->y, 0, 0, p);//e->xvel, e->yvel);
    }
    if (cyclesleft == -150)
    {
        e->dissolve = true;
        e->dead = true;
    }
    return 0;
}


//RIGHT FODDER------------------------------------------------------------------
rightfodder::rightfodder(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p)
{
    
    activatecycles = sactivatecycles;
    active = false;
    dead = false;
    dissolve = false;
    sprite = 8;
    currentwaypoint = 0;
    score = 400;
    
    vbarrages.push_back(Barrage());
    vbarrages[0].addOutCircleRotate(.01, 16, 0, 00, 00, Bullet(0, 0, 0, 0, 0, 0, true, 0, 0, -1, 0, 0, 1.4, 7, 1, 5),0);
    
    scoredropchance = .6;
    powerdropchance = .6;
    hp = 4;
    x = sx;
    y = sy;
    xvel = 0;
    yvel = 0;
    xaccel = 0;
    yaccel = 0;
    rotvel = 0;
    rotaccel = 0;
    radvel = 0;
    radaccel = 0;
    radius = 15;
    
    vwaypoints.push_back(new wprightfodderdown());
    vwaypoints.push_back(new wprightfoddercircle());
    vwaypoints.push_back(new wprightfodderleft());
    vwaypoints[currentwaypoint]->enter(this,bv, p);
    
    
    return;
}

rightfodder::~rightfodder()
{
    vector<Waypoint*>::iterator k;
    for(k=vwaypoints.begin(); k != vwaypoints.end(); k++)
    {
       delete (*k);
    }
    return;
}

//wprightfodderdown/////////////////////////////////////////////////////////
wprightfodderdown::wprightfodderdown()
{
    return;
}

wprightfodderdown::~wprightfodderdown()
{
    return;
}

int wprightfodderdown::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->yvel = 2.8;
    cyclesleft = 30;
    return 0;
}

int wprightfodderdown::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wprightfodderdown::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft < 0)
    {
        return 1;
    }
    return 0;
}

//wprightfoddercircle/////////////////////////////////////////////////////////
wprightfoddercircle::wprightfoddercircle()
{
    return;
}

wprightfoddercircle::~wprightfoddercircle()
{
    return;
}

int wprightfoddercircle::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->yvel = 0;
    e->rotvel = 2.8;
    e->rcenterx = e->x-80;
    e->rcentery = e->y;
    cyclesleft = 40;
    return 0;
}

int wprightfoddercircle::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wprightfoddercircle::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft < 0)
    {
        return 1;
    }
    return 0;
}

//wprightfodderleft/////////////////////////////////////////////////////////
wprightfodderleft::wprightfodderleft()
{
    return;
}

wprightfodderleft::~wprightfodderleft()
{
    return;
}

int wprightfodderleft::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft = 110;
    double theta, tx, ty, txx;
    TwoVector v(e->x - e->rcenterx, e->y - e->rcentery);

    theta = e->rotvel / v.getLength();
    tx = e->x - e->rcenterx; ty = e->y - e->rcentery;
    txx = tx;
    tx = tx * cos(theta) - ty * sin(theta);
    ty = txx * sin(theta) + ty * cos(theta);
    e->xvel = tx + e->rcenterx - e->x; e->yvel = ty + e->rcentery - e->y;
    
    e->rotvel = 0;
    //cyclesleft = 200;
    return 0;
}

int wprightfodderleft::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    e->dead = true;
    return 0;
}

int wprightfodderleft::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    cyclesleft--;
    if (cyclesleft == 0)
    {
        e->vbarrages[0].getBarrage(bv, e->x, e->y, 0, 0, p);//e->xvel, e->yvel);
    }
    if (cyclesleft == -150)
    {
        e->dissolve = true;
        e->dead = true;
    }
    return 0;
}

//linear
LinearEnemy::LinearEnemy(const LinearTransform *transform, Enemy *inner)
{
   this->transform.setTo(transform);
   this->inner = inner;
   this->first_time = true;
   this->hp = (inner->hp > 0) ? inner->hp : 1;
   return;
}

LinearEnemy::~LinearEnemy()
{
   delete this->inner;
   return;   
}

bool LinearEnemy::update(list<Bullet>*bv, Player *p, GameSpace *gs)
{
   bool result = inner->update(bv, p, gs);
   if (first_time)
      this->hp = inner->hp;
   return 0;   
}

//smallblue
smallblue::smallblue(double sx, double sy, int sactivatecycles,list<Bullet>* bv,
   Player* p)
{
   activatecycles = sactivatecycles;
   active = false;
   dead = false;
   dissolve = false;
   sprite = 17;
   currentwaypoint = 0;
   score = 100;

   scoredropchance = .5;
   powerdropchance = .5;
   hp = 1;
   x = sx;
   y = sy;
   xvel = 0;
   yvel = 0;
   xaccel = 0;
   yaccel = 0;
   rotvel = 0;
   rotaccel = 0;
   radvel = 0;
   radaccel = 0;
   radius = 13;

   vwaypoints.push_back(new wp_smallblue_0());
   vwaypoints[currentwaypoint]->enter(this,bv, p);
   return;
}

smallblue::~smallblue()
{
   return;
}

wp_smallblue_0::wp_smallblue_0()
{
   return;   
}

wp_smallblue_0::~wp_smallblue_0()
{
   return;   
}

int wp_smallblue_0::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
   e->xvel = 2.5;
   return 0;
}

int wp_smallblue_0::die(Enemy* e,list<Bullet>* bv, Player* p)
{
   e->dead = true;
   return 0;   
}

int wp_smallblue_0::update(Enemy* e,list<Bullet>* bv, Player* p)
{
   return 0;
}
