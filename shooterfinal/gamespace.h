#ifndef _SHOOTERGAMESPACE__
#define _SHOOTERGAMESPACE__

#include <list>
#include <vector>

class GameSpace;

#include "bullet.h"
#include "player.h"
#include "item.h"
#include "spritenote.h"
#include "keystate.h"
#include "enemybase.h"
#include "star.h"
#include "random.h"

using namespace std;

class GameSpace
{
    public:
    Player thePlayer; //the player object in this gamespace
    int level;
    
    list<Bullet> lParticles;
    list<Enemy*> lEnemies;
    list<Bullet> lEnemyBullets;  //the list of enemy bullets
    list<Bullet> lFriendlyBullets;  //the list of player's bullets
    list<Item*> lItems;   //list of items (note that Item is a base class, and
                         //the contents of this list will be polymorphed objects
                         //that all run update() each cycle, and run onPickup()
                         //when they are picked up.
    list<Star> lStars;
    double screenleft, screenright, screentop, screenbottom;
    private:
    bool isSim;
    
    
    public:
    
    int seed;
    int cycle;
    int lastcycle;
    Random gsran;
    GameSpace(int slevel, double left, double right, double top, double bottom, int seed, bool iSim);
    ~GameSpace();    
        
    int updateGameState(KeyState ks); //this will update the entire game
                                          //state... player, enemies, check
                                          //for collisions, etc. The value
                                          //returned indicates if the player
                                          //has died, or if the player has gone
                                          //to a new level.
                                          
    void getSprites(vector<SpriteNote>* vsn, KeyState ks); //this returns a vector of sprite notes
                                     //that the graphics engine can use to 
                                     //render the game. It will iterate through
                                     //each of the linked lists and fill the
                                     //vector with spritenotes.

// Special effects:  Functions whose name begins with fx_ are special effects
//   that have no function in terms of game mechanics.
   void fx_explosion(double x, double y, int n, double force, int sprite);
         
};

#endif
