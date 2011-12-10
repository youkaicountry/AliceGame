#include <list>
#include "player.h"
#include <vector>
#include "gamespace.h"
#include "keystate.h"
#include <Math.h>
#include "barrage.h"
#include "twovector.h"
#include "random.h"
#include "item.h"

#include "myenemies.h"

enum {GS_CONTINUE, GS_DEAD, GS_LEVELUP};

GameSpace::GameSpace(int slevel, double left, double right, double top, double bottom, int seed, bool iSim)
{
   isSim = iSim;
   lastcycle = 100000;
    cycle = 1;
    level = slevel;  //whatever calculations in setting up the level
                     //are done here;
    
    gsran.setSeed(seed);                 
    screenleft = left;screenright = right;screentop = top;screenbottom = bottom;
    
    //Random r;
    for (int da = 0;da < 250; da++)
    {
       lStars.push_back(Star(gsran.nextDouble(800),gsran.nextDouble(600),gsran.nextDouble(100)));
    }
    
    Barrage b;
    //TEST 2
    //these two little shits have an INITIAL outward velocity enforced by the outcircle,
    //and they have a rotational velocity given... but they have NO actual radial
    //velocity, so they produce an interesting pattern.
    /*b.addOutCircleRotate(01, 40, 0, .012, 0,Bullet(0.0,0.0,0.0,0.0,0.0,0.0,true,0.0,0.0,1,0,0,0,5.0,5),0);
    b.addOutCircleRotate(01, 40, 0, .012, 0,Bullet(0.0,0.0,0.0,0.0,0.0,0.0,true,0.0,0.0,-1,0,0,0,5.0,6),0);
    b.addOutCircleRotate(5,22,0,0,0,Bullet(0.0,0.0,0.0,0.0,0.0,0.0,true,0.0,0.0,0.0,.006,0.0,1.1,5,7),0);
    b.addOutCircleRotate(5,22,0,0,0,Bullet(0.0,0.0,0.0,0.0,0.0,0.0,true,0.0,0.0,0.0,-.006,0.0,1.1,5,7),0);
     b.addOutCircleRotate(25,22,0,0,0,Bullet(0.0,0.0,0.0,0.0,0.0,0.0,true,0.0,0.0,0.0,.006,0.0,1.1,5,7),0);
    b.addOutCircleRotate(25,22,0,0,0,Bullet(0.0,0.0,0.0,0.0,0.0,0.0,true,0.0,0.0,0.0,-.006,0.0,1.1,5,7),0);
    b.addOutCircleRotate(50,22,0,0,0,Bullet(0.0,0.0,0.0,0.0,0.0,0.0,true,0.0,0.0,0.0,.006,0.0,1.1,5,7),0);
    b.addOutCircleRotate(50,22,0,0,0,Bullet(0.0,0.0,0.0,0.0,0.0,0.0,true,0.0,0.0,0.0,-.006,0.0,1.1,5,7),0);
    b.addOutCircleRotate(75,22,0,0,0,Bullet(0.0,0.0,0.0,0.0,0.0,0.0,true,0.0,0.0,0.0,.006,0.0,1.1,5,7),0);
    b.addOutCircleRotate(75,22,0,0,0,Bullet(0.0,0.0,0.0,0.0,0.0,0.0,true,0.0,0.0,0.0,-.006,0.0,1.1,5,7),0);
    //this thing creates the barrage
    b.getBarrage(&lEnemyBullets, 400, 200);*/ 
    
    
   
   //INITIALIZE THE LEVEL (PLACING ENEMIES)
    int wave1 = 300;
    lEnemies.push_back(new leftfodder( 20, -10, wave1+00, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new leftfodder( 20, -10, wave1+25, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new leftfodder( 20, -10, wave1+50, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new leftfodder( 20, -10, wave1+75, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new rightfodder(780,-10, wave1+100, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new rightfodder(780,-10, wave1+125, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new rightfodder(780,-10, wave1+150, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new rightfodder(780,-10, wave1+175, &lEnemyBullets, &thePlayer));
    
    int wave2 = 2800;
    
    lEnemies.push_back(new spout(-10, 30, wave2+0, &lEnemyBullets, &thePlayer, .8));
    lEnemies.push_back(new spout(810, 30, wave2+0, &lEnemyBullets, &thePlayer, -.8));
    lEnemies.push_back(new spout(-10, 120, wave2+100, &lEnemyBullets, &thePlayer, 1.15));
    lEnemies.push_back(new spout(810, 120, wave2+100, &lEnemyBullets, &thePlayer, -1.15));
    lEnemies.push_back(new spout(-10, 10, wave2+200, &lEnemyBullets, &thePlayer, 1.70));

    int wave3 = 1000;
    //int wave3 = 100;
    
    lEnemies.push_back(new sprayer(-10, 80, wave3+0, &lEnemyBullets, &thePlayer, .6));
    lEnemies.push_back(new sprayer(-10, 40, wave3+0, &lEnemyBullets, &thePlayer, 1.70));
    lEnemies.push_back(new sprayer(810, 80, wave3+0, &lEnemyBullets, &thePlayer, -.6));
    
    lEnemies.push_back(new ferret(150, -10, wave3+150, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new ferret(650, -10, wave3+150, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new ferret(400, -30, wave3+150, &lEnemyBullets, &thePlayer));
    
    lEnemies.push_back(new wall(150, -30, wave3+300, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new wall(650, -30, wave3+300, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new wall(300, -150, wave3+300, &lEnemyBullets, &thePlayer));
    lEnemies.push_back(new wall(500, -150, wave3+300, &lEnemyBullets, &thePlayer));
    


/*
   lEnemies.push_back(new smallblue(-20, 30, 300, &lEnemyBullets, &thePlayer));
*/
    return;
}

GameSpace::~GameSpace()
{
    //CLEAR INIT OBJECTS
    list<Enemy*>::iterator k;
    for(k=lEnemies.begin(); k != lEnemies.end(); k++)
    {
       delete (*k);
    } 
    
    list<Item*>::iterator i;
    for(i=lItems.begin(); i != lItems.end(); i++)
    {
       delete (*i);
    }  
    return;
}

int GameSpace::updateGameState(KeyState ks)
{
    //UPDATE PLAYER
    //position
    
    //QUICK AND DIRTY INTEGRATOR ON PLAYER 
    cycle++;
    double px, py, at; px = 0; py = 0;
    if (ks.isShift()) {thePlayer.setSpeed(1.5);} else {thePlayer.setSpeed(2.3);}
    if (ks.isUp()) {py -= 1;}
    if (ks.isDown()) {py += 1;}
    if (ks.isRight()) {px += 1;}
    if (ks.isLeft()) {px -= 1;}
    at = sqrt(px*px+py*py);
    if (at != 0)
    {
        px /= at;
        py /= at;
    }
    px *= thePlayer.getSpeed();
    py *= thePlayer.getSpeed();
    thePlayer.xvel *= .5; //FRICTION
    thePlayer.yvel *= .5; //FRICTION
    thePlayer.xvel += px;
    thePlayer.yvel += py;
    
    thePlayer.setX(thePlayer.getX()+thePlayer.xvel);
    thePlayer.setY(thePlayer.getY()+thePlayer.yvel);
    //shooting
    //THIS TAKES CARE OF HOW THE PLAYER SHOOTS FOR VARIOUS POWER VALUES
    if (ks.isZ())
    {
       if (thePlayer.getRecoilA() == 0)
       {
           //shooting code (takes power into account
           if (thePlayer.getPower() >= 0)
           {
              lFriendlyBullets.push_back(Bullet(thePlayer.getX(), thePlayer.getY()-18, 0, 0, 0, -10, 5, 2.0, 2)); 
           }
           if (thePlayer.getPower() >= 32)
           {
              lFriendlyBullets.push_back(Bullet(thePlayer.getX()-8, thePlayer.getY()-2, 0, 0, 0, -7, 5, 2.0, 3)); 
              lFriendlyBullets.push_back(Bullet(thePlayer.getX()+8, thePlayer.getY()-2, 0, 0, 0, -7, 5, 2.0, 3));
           }
           thePlayer.setRecoilA(10);
       }
       if (thePlayer.getRecoilB() == 0)
       {
            if (thePlayer.getPower() >= 64)
            {
               lFriendlyBullets.push_back(Bullet(thePlayer.getX()-8, thePlayer.getY()-2, -.11, -.18, 0, -2.5, 5, 4.0, 4)); 
               lFriendlyBullets.push_back(Bullet(thePlayer.getX()+8, thePlayer.getY()-2, .11, -.18, 0, -2.5, 5, 4.0, 4));     
            }
            thePlayer.setRecoilB(15);
       } 
    }
    if (thePlayer.getRecoilA() > 0) {thePlayer.setRecoilA(thePlayer.getRecoilA()-1);}
    if (thePlayer.getRecoilB() > 0) {thePlayer.setRecoilB(thePlayer.getRecoilB()-1);}
    
    //MAKE SURE THE PLAYER DOESN'T ESCAPE!
    if (thePlayer.getX() < screenleft) {thePlayer.setX(screenleft);}
    if (thePlayer.getX() > screenright) {thePlayer.setX(screenright);}
    if (thePlayer.getY() < screentop) {thePlayer.setY(screentop);}
    if (thePlayer.getY() > screenbottom) {thePlayer.setY(screenbottom);}
    
    //UPDATE ENEMIES
    list<Enemy*>::iterator k;
    for(k=lEnemies.begin(); k != lEnemies.end();)
    {
       if ((*k)->update(&lEnemyBullets, &thePlayer, this) == true)
          {delete (*k);k = lEnemies.erase(k);}
      else
        k++;
    }  
    
    //UPDATE ITEMS
    list<Item*>::iterator z;
    for(z = lItems.begin(); z != lItems.end();)
    {
       (*z)->update();
       if (
        (((*z)->getX() + (*z)->getRadius()) < screenleft)  ||
        (((*z)->getX() - (*z)->getRadius()) > screenright) ||
        (((*z)->getY() + (*z)->getRadius()) < (screentop - 70))   ||
        (((*z)->getY() - (*z)->getRadius()) > screenbottom)
          )
           {delete (*z);z= lItems.erase(z);}
       else
          z++;
       
    }  
    
    //UPDATE BULLETS
    list<Bullet>::iterator i;
    for(i=lEnemyBullets.begin(); i != lEnemyBullets.end();)
    {
       i->update();
       if (
        ((i->getX() + i->getRadius()) < screenleft)  ||
        ((i->getX() - i->getRadius()) > screenright) ||
        ((i->getY() + i->getRadius()) < screentop)   ||
        ((i->getY() - i->getRadius()) > screenbottom)
          )
           {i=lEnemyBullets.erase(i);}
       else
          i++;
    }
    //FRIENDLY BULLETS
    list<Bullet>::iterator j;
    for(j=lFriendlyBullets.begin(); j != lFriendlyBullets.end();)
    {
       j->update();
       if ((j->getX() + j->getRadius()) < screenleft) {j=lFriendlyBullets.erase(j);}
       else if ((j->getX() - j->getRadius()) > screenright) {j=lFriendlyBullets.erase(j);}
       else if ((j->getY() + j->getRadius()) < screentop) {j=lFriendlyBullets.erase(j);}
       else if ((j->getY() - j->getRadius()) > screenbottom) {j=lFriendlyBullets.erase(j);}
       else
           j++;
    }
    //PARTICLES
    if (isSim == false)
    {
       list<Bullet>::iterator u;
       for(u=lParticles.begin(); u != lParticles.end();)
       {
          u->update();
          if ((u->getX() + u->getRadius()) < screenleft) {u=lFriendlyBullets.erase(u);}
          else if ((u->getX() - u->getRadius()) > screenright) {u=lFriendlyBullets.erase(u);}
          else if ((u->getY() + u->getRadius()) < screentop) {u=lFriendlyBullets.erase(u);}
          else if ((u->getY() - u->getRadius()) > screenbottom) {u=lFriendlyBullets.erase(u);}
          else
              u++;
       }
    }
    
    //check items collide with player
    list <Item*>::iterator f;
    for (f=lItems.begin(); f != lItems.end();)
    {
       TwoVector v((*f)->getX() - thePlayer.getX(),(*f)->getY() - thePlayer.getY());
       if (v.getLength() < ((*f)->getRadius() + 16))
       {
          (*f)->onPickup(&thePlayer);
          Item* it = (*f);
          f = lItems.erase(f);
          delete it;
       }
       else {f++;}
    }
    
    //check bullets collide with player
    if(thePlayer.invincibletime == 0)
    {
       list <Bullet>::iterator b;
       for (b=lEnemyBullets.begin(); b != lEnemyBullets.end();)
       {
          TwoVector v(b->getX() - thePlayer.getX(),b->getY() - thePlayer.getY());
          if (v.getLength() < (b->getRadius()))
          {
                thePlayer.invincibletime = 200;
                thePlayer.setLives(thePlayer.getLives()-1);
                thePlayer.setX(400);
                thePlayer.setY(550);
             //thePlayer.invincibletime--;
             //(*f)->onPickup(&thePlayer);
             b = lEnemyBullets.erase(b);
          }
          else {b++;}
       }
    }
    else {thePlayer.invincibletime--;}
    
    //check friendlybullet-enemy collisions
    list <Bullet>::iterator l;
    list <Enemy*>::iterator m;
    
    for(m=lEnemies.begin(); m != lEnemies.end(); m++)
    {
       for(l=lFriendlyBullets.begin(); l != lFriendlyBullets.end();)
       {
        
            TwoVector v((*m)->x - l->getX(),(*m)->y - l->getY());
            if (v.getLength() < ((*m)->radius + l->getRadius()) && (*m)->isHittable() == true)
            {
                (*m)->hp -= l->getDamage();
                
                thePlayer.setScore(thePlayer.getScore()+10); //increase player score by 10 for the shot hitting
                fx_explosion(l->getX(), l->getY(), 12, 2.0, 10);
                l = lFriendlyBullets.erase(l);
            }
            else {l++;}
        }  
    }
    
    
    
    if (cycle == lastcycle || thePlayer.getLives() < 0) 
    {
       //here set final play score
       if (thePlayer.getLives() < 0) {thePlayer.setLives(0);}
       thePlayer.setScore(thePlayer.getScore()+(300*thePlayer.getLives()));
       return 0;
    } //if game is over, return 0
    return 1;
}


//THIS GARBAGE JUST CYCLES THROUGH ALL OF THE LISTS OF CRAP AND SETS
//SPRITE NOTES FOR THEM
void GameSpace::getSprites(vector<SpriteNote>* vsn, KeyState ks) //returns list of sprite to be drawn
{
    //if (vsn->empty() == false) {vsn->clear();}   
    vsn->clear();
    
    //update sprite list for player
    if (thePlayer.invincibletime > 0)
    {
       vsn->push_back(SpriteNote((int)thePlayer.getX(), (int)thePlayer.getY(), thePlayer.invinciblesprite));
    }
    else
    {
       vsn->push_back(SpriteNote((int)thePlayer.getX(), (int)thePlayer.getY(), thePlayer.getSprite()));
    }
    
    if (ks.isShift())
    {
         vsn->push_back(SpriteNote((int)thePlayer.getX()+1, (int)thePlayer.getY(), 21));
    }
    
    //update sprite list for friendly bullets
    list<Bullet>::iterator j;
    for(j=lFriendlyBullets.begin(); j != lFriendlyBullets.end(); j++)
    {
       vsn->push_back(SpriteNote((int)j->getX(), (int)j->getY(), j->getSprite()));
    }
    
    //update sprite list for enemies
    list<Enemy*>::iterator k;
    for(k=lEnemies.begin(); k != lEnemies.end(); k++)
    {
        if ((*k)->isVisible())
        {
           vsn->push_back(SpriteNote((int)(*k)->x, (int)(*k)->y, (*k)->sprite));
        }
    }
    
    //update sprite list for items
    list<Item*>::iterator z;
    for(z=lItems.begin(); z != lItems.end(); z++)
    {
           vsn->push_back(SpriteNote((int)(*z)->getX(), (int)(*z)->getY(), (*z)->getSprite()));
    }   
     
    //update sprite list for enemy bullets
    list<Bullet>::iterator i;
    for(i=lEnemyBullets.begin(); i != lEnemyBullets.end(); i++)
    {
       vsn->push_back(SpriteNote((int)i->getX(), (int)i->getY(), i->getSprite()));
    }
    
    list<Bullet>::iterator u;
    for(u=lParticles.begin(); u != lParticles.end(); u++)
    {
       vsn->push_back(SpriteNote((int)u->getX(), (int)u->getY(), u->getSprite()));
    }
    

       
    return;

}

//THIS CODE GENERATES THE PARTICLES FROM KILLS
void GameSpace::fx_explosion(double x, double y, int n, double force, int sprite)
{
   if (isSim)
      return;
   double xforce = force, yforce = force*(4.0/3.0);
   for(int i=0;i<n;i++)
   {
      lParticles.push_back(Bullet(x, y, 0.0, .06+gsran.nextDouble(.03),
         xforce*(2.0*gsran.nextDouble()-1.0), -0.1-yforce*gsran.nextDouble(),
         1.0, 1.0, sprite));
   }
   return;
}
