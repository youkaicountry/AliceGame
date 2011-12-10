#ifndef _DNA__
#define _DNA__

#include "random.h"
#include <fstream.h>
#include <sstream>
#include <wchar.h>
#include <iostream.h>

template<class T>
inline T read(ifstream *in)
{
   T result;
   in->read((char *) (&result), sizeof(T));
   return result;
}

template<class T>
inline void write(ofstream *out, T value)
{
   T result;
   out->write((char *) (&value), sizeof(T));
   return;
}

class DNA
{
    public:
       DNA();
       ~DNA();
       
       Random ra;
       
       double gameline;
       double bulletpanic;
       int reactioncycles;
       //double bulletsee;
       double carefulzone;
       
       double bulletsee[3];
       
       double ebulletattract[3];
       double ebulletattractpower[3]; 
       double ebulletrepel[3];
       double ebulletrepelpower[3];
       
       double elineattract[3];
       double elineattractpower[3];
       double elinerepel[3];
       double elinerepelpower[3];
       
       double wlineattract[3];
       double wlineattractpower[3];
       double wlinerepel[3];
       double wlinerepelpower[3];
       
       double powerupattract[3];
       double powerupattractpower[3];
       double poweruprepel[3];
       double poweruprepelpower[3];

       //request the proper article, by listing the state:
       //0 = Powerup on screen
       //1 = enemies on screen
       //2 = none on screen
       int getReactionCycles();
       double getBulletSee(int state);
       double getBulletPanic();
       double getCarefulZone();
       double getGameLine();
       
       double getEBulletAttract(int state);
       double getEBulletAttractPower(int state);
       double getEBulletRepel(int state);
       double getEBulletRepelPower(int state);
       
       double getELineAttract(int state);
       double getELineAttractPower(int state);
       double getELineRepel(int state);
       double getELineRepelPower(int state);
       
       double getWLineAttract(int state);
       double getWLineAttractPower(int state);
       double getWLineRepel(int state);
       double getWLineRepelPower(int state);
       
       double getPowerUpAttract(int state);
       double getPowerUpAttractPower(int state);
       double getPowerUpRepel(int state);
       double getPowerUpRepelPower(int state);
       
       void load(char* filename);
       void save(char* filename);
       
       void clear();
       
       void putInt(ostream *out, int x);
       void putDouble(ostream *out, double x);
       
       //Genetic Algorithm garbage
       DNA mate(DNA partner, double crossover, int rlock);
       void mutate(double chance, double severity, int rlock);
       
};

#endif
