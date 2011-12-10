#ifndef _AIPLAYER__
#define _AIPLAYER__

#include "keystate.h"
#include "random.h"
#include "gamespace.h"
#include <vector>
#include <list>
#include "player.h"
#include "dna.h"

class AIPlayer
{
    private:
    int enemies;
    int enemytarget;
    int items;
    int itemtarget;
    int rps; //reactions per second  
    double bulletdangerradius;
    double weightvariance;
    double bulletmissprobability;
    double jitterprobability;
    
    double gameline; //percent below lowest enemy
    
    double bulletrepel;
    bool bulletrepelsquared;
    double bulletattract;
    bool bulletattractsquared;
    
    double screenedgerepel;
    bool screenedgerepelsquared;
    double screenedgeattract;
    bool screenedgeattractsquared;
    
    double gamelinerepel;
    bool gamelinesquared;
    double gamelineattract;
    bool gamelineattractsquared;
    
    double enemyrepel;
    bool enemysquared;
    double enemyattract;
    bool enemyattractsquared;
   
    Random airan;
    
    public:
    AIPlayer();
    ~AIPlayer();
    
    int getRps();
    void setRps(int newrps);
    
    double getBulletDangerRadius();
    void setBulletDangerRadius(double newbulletdangerradius);
    
    double getWeightVariance();
    void setWeightVariance(double newweightvariance);
    
    double getBulletMissProbability();
    void setBulletMissProbability(double newbulletmissprobability);
    
    KeyState update(GameSpace* gs, Player* p, DNA dna, KeyState kes); //main update method 
};

#endif
