#include <list>
#include "player.h"
#include <vector.h>
#include "keystate.h"
#include <Math.h>
#include "barrage.h"
#include "twovector.h"
#include "random.h"
#include "item.h"
#include "cwaypoint.h"
#include "lua.hpp"
#include "pather.h"
#include "bullet.h"

//#include "myenemies.h"
#include "neoenemy.h"
#include "gamespace.h"
#include "neobullet.h"

enum {GS_CONTINUE, GS_DEAD, GS_LEVELUP};

GameSpace::GameSpace(int slevel, double left, double right, double top, double bottom, int seed, bool iSim, char* filename, char* charfile)
{
   thePlayer = new Player(charfile);
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
    b.getBarrage(&lNeoEnemyBullets, 400, 200);*/ 
    
    
   
   //INITIALIZE THE LEVEL (PLACING ENEMIES)
    /*int wave1 = 300;
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
    lEnemies.push_back(new wall(500, -150, wave3+300, &lEnemyBullets, &thePlayer));*/
    
    
    lua_State* LStat = luaL_newstate();
    luaL_openlibs(LStat);
   
   
   //loadLuaLib("lib", LStat);
   
   int s = luaL_loadfile(LStat, filename);

   //TreeTexture::registerOperations(LStat);
   
   //PATH STUFF
   lua_pushstring(LStat, "newPath");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_addPath, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "addPLine");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_insertLine, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   //WAYPOINT STUFF
   lua_pushstring(LStat, "setWPCycleInfo");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setCycleInfo, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "newWayPoint");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_addWayPoint, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "setWPDeathInfo");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setDeathInfo, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "setWPHP");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setHP, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "setWPInitVel");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setInitVel, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "setWPTimedPath");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setTimedPath, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);

   lua_pushstring(LStat, "setWPSpeedPath");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setSpeedPath, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   
   //ENEMY STUFF
   lua_pushstring(LStat, "newEnemy");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_addEnemy, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "setERadius");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setRadius, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "setESprite");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setSprite, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "setEHP");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_setEHP, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   lua_pushstring(LStat, "addEWayPoint");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_insertWayPoint, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   
   
   //LEVEL STUFF
   lua_pushstring(LStat, "addEToLevel");
   lua_pushlightuserdata(LStat, this);
   lua_pushcclosure(LStat, l_addToLevel, 1);
   lua_settable(LStat, LUA_GLOBALSINDEX);
   

    s = lua_pcall(LStat, 0, 0, 0);
   
   lua_getfield(LStat, LUA_GLOBALSINDEX, "setupLevel");          /* function to be called */
   lua_pushnumber(LStat, 69);
   lua_pcall(LStat, 1, LUA_MULTRET, 0);
   
   
    //CWayPoint* wp1 = new CWayPoint();
    //wp1->setCycleInfo(1000, 1);
    //vWayPoints[0]->setInitVel(1, 1);
    //wp1->setDeathInfo(10, true, 0);
    //vWayPoints.push_back(wp1);

    //NeoEnemy* ne1 = new NeoEnemy();
    //ne1->activatecycles = 10;
    //ne1->addWayPoint(vWayPoints[0]);
    //lEnemies.push_back(ne1);
    
    for(int aj = 0;aj < vTempEnemies2.size(); aj++)
    {
       lEnemies.push_back(vTempEnemies2[aj]);
    }
    
    NeoBullet* nb = new NeoBullet(this);
    nb->x = 50;
    nb->y = 50;
    nb->sprite = 4;
    
    lEnemyBullets.push_back(*nb);


/*
   lEnemies.push_back(new smallblue(-20, 30, 300, &lEnemyBullets, &thePlayer));
*/
    return;
}

GameSpace::~GameSpace()
{
    //CLEAR INIT OBJECTS
    list<NeoEnemy*>::iterator k;
    for(k=lEnemies.begin(); k != lEnemies.end(); k++)
    {
       delete (*k);
    } 
    
    list<Item*>::iterator i;
    for(i=lItems.begin(); i != lItems.end(); i++)
    {
       delete (*i);
    } 
    
    delete thePlayer;
     
    return;
}

int GameSpace::updateGameState(KeyState ks)
{
   //printf("SIZEOFE: %d\n", lEnemies.size());
    //UPDATE PLAYER
    //position
    
    //QUICK AND DIRTY INTEGRATOR ON PLAYER 
    cycle++;
    double px, py, at; px = 0; py = 0;
    if (ks.isShift()) {thePlayer->setSpeed(1.5);} else {thePlayer->setSpeed(2.3);}
    if (ks.isUp()) {py -= 1;}
    if (ks.isDown()) {py += 1;}
    if (ks.isRight()) 
    {
         px += 1;
         if(thePlayer->getRotation()<thePlayer->getRotationMax())
         {
            thePlayer->setRotation(thePlayer->getRotation()+thePlayer->getRotationSpeed());
         }
         else
         {
            thePlayer->setRotation(thePlayer->getRotationMax());
         }
   }
    if (ks.isLeft()) 
    {
         px -= 1;
         if(thePlayer->getRotation() > -(thePlayer->getRotationMax()))
         {
            thePlayer->setRotation(thePlayer->getRotation()-thePlayer->getRotationSpeed());
         }
         else
         {
            thePlayer->setRotation(-(thePlayer->getRotationMax()));
         }
    }
    if (px == 0 && thePlayer->getRotation() > 0)
    {
       thePlayer->setRotation(thePlayer->getRotation()-thePlayer->getRotationSpeed());
    }
    if (px == 0 && thePlayer->getRotation() < 0)
    {
       thePlayer->setRotation(thePlayer->getRotation()+thePlayer->getRotationSpeed());
    }
    at = sqrt(px*px+py*py);
    if (at != 0)
    {
        px /= at;
        py /= at;
    }
    px *= thePlayer->getSpeed();
    py *= thePlayer->getSpeed();
    thePlayer->xvel *= .5; //FRICTION
    thePlayer->yvel *= .5; //FRICTION
    thePlayer->xvel += px;
    thePlayer->yvel += py;
    
    thePlayer->setX(thePlayer->getX()+thePlayer->xvel);
    thePlayer->setY(thePlayer->getY()+thePlayer->yvel);
    //shooting
    //THIS TAKES CARE OF HOW THE PLAYER SHOOTS FOR VARIOUS POWER VALUES
    if (ks.isZ())
    {
       if (thePlayer->getRecoilA() == 0)
       {
           //shooting code (takes power into account
           if (thePlayer->getPower() >= 0)
           {
              //lFriendlyBullets.push_back(Bullet(thePlayer->getX(), thePlayer->getY()-18, 0, 0, 0, -10, 5, 2.0, 2)); 
           }
           if (thePlayer->getPower() >= 32)
           {
              //lFriendlyBullets.push_back(Bullet(thePlayer->getX()-8, thePlayer->getY()-2, 0, 0, 0, -7, 5, 2.0, 3)); 
              //lFriendlyBullets.push_back(Bullet(thePlayer->getX()+8, thePlayer->getY()-2, 0, 0, 0, -7, 5, 2.0, 3));
           }
           thePlayer->setRecoilA(10);
       }
       if (thePlayer->getRecoilB() == 0)
       {
            if (thePlayer->getPower() >= 64)
            {
               //lFriendlyBullets.push_back(Bullet(thePlayer->getX()-8, thePlayer->getY()-2, -.11, -.18, 0, -2.5, 5, 4.0, 4)); 
               //lFriendlyBullets.push_back(Bullet(thePlayer->getX()+8, thePlayer->getY()-2, .11, -.18, 0, -2.5, 5, 4.0, 4));     
            }
            thePlayer->setRecoilB(15);
       } 
    }
    if (thePlayer->getRecoilA() > 0) {thePlayer->setRecoilA(thePlayer->getRecoilA()-1);}
    if (thePlayer->getRecoilB() > 0) {thePlayer->setRecoilB(thePlayer->getRecoilB()-1);}
    
    //MAKE SURE THE PLAYER DOESN'T ESCAPE!
    if (thePlayer->getX() < screenleft) {thePlayer->setX(screenleft);}
    if (thePlayer->getX() > screenright) {thePlayer->setX(screenright);}
    if (thePlayer->getY() < screentop) {thePlayer->setY(screentop);}
    if (thePlayer->getY() > screenbottom) {thePlayer->setY(screenbottom);}
    
    //UPDATE ENEMIES
    list<NeoEnemy*>::iterator k;
    for(k=lEnemies.begin(); k != lEnemies.end();)
    {
       if ((*k)->update(thePlayer, this) == true)
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
    list<NeoBullet>::iterator i;
    for(i=lEnemyBullets.begin(); i != lEnemyBullets.end();)
    {
       i->update(thePlayer, this);
       if (
        ((i->x + i->radius) < screenleft)  ||
        ((i->x - i->radius) > screenright) ||
        ((i->y + i->radius) < screentop)   ||
        ((i->y - i->radius) > screenbottom)
          )
           {i=lEnemyBullets.erase(i);}
       else
          i++;
    }
    //FRIENDLY BULLETS
    list<NeoBullet>::iterator j;
    for(j=lFriendlyBullets.begin(); j != lFriendlyBullets.end();)
    {
       j->update(thePlayer, this);
       if ((j->x + j->radius) < screenleft) {j=lFriendlyBullets.erase(j);}
       else if ((j->x - j->radius) > screenright) {j=lFriendlyBullets.erase(j);}
       else if ((j->y + j->radius) < screentop) {j=lFriendlyBullets.erase(j);}
       else if ((j->y - j->radius) > screenbottom) {j=lFriendlyBullets.erase(j);}
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
          if ((u->getX() + u->getRadius()) < screenleft) {u=lParticles.erase(u);}
          else if ((u->getX() - u->getRadius()) > screenright) {u=lParticles.erase(u);}
          else if ((u->getY() + u->getRadius()) < screentop) {u=lParticles.erase(u);}
          else if ((u->getY() - u->getRadius()) > screenbottom) {u=lParticles.erase(u);}
          else
              u++;
       }
    }
    
    //check items collide with player
    list <Item*>::iterator f;
    for (f=lItems.begin(); f != lItems.end();)
    {
       TwoVector v((*f)->getX() - thePlayer->getX(),(*f)->getY() - thePlayer->getY());
       if (v.getLength() < ((*f)->getRadius() + 16))
       {
          (*f)->onPickup(thePlayer);
          Item* it = (*f);
          f = lItems.erase(f);
          delete it;
       }
       else {f++;}
    }
    
    //check bullets collide with player
    if(thePlayer->invincibletime == 0)
    {
       list <NeoBullet>::iterator b;
       for (b=lEnemyBullets.begin(); b != lEnemyBullets.end();)
       {
          TwoVector v(b->x - thePlayer->getX(),b->y - thePlayer->getY());
          if (v.getLength() < (b->radius))
          {
                thePlayer->invincibletime = 200;
                thePlayer->setLives(thePlayer->getLives()-1);
                thePlayer->setX(400);
                thePlayer->setY(550);
             //thePlayer->invincibletime--;
             //(*f)->onPickup(&thePlayer);
             b = lEnemyBullets.erase(b);
          }
          else {b++;}
       }
    }
    else {thePlayer->invincibletime--;}
    
    //check friendlybullet-enemy collisions
    list <NeoBullet>::iterator l;
    list <NeoEnemy*>::iterator m;
    
    for(m=lEnemies.begin(); m != lEnemies.end(); m++)
    {
       for(l=lFriendlyBullets.begin(); l != lFriendlyBullets.end();)
       {
        
            TwoVector v((*m)->x - l->x,(*m)->y - l->y);
            if (v.getLength() < ((*m)->radius + l->radius) && (*m)->isHittable() == true)
            {
                (*m)->hp -= l->damage;
                
                thePlayer->setScore(thePlayer->getScore()+10); //increase player score by 10 for the shot hitting
                fx_explosion(l->x, l->y, 12, 2.0, 10);
                l = lFriendlyBullets.erase(l);
            }
            else {l++;}
        }  
    }
    
    
    
    if (cycle == lastcycle || thePlayer->getLives() < 0) 
    {
       //here set final play score
       if (thePlayer->getLives() < 0) {thePlayer->setLives(0);}
       //thePlayer->setScore(thePlayer->getScore()+(300*thePlayer->getLives()));
       return 0;
    } //if game is over, return 0
    return 1;
}


//THIS GARBAGE JUST CYCLES THROUGH ALL OF THE LISTS OF CRAP AND SETS
//SPRITE NOTES FOR THEM
void GameSpace::getSprites(vector<SpriteNote>* vsn, SpriteNote* BG, KeyState ks) //returns list of sprite to be drawn
{
    //if (vsn->empty() == false) {vsn->clear();}   
    vsn->clear();
    //tdvsn->clear();
    
    //update sprite list for player
    if (thePlayer->invincibletime > 0)
    {
       vsn->push_back(SpriteNote((int)thePlayer->getX(), (int)thePlayer->getY(), thePlayer->getRotation(), 0, 0, thePlayer->getSpriteInvincible()));
    }
    else
    {
       vsn->push_back(SpriteNote((int)thePlayer->getX(), (int)thePlayer->getY(), thePlayer->getRotation(), 0, 0, thePlayer->getSprite1()));
    }
    
    if (ks.isShift())
    {
         vsn->push_back(SpriteNote((int)thePlayer->getX()+1, (int)thePlayer->getY(), 21));
    }
    
    //update sprite list for friendly bullets
    list<NeoBullet>::iterator j;
    for(j=lFriendlyBullets.begin(); j != lFriendlyBullets.end(); j++)
    {
       vsn->push_back(SpriteNote((int)j->x, (int)j->y, j->sprite));
    }
    
    //update sprite list for enemies
    list<NeoEnemy*>::iterator k;
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
    list<NeoBullet>::iterator i;
    for(i=lEnemyBullets.begin(); i != lEnemyBullets.end(); i++)
    {
       vsn->push_back(SpriteNote((int)i->x, (int)i->y, i->sprite));
    }
    
    list<Bullet>::iterator u;
    for(u=lParticles.begin(); u != lParticles.end(); u++)
    {
       vsn->push_back(SpriteNote((int)u->getX(), (int)u->getY(), u->getSprite()));
    }
    

    //BG
    //if (BG != NULL) {delete BG;}
    //BG = new SpriteNote(0, 0, thePlayer->getBGSprite());
    //printf("getting here\n");
    BG->sprite = thePlayer->getBGSprite();
    BG->x = 400-22;
    BG->y = 300-22;
    //tdvsn->push_back(SpriteNote(0, 0, 0));   
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

int GameSpace::l_setCycleInfo(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -4);
   int cycles = (int) lua_tonumber(luaVM, -3);
   int next = (int) lua_tonumber(luaVM, -2); //handle 2
   bool last = (bool)lua_tonumber(luaVM, -1);
   gs->vWayPoints[num]->setCycleInfo(cycles, next, last);
   lua_pushnumber(luaVM, 1);
   return 1;
}

int GameSpace::l_addWayPoint(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   CWayPoint* wp = new CWayPoint();
   int a = gs->vWayPoints.size();
   gs->vWayPoints.push_back(wp);
   //printf("SIZE: %d\n", gs->vWayPoints.size());
   lua_pushnumber(luaVM, a);
   return 1;
}

int GameSpace::l_setInitVel(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -3);
   double x = (double) lua_tonumber(luaVM, -2);
   double y = (double) lua_tonumber(luaVM, -1); //handle 2
   gs->vWayPoints[num]->setInitVel(x, y);
   lua_pushnumber(luaVM, 1);
   return 1;
}

int GameSpace::l_setDeathInfo(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -3);
   bool final= (bool) lua_tonumber(luaVM, -2); //handle 2
   int nextwp = (int) lua_tonumber(luaVM, -1); //handle 2
   gs->vWayPoints[num]->setDeathInfo(final, nextwp);
   lua_pushnumber(luaVM, 1);
   return 1;
}

int GameSpace::l_setHP(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -2);
   int hp= (int) lua_tonumber(luaVM, -1); //handle 2
   gs->vWayPoints[num]->setHP(hp);
   lua_pushnumber(luaVM, 1);
   return 1;
}

int GameSpace::l_addEnemy(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   NeoEnemy* ne = new NeoEnemy(gs);
   int a = gs->vTempEnemies.size();
   gs->vTempEnemies.push_back(ne);
   //printf("SIZE: %d\n", gs->vWayPoints.size());
   lua_pushnumber(luaVM, a);
   return 1;
}

int GameSpace::l_setSprite(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -2);
   int sprite = (int)lua_tonumber(luaVM, -1);
   gs->vTempEnemies[num]->sprite = sprite;
   //printf("SIZE: %d\n", gs->vWayPoints.size());
   lua_pushnumber(luaVM, 1);
   return 1;
}

int GameSpace::l_setEHP(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -2);
   int hp= (int)lua_tonumber(luaVM, -1);
   gs->vTempEnemies[num]->hp = hp;
   //printf("SIZE: %d\n", gs->vWayPoints.size());
   lua_pushnumber(luaVM, 1);
   return 1;
}

int GameSpace::l_setSpeedPath( lua_State* luaVM )
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -6);
   double endx = (double)lua_tonumber(luaVM, -5);
   double endy = (double)lua_tonumber(luaVM, -4);
   int path = (int)lua_tonumber(luaVM, -3);
   double speed = (double)lua_tonumber(luaVM, -2);
   int nextstate = (int)lua_tonumber(luaVM, -1);
   printf("lua nextstate: %d\n", nextstate);
   gs->vWayPoints[num]->addSpeedPath(path, endx, endy, speed, nextstate, gs->vPathers[path]);
   //printf("SIZE: %d\n", gs->vWayPoints.size());
   lua_pushnumber(luaVM, 1);
   return 1;
}

int GameSpace::l_setTimedPath( lua_State* luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -6);
   double endx = (double)lua_tonumber(luaVM, -5);
   double endy = (double)lua_tonumber(luaVM, -4);
   int path = (int)lua_tonumber(luaVM, -3);
   int cycles = (int)lua_tonumber(luaVM, -2);
   int nextstate = (int)lua_tonumber(luaVM, -1);
   gs->vWayPoints[num]->addTimedPath(path, endx, endy, cycles, nextstate, gs->vPathers[path]);
   //printf("SIZE: %d\n", gs->vWayPoints.size());
   lua_pushnumber(luaVM, 1);
   return 1;
}

int GameSpace::l_setRadius(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -2);
   double radius = (double)lua_tonumber(luaVM, -1);
   gs->vTempEnemies[num]->radius = radius;
   //printf("SIZE: %d\n", gs->vWayPoints.size());
   lua_pushnumber(luaVM, 1);
   return 1;
}

int GameSpace::l_insertWayPoint(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -2);
   int id = (int) lua_tonumber(luaVM, -1);
   gs->vTempEnemies[num]->vwaypoints.push_back(gs->vWayPoints[id]);
   lua_pushnumber(luaVM, 1);
   return 1;
}

int GameSpace::l_addToLevel(lua_State *luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int id = (int)lua_tonumber(luaVM, -4);
   int x = (int)lua_tonumber(luaVM, -3);
   int y = (int)lua_tonumber(luaVM, -2);
   int cycles = (int)lua_tonumber(luaVM, -1);
   int a = gs->vTempEnemies2.size();
   NeoEnemy* ne = new NeoEnemy(gs);
   ne->copyFrom(gs->vTempEnemies[id]);
   gs->vTempEnemies2.push_back(ne);
   gs->vTempEnemies2[a]->activatecycles = cycles;
   gs->vTempEnemies2[a]->x = x;
   gs->vTempEnemies2[a]->y = y;
   lua_pushnumber(luaVM, a);
   return 1;
}

int GameSpace::l_addPath( lua_State* luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   Pather* pa = new Pather();
   int a = gs->vPathers.size();
   gs->vPathers.push_back(pa);
   printf("HeRe\n");
   //printf("SIZE: %d\n", gs->vWayPoints.size());
   lua_pushnumber(luaVM, a);
}

int GameSpace::l_insertLine( lua_State* luaVM)
{
   GameSpace* gs = (GameSpace*)lua_touserdata(luaVM, lua_upvalueindex(1));
   int num = (int)lua_tonumber(luaVM, -3);
   double xend = (double) lua_tonumber(luaVM, -2);
   double yend = (double) lua_tonumber(luaVM, -1);
   printf("HeRe\n");
   gs->vPathers[num]->addLine(xend, yend);
   lua_pushnumber(luaVM, 1);
   return 1;
}

