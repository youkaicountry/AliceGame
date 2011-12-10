#ifndef _SHOOTERGAMESPACE__
#define _SHOOTERGAMESPACE__

#include <list.h>
#include <vector.h>

class GameSpace;
class NeoBullet;

#include "bullet.h"
#include "player.h"
#include "item.h"
#include "spritenote.h"
#include "keystate.h"
//#include "enemybase.h"
#include "star.h"
#include "random.h"
#include "neoenemy.h"
#include "cwaypoint.h"
#include "lua.hpp"
#include "pather.h"


using namespace std;

class GameSpace
{
    public:
    Player* thePlayer; //the player object in this gamespace
    int level;
    
    //NeoEnemy ne;
    
    list<Bullet> lParticles;
    list<NeoEnemy*> lEnemies;
    vector<CWayPoint*> vWayPoints;
    vector<NeoEnemy*> vTempEnemies;
    vector<NeoEnemy*> vTempEnemies2;
    
    vector<Pather*> vPathers;
    
    list<NeoBullet> lEnemyBullets;  //the list of enemy bullets
    list<NeoBullet> lFriendlyBullets;  //the list of player's bullets
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
    GameSpace(int slevel, double left, double right, double top, double bottom, int seed, bool iSim, char* filename, char* charfile);
    ~GameSpace();    
        
    int updateGameState(KeyState ks); //this will update the entire game
                                          //state... player, enemies, check
                                          //for collisions, etc. The value
                                          //returned indicates if the player
                                          //has died, or if the player has gone
                                          //to a new level.
                                          
    void getSprites(vector<SpriteNote>* vsn, SpriteNote* BG, KeyState ks); //this returns a vector of sprite notes
                                     //that the graphics engine can use to 
                                     //render the game. It will iterate through
                                     //each of the linked lists and fill the
                                     //vector with spritenotes.

// Special effects:  Functions whose name begins with fx_ are special effects
//   that have no function in terms of game mechanics.
   void fx_explosion(double x, double y, int n, double force, int sprite);
   
    static int l_setCycleInfo( lua_State* luaVM );
    static int l_addWayPoint( lua_State* luaVM);
    static int l_setDeathInfo( lua_State* luaVM);
    static int l_setHP(lua_State *luaVM);
    static int l_setInitVel( lua_State* luaVM);
    static int l_setSpeedPath( lua_State* luaVM);
    static int l_setTimedPath( lua_State* luaVM);
    
    static int l_addEnemy( lua_State* luaVM);
    static int l_setRadius( lua_State* luaVM);
    static int l_setSprite( lua_State* luaVM);
    static int l_setEHP( lua_State* luaVM);
    static int l_insertWayPoint( lua_State* luaVM);
    
    static int l_addPath( lua_State* luaVM);
    static int l_insertLine( lua_State* luaVM);
    
    static int l_addToLevel( lua_State* luaVM);
    
         
};

#endif
