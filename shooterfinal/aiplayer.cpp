#include "aiplayer.h"
#include "keystate.h"
#include "random.h"
#include "gamespace.h"
#include <iostream.h>
#include <vector>
#include <list>
#include "twovector.h"
#include "player.h"
#include <math.h>
#include "enemybase.h"
#include "dna.h"

AIPlayer::AIPlayer()
{
    gameline = .65;
    jitterprobability = .005;
    enemies = -1;
    items = -1;
    return;
}

AIPlayer::~AIPlayer()
{
    return;
}

int AIPlayer::getRps()
{
    return rps;
}

void AIPlayer::setRps(int newrps)
{
    rps = newrps;
    return;
}
    
double AIPlayer::getBulletDangerRadius()
{
    return bulletdangerradius;
}

void AIPlayer::setBulletDangerRadius(double newbulletdangerradius)
{
    bulletdangerradius = newbulletdangerradius;
    return;
}
    
double AIPlayer::getWeightVariance()
{
    return weightvariance;
}

void AIPlayer::setWeightVariance(double newweightvariance)
{
    weightvariance = newweightvariance;
    return;
}
    
double AIPlayer::getBulletMissProbability()
{
    return bulletmissprobability;
}

void AIPlayer::setBulletMissProbability(double newbulletmissprobability)
{
    bulletmissprobability = newbulletmissprobability;
    return;
}

int getWidth(bool a, bool b, bool c)
{
   //b is the middle
   if (b == false) {return 0;}
   return ((int)a + (int)b + (int)c);
}
   
//THIS THING TAKES AN ANGLE AND CONVERTS IT TO ONE OF THE 8 DIRECTIONS
int getDirection(double theta)
{
   if (theta < .3927 && theta >= -.3927)
    {
        //ks.setRight(true);
        return 2;
    }
    else if (theta >= .3927 && theta < 1.1781)
    {
        return 1;
        //ks.setRight(true);
        //ks.setUp(true);
    }
    else if (theta >= 1.1781 && theta < 1.9634)
    {
        return 0;
        //ks.setUp(true);
    }
    else if (theta >= 1.9634 && theta < 2.7488)
    {
        return 7;
        //ks.setLeft(true);
        //ks.setUp(true);
    }
    else if (theta < -.3927 && theta >= -1.1781)
    {
        return 3;
        //ks.setRight(true);
        //ks.setDown(true);
    }
    else if (theta < -1.1781 && theta >= -1.9634)
    {
        return 4;
        //ks.setDown(true);
    }
    else if (theta < -1.9634 && theta >= -2.7438)
    {
        return 5;
        //ks.setLeft(true);
        //ks.setDown(true);
    }
    else if (theta < -2.7438 || theta >= 2.7488)
    {
        return 6;
        //ks.setLeft(true);
    }
   
   return 0;
}

KeyState AIPlayer::update(GameSpace* gs, Player* p, DNA dna, KeyState kes)
{
    if (gs->cycle % dna.getReactionCycles() != 0)
    {
       return kes;
    } 
    
    
    //examine enemies and pick one
    int tempenemies = 0;
    //cout << enemies << "\n";
    list<Enemy*>::iterator ne;
    for(ne=gs->lEnemies.begin(); ne != gs->lEnemies.end();ne++)
    {
       if ((*ne)->active) {tempenemies++;}
    }
    enemies = tempenemies;
    if (enemies > tempenemies || (enemies == 0))
    {
         //cout << "changing target\n";
         enemytarget = airan.nextInt(enemies)+1;
    }
    
    //cout << enemies << "\n";
    //cout << enemytarget << "\n";
    
    //examine items and pick one
    int tempitems = 0;
    list<Item*>::iterator it;
    for(it=gs->lItems.begin(); it != gs->lItems.end();it++)
    {
       tempitems++;
    }
    items = tempitems;
    if (items > tempitems || (items == 0))
    {
         //TODO : pick item based on merits (like distance)
         itemtarget = airan.nextInt(items)+1;
    }
    //cout << items;
    
    //FIND NEAREST BULLET
    double nearestbullet = 100000;
    list<Bullet>::iterator bu;
    for(bu=gs->lEnemyBullets.begin(); bu != gs->lEnemyBullets.end();bu++)
    {
       TwoVector vb(bu->getX() - p->getX(), bu->getY() - p->getY());
       double dtest = vb.getLength(); dtest -= p->getRadius();dtest -= bu->getRadius();
       if (dtest < nearestbullet) {nearestbullet = dtest;}
    }
    
    
        //SET STATE FOR FSM
        int state = 1;
        if (enemies > 0) {state = 1;}
        if (items > 0) {state = 0;} //there are items on the screen
        if (dna.getBulletPanic() >= nearestbullet) {state = 2;}
        
        //THE FOLLOWING COMMENTED OUT CODE IS AN OLD STATE I DECIDED TO SCRAP.
        
        /*if (state == 3)
        {
           bool bulletmap[8];
           for (int iii = 0;iii < 8;iii++)
           {
              bulletmap[iii] = true;
           }
           list<Bullet>::iterator eb;
           for(eb=gs->lEnemyBullets.begin(); eb != gs->lEnemyBullets.end();eb++)
           {
              TwoVector vk(eb->getX() - p->getX(), eb->getY() - p->getY());
              double grest = vk.getLength(); grest -= p->getRadius();grest -= eb->getRadius();
              if (grest <= dna.getBulletPanic()) 
              {
                  double th = atan2(vk.getY(), vk.getX());
                  bulletmap[getDirection(th)] = false;
              }
           }
         
         int bulletwidth[8];
         bulletwidth[0] = getWidth(bulletmap[7], bulletmap[0], bulletmap[1]);
         bulletwidth[1] = getWidth(bulletmap[0], bulletmap[1], bulletmap[2]);
         bulletwidth[2] = getWidth(bulletmap[1], bulletmap[2], bulletmap[3]);
         bulletwidth[3] = getWidth(bulletmap[2], bulletmap[3], bulletmap[4]);
         bulletwidth[4] = getWidth(bulletmap[3], bulletmap[4], bulletmap[5]);
         bulletwidth[5] = getWidth(bulletmap[4], bulletmap[5], bulletmap[6]);
         bulletwidth[6] = getWidth(bulletmap[5], bulletmap[6], bulletmap[7]);
         bulletwidth[7] = getWidth(bulletmap[6], bulletmap[7], bulletmap[0]);
         
         //cout << bulletwidth[0] << " " << bulletwidth[1] << " " << bulletwidth[2] << " "
         //<< bulletwidth[3] << " " << bulletwidth[4] << " " << bulletwidth[5] << " "  <<
         //bulletwidth[6] << " " << bulletwidth[7] << "\n";
         
         int jklol;
         int vj = 0;int look = 0;
         //now use the bulletwidth
         //if (p->getX() >= 400)
         //{
         
            for (jklol = 7;jklol >= 0;jklol--)
            {
               if (bulletwidth[jklol] > vj) {look = jklol;vj = bulletwidth[jklol];}
            }
         //}
         //else
         //{
            //for (jklol = 0;jklol <= 7;jklol++)
            //{
             //  if (bulletwidth[jklol] > vj) {look = jklol;vj = bulletwidth[jklol];}
           // }
         //}
            
         KeyState ks;
         //ks.setShift(true);
         ks.setZ(true);
         if (nearestbullet <= dna.getCarefulZone()) {ks.setShift(true);} 
         
    if (look == 0)
    {
       ks.setUp(true);
    }
    else if (look == 1)
    {
       ks.setUp(true);
       ks.setRight(true);
    }
    else if (look == 2)
    {
       ks.setRight(true);
    }
    else if (look == 3)
    {
       ks.setDown(true);
       ks.setRight(true);
    }
    else if (look == 4)
    {
       ks.setDown(true);
    }
    else if (look == 5)
    {
       ks.setDown(true);
       ks.setLeft(true);
    }
    else if (look == 6)
    {
       ks.setLeft(true);
    }
    else if (look == 7)
    {
       ks.setUp(true);
       ks.setLeft(true);
    }
    return ks;
         
         
         }
      */  
        
        
        //cout << state;
    
    //force add
    //BULLETS
    TwoVector forces(0, 0);
    list<Bullet>::iterator i;
    for(i=gs->lEnemyBullets.begin(); i != gs->lEnemyBullets.end();i++)
    {
       TwoVector v(i->getX() - p->getX(), i->getY() - p->getY());
       double dist = v.getLength();
       if (dist <= dna.getBulletSee(state))
       {
          dist-=i->getRadius();
          v = v.normalize();
          TwoVector vil = v;
          TwoVector w(i->effvelx, i->effvely);
          w = w.normalize();
          double dprod = (v.getX() * w.getX()) + (v.getY() * w.getY());
          dprod *= -1;
          dprod += 1;dprod *= .5;dprod += .5; //get velocity factor
          //if (dprod < .5) {dprod = 1;}
          //double dprod = 1;
       

             v = v.scale(dna.getEBulletRepel(state)/(pow(dist,dna.getEBulletRepelPower(state))));
             forces.setX(forces.getX()-(v.getX()*dprod));
             forces.setY(forces.getY()+(v.getY()*dprod));
       
             v = vil;
             
             v = v.scale(dna.getEBulletAttract(state)/(pow(dist,dna.getEBulletAttractPower(state))));
             forces.setX(forces.getX()+v.getX());
             forces.setY(forces.getY()-v.getY());
       }
       
    }
    
    //ITEM FORCES
    list<Item*>::iterator ite;
    double inowx = -100; double inowy = -100;
    int ilooking = 0;
    for(ite=gs->lItems.begin(); ite != gs->lItems.end();ite++)
    {
          if (items == 0) {break;}
          //if ((*n)->hp <= aa) {aa = (*n)->hp; nowx = (*n)->x;}
          ilooking++;
          if (ilooking == itemtarget) {inowx = (*ite)->getX();inowy = (*ite)->getY();break;}
          
    }
      // cout << inowx << ", " << inowy << "\n";
       TwoVector vi(inowx - p->getX(), inowy - p->getY());
       double dist = vi.getLength();
       //if (dist <= dna.getBulletSee(state))
       //{
          vi = vi.normalize();
          TwoVector tvi = vi;
          //TwoVector w(i->effvelx, i->effvely);
          //w = w.normalize();
          //double dprod = (v.getX() * w.getX()) + (v.getY() * w.getY());
          //dprod *= -1;
          //dprod += 1;dprod *= .5;dprod += .5; //get velocity factor
          //if (dprod < .5) {dprod = 1;}
          //double dprod = 1;
       
          if (items > 0)
          {
               //cout << "in item";
             vi = vi.scale(dna.getPowerUpRepel(state)/(pow(dist,dna.getPowerUpRepelPower(state))));
             forces.setX(forces.getX()-vi.getX());
             forces.setY(forces.getY()+vi.getY());

       
          //vi = vi.normalize();
             vi = tvi;
             
             vi = vi.scale(dna.getPowerUpAttract(state)/(pow(dist,dna.getPowerUpAttractPower(state))));
             forces.setX(forces.getX()+vi.getX());
             forces.setY(forces.getY()-vi.getY());

         }
       //}
       
    
    //GAMELINE FORCES
    gameline = dna.getGameLine();
    list<Enemy*>::iterator k;
    double aa = 0;
    for(k=gs->lEnemies.begin(); k != gs->lEnemies.end();k++)
    {
       if ((*k)->active)
       {
          if ((*k)->y > aa) {aa = (*k)->y;}
       }
    }
    double effectivegameline = ((600 - aa) * gameline) + aa;
    dist = (p->getY()-effectivegameline);  

        forces.setY(forces.getY()+dna.getWLineAttract(state)*(pow(dist,dna.getWLineAttractPower(state))));

        forces.setY(forces.getY()-dna.getWLineRepel(state)*(pow(dist,dna.getWLineRepelPower(state))));

    //ENEMY FORCES
    list<Enemy*>::iterator n;
    //aa = 10000;
    double nowx = -100;
    int tlooking = 0;
    for(n=gs->lEnemies.begin(); n != gs->lEnemies.end();n++)
    {
       if (enemies == 0) {break;}
       if ((*n)->active)
       {
          //if ((*n)->hp <= aa) {aa = (*n)->hp; nowx = (*n)->x;}
          tlooking++;
          if (tlooking == enemytarget) {nowx = (*n)->x;break;}
       }
    }
    if (nowx < 0) {nowx = 300;}

        nowx += (5 - airan.nextDouble(10));
       dist = (p->getX()-nowx);  
       //cout << dist << "\n";
       if (fabs(dist) >= 2.5)
       { 
           forces.setX(forces.getX()-dna.getELineAttract(state)*(pow(dist,dna.getELineRepelPower(state))));
          
           forces.setX(forces.getX()+dna.getELineRepel(state)*(pow(dist,dna.getELineRepelPower(state))));
       }
    
    
    //CUT OFF IF FORCE UNDER A CERTAIN LIMIT.
    if (fabs(forces.getX()) < .4) {forces.setX(0);}
    if (fabs(forces.getY()) < .4) {forces.setY(0);} 
    //interpret results and set keys
    double thet = atan2(forces.getY(), forces.getX());
    KeyState ks;
    
   /* double z = airan.nextDouble(1.0);
    if (z > (1.0 - jitterprobability))
    {
        z = airan.nextDouble(1.0);
        if (z > .75)
        {
            ks.setRight(true);
        }
        else if (z > .5)
        {
            ks.setLeft(true);
        }
        else if (z > .25)
        {
            ks.setDown(true);
        }
        else if (z >= 0)
        {
            ks.setUp(true);
        }
        ks.setZ(true);
        return ks;
    }*/
    
    //IF NO FORCES, LET UP ON ALL DIRECTION KEYS
    if (forces.getLength() == 0)
    {
        ks.setUp(false);
        ks.setDown(false);
        ks.setLeft(false);
        ks.setRight(false);
        ks.setZ(true);
        return ks;
    }
    
    //CALL THE ANGLE->8DIR FUNCTION
    int direc = getDirection(thet);
    
    //USE THE OUTPUT VALUE TO DETERMINE WHAT KEYS TO PRESS
    if (direc == 0)
    {
       ks.setUp(true);
    }
    else if (direc == 1)
    {
       ks.setUp(true);
       ks.setRight(true);
    }
    else if (direc == 2)
    {
       ks.setRight(true);
    }
    else if (direc == 3)
    {
       ks.setDown(true);
       ks.setRight(true);
    }
    else if (direc == 4)
    {
       ks.setDown(true);
    }
    else if (direc == 5)
    {
       ks.setDown(true);
       ks.setLeft(true);
    }
    else if (direc == 6)
    {
       ks.setLeft(true);
    }
    else if (direc == 7)
    {
       ks.setUp(true);
       ks.setLeft(true);
    }
    
    //SHOULD SHIFT (FOCUS) BE HELD?
    if (nearestbullet <= dna.getCarefulZone()) {ks.setShift(true);}
    ks.setZ(true);
    
    return ks;
}
