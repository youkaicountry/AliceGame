#ifndef _MYENEMIES__
#define _MYENEMIES__
#include "enemybase.h"
#include "linear.h"
#include <list>

//------------------------------------------------------------------------------
//WALL
//------------------------------------------------------------------------------
class wall : public Enemy
{
    public:
    wall(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p);
    virtual ~wall();
};

class wpwallin : public Waypoint
{
    public:
    wpwallin();
    ~wpwallin();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class wpwallshoot : public Waypoint
{
    public:
    wpwallshoot();
    ~wpwallshoot();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class wpwallout : public Waypoint
{
    public:
    wpwallout();
    ~wpwallout();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

//------------------------------------------------------------------------------
//FERRET
//------------------------------------------------------------------------------
class ferret : public Enemy
{
    public:
    ferret(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p);
    virtual ~ferret();
};

class wpferretin : public Waypoint
{
    public:
    wpferretin();
    ~wpferretin();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class wpferretshoot : public Waypoint
{
    public:
    wpferretshoot();
    ~wpferretshoot();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class wpferretout : public Waypoint
{
    public:
    wpferretout();
    ~wpferretout();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

//------------------------------------------------------------------------------
//SPRAYER
//------------------------------------------------------------------------------
class sprayer : public Enemy
{
    public:
    sprayer(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p, double direction);
    virtual ~sprayer();
};

class wpsprayin : public Waypoint
{
    public:
    wpsprayin();
    ~wpsprayin();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class wpsprayshoot : public Waypoint
{
    public:
    wpsprayshoot();
    ~wpsprayshoot();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class wpsprayout : public Waypoint
{
    public:
    wpsprayout();
    ~wpsprayout();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

//------------------------------------------------------------------------------
//LEFTSPOUT
//------------------------------------------------------------------------------
class spout : public Enemy
{
    public:
    spout(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p, double direction);
    virtual ~spout();
};

class wpspoutin : public Waypoint
{
    public:
    wpspoutin();
    ~wpspoutin();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class wpspoutshoot : public Waypoint
{
    public:
    wpspoutshoot();
    ~wpspoutshoot();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class wpspoutout : public Waypoint
{
    public:
    wpspoutout();
    ~wpspoutout();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

//class wpleftfodderdown;
class leftfodder : public Enemy
{
    public:
    leftfodder(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p);
    ~leftfodder();
};

class wpleftfodderdown : public Waypoint
{
    public:
    wpleftfodderdown();
    ~wpleftfodderdown();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class wpleftfoddercircle : public Waypoint
{
    public:
    wpleftfoddercircle();
    ~wpleftfoddercircle();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};
    
class wpleftfodderright : public Waypoint
{
    public:
    wpleftfodderright();
    ~wpleftfodderright();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};


//RIGHT FODDER------------------------------------------------------------------
class rightfodder : public Enemy
{
    public:
    rightfodder(double sx, double sy, int sactivatecycles,list<Bullet>* bv, Player* p);
    ~rightfodder();
};

class wprightfodderdown : public Waypoint
{
    public:
    wprightfodderdown();
    ~wprightfodderdown();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class wprightfoddercircle : public Waypoint
{
    public:
    wprightfoddercircle();
    ~wprightfoddercircle();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};
    
class wprightfodderleft : public Waypoint
{
    public:
    wprightfodderleft();
    ~wprightfodderleft();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

class LinearEnemy : public Enemy
{
public:
   double x, y;    // yes, they hide the base class x and y,
                   // but only from the point of view of the client class.

   LinearEnemy(const LinearTransform *transform,
      Enemy *inner);
   ~LinearEnemy();
   virtual bool update(list<Bullet>* bv, Player* p, GameSpace *gs);

private:   
   LinearTransform transform;
   Enemy *inner;
   bool first_time;
};

class smallblue : public Enemy
{
public:
    smallblue(double sx, double sy, int sactivatecycles,list<Bullet>* bv,
       Player* p);
    ~smallblue();
};

class wp_smallblue_0 : public Waypoint
{
public:
    wp_smallblue_0();
    ~wp_smallblue_0();
    
    int enter(Enemy* e,list<Bullet>* bv, Player* p);
    int die(Enemy* e,list<Bullet>* bv, Player* p);
    int update(Enemy* e,list<Bullet>* bv, Player* p);
};

#endif
