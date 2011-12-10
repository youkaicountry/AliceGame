#include "dna.h"
#include "random.h"
#include <fstream.h>
#include <sstream>
#include <wchar.h>
#include <iostream.h>
#include <iosfwd> // for istream, ostream

DNA::DNA()
{
       reactioncycles = 3;
       bulletpanic = 6;
       //bulletsee = 80;
       carefulzone = 25;
       gameline = .65;
   
       bulletsee[0] = 60;
       bulletsee[1] = 80;
       bulletsee[2] = 10;
       
       ebulletattract[0] = 0;
       ebulletattractpower[0] = 1; 
       ebulletrepel[0] = 3200;
       ebulletrepelpower[0] = 2;
       
       elineattract[0] = .03;
       elineattractpower[0] = 1;
       elinerepel[0] = 0;
       elinerepelpower[0] = 1;
       
       wlineattract[0] = .02;
       wlineattractpower[0] = 1;
       wlinerepel[0] = 0;
       wlinerepelpower[0] = 1;
       
       powerupattract[0] = 4300;
       powerupattractpower[0] = 1;
       poweruprepel[0] = 0;
       poweruprepelpower[0] = 1;
       
       ebulletattract[1] = 0;
       ebulletattractpower[1] = 1; 
       ebulletrepel[1] = 3200;
       ebulletrepelpower[1] = 2;
       
       elineattract[1] = .03;
       elineattractpower[1] = 1;
       elinerepel[1] = 0;
       elinerepelpower[1] = 1;
       
       wlineattract[1] = .02;
       wlineattractpower[1] = 1;
       wlinerepel[1] = 0;
       wlinerepelpower[1] = 1;
       
       powerupattract[1] = 0;
       powerupattractpower[1] = 1;
       poweruprepel[1] = 0;
       poweruprepelpower[1] = 1;
       
       ebulletattract[2] = 0;
       ebulletattractpower[2] = 2; 
       ebulletrepel[2] = 3500;
       ebulletrepelpower[2] = 2.2;
       
       elineattract[2] = .03;
       elineattractpower[2] = 1;
       elinerepel[2] = 0;
       elinerepelpower[2] = 1;
       
       wlineattract[2] = .02;
       wlineattractpower[2] = 1;
       wlinerepel[2] = 0;
       wlinerepelpower[2] = 1;
       
       powerupattract[2] = 0;
       powerupattractpower[2] = 1;
       poweruprepel[2] = 0;
       poweruprepelpower[2] = 1;
       
       this->clear();
       //this->load("stock.dna");
    
    return;
}

DNA::~DNA()
{
    return;
}

void DNA::clear()
{
   bulletpanic = 0.0001;
   reactioncycles = 1;
   carefulzone = .0001;
   gameline = .65;
   
   int i = 0;
   
   for(i=0;i<3;i++)
   {
        bulletsee[i] = 0.0001;
   }
   
   for(i = 0;i < 3;i++)
      {
         ebulletattract[i] = .0001;
         ebulletattractpower[i] = 1;
         ebulletrepel[i] = 0.0001;
         ebulletrepelpower[i] = 1;
      }
      
      for(i = 0;i < 3;i++)
      {
         elineattract[i] = 0.0001;
         elineattractpower[i] = 1; 
         elinerepel[i] = 0.0001;
         elinerepelpower[i] = 1;
      }
      
      for(i = 0;i < 3;i++)
      {
         wlineattract[i] = 0.0001;
         wlineattractpower[i] = 1; 
         wlinerepel[i] = 0.0001;
         wlinerepelpower[i] = 1;
      }
      
      for(i = 0;i < 3;i++)
      {
         powerupattract[i] = 0.0001;
         powerupattractpower[i] = 1; 
         poweruprepel[i] = 0.0001;
         poweruprepelpower[i] = 1;
      }
   
   return;
}

//LOADS DNA FROM A FILE
void DNA::load(char* filename)
{
   ifstream myFile(filename, ios::in | ios::binary);
   bulletpanic = read<double>(&myFile);
   reactioncycles = read<int>(&myFile);
   carefulzone = read<double>(&myFile);
   gameline = read<double>(&myFile);
   
   int i = 0;
   
   for(i=0;i<3;i++)
   {
      bulletsee[i] = read<double>(&myFile);
   }
   
   for(i = 0;i < 3;i++)
      {
         ebulletattract[i] = read<double>(&myFile);
         ebulletattractpower[i] = read<double>(&myFile); 
         ebulletrepel[i] = read<double>(&myFile);
         ebulletrepelpower[i] = read<double>(&myFile);
      }
      
      for(i = 0;i < 3;i++)
      {
         elineattract[i] = read<double>(&myFile);
         elineattractpower[i] = read<double>(&myFile); 
         elinerepel[i] = read<double>(&myFile);
         elinerepelpower[i] = read<double>(&myFile);
      }
      
      for(i = 0;i < 3;i++)
      {
         wlineattract[i] = read<double>(&myFile);
         wlineattractpower[i] = read<double>(&myFile); 
         wlinerepel[i] = read<double>(&myFile);
         wlinerepelpower[i] = read<double>(&myFile);
      }
      
      for(i = 0;i < 3;i++)
      {
         powerupattract[i] = read<double>(&myFile);
         powerupattractpower[i] = read<double>(&myFile); 
         poweruprepel[i] = read<double>(&myFile);
         poweruprepelpower[i] = read<double>(&myFile);
      }
   
   
   myFile.close();
   
   return;
}

//SAVES THIS DNA TO A FILE
void DNA::save(char* filename)
{
   ofstream myFile(filename, ios::out | ios::binary);
   //for (int ii = 0;ii < replay.size();ii++)
   // {
   //   myFile << replay[ii];
   //}
   
   //for (int ii = 0;ii < replay.size();ii++)
      write<double>(&myFile, bulletpanic);
      write<int>(&myFile, reactioncycles);
      write<double>(&myFile, carefulzone);
      write<double>(&myFile, gameline);
      
      int i = 0;
      
      for(i = 0;i<3;i++)
      {
         write<double>(&myFile, bulletsee[i]);
      }
      
      for(i = 0;i < 3;i++)
      {
         write<double>(&myFile, ebulletattract[i]);
         write<double>(&myFile, ebulletattractpower[i]); 
         write<double>(&myFile, ebulletrepel[i]);
         write<double>(&myFile, ebulletrepelpower[i]);
      }
      
      for(i = 0;i < 3;i++)
      {
         write<double>(&myFile, elineattract[i]);
         write<double>(&myFile, elineattractpower[i]); 
         write<double>(&myFile, elinerepel[i]);
         write<double>(&myFile, elinerepelpower[i]);
      }
      
      for(i = 0;i < 3;i++)
      {
         write<double>(&myFile, wlineattract[i]);
         write<double>(&myFile, wlineattractpower[i]); 
         write<double>(&myFile, wlinerepel[i]);
         write<double>(&myFile, wlinerepelpower[i]);
      }
      
      for(i = 0;i < 3;i++)
      {
         write<double>(&myFile, powerupattract[i]);
         write<double>(&myFile, powerupattractpower[i]); 
         write<double>(&myFile, poweruprepel[i]);
         write<double>(&myFile, poweruprepelpower[i]);
      }
   
   
   myFile.close();
   return;
}

//MATES THIS DNA WITH ANOTHER DNA, AND RETURNS THE RESULTING CHILD DNA
DNA DNA::mate(DNA partner, double crossover, int rlock)
{
   DNA child;
   int i = 0;
   
   //printf("started mate");
   
   //Random hr;
   
   for (i = 0;i < 3;i++)
   {
      //printf("start sub\n");
      //printf("%g",child.ebulletattract);
      //if (hr.nextDouble(1.0) < 1) {printf("printed");}
      if (ra.nextDouble(1.0) < crossover) {child.ebulletattract[i] = ebulletattract[i];}
      else {child.ebulletattract[i] = partner.ebulletattract[i];}
      
      if (ra.nextDouble(1.0) < crossover) {child.ebulletattractpower[i] = ebulletattractpower[i];}
      else {child.ebulletattractpower[i] = partner.ebulletattractpower[i];}
      
      if (ra.nextDouble(1.0) < crossover) {child.ebulletrepel[i] = ebulletrepel[i];}
      else {child.ebulletrepel[i] = partner.ebulletrepel[i];}
      
      if (ra.nextDouble(1.0) < crossover) {child.ebulletrepelpower[i] = ebulletrepelpower[i];}
      else {child.ebulletrepelpower[i] = partner.ebulletrepelpower[i];}
      
   }
   
   //printf("m1");
   
   for (i = 0;i < 3;i++)
   {
      if (ra.nextDouble(1.0) < crossover) {child.elineattract[i] = this->elineattract[i];}
      else {child.elineattract[i] = partner.elineattract[i];}
      if (ra.nextDouble(1.0) < crossover) {child.elineattractpower[i] = this->elineattractpower[i];}
      else {child.elineattractpower[i] = partner.elineattractpower[i];}
      if (ra.nextDouble(1.0) < crossover) {child.elinerepel[i] = this->elinerepel[i];}
      else {child.elinerepel[i] = partner.elinerepel[i];}
      if (ra.nextDouble(1.0) < crossover) {child.elinerepelpower[i] = this->elinerepelpower[i];}
      else {child.elinerepelpower[i] = partner.elinerepelpower[i];}
   }
   
   //printf("m2");
   
   for (i = 0;i < 3;i++)
   {
      if (ra.nextDouble(1.0) < crossover) {child.wlineattract[i] = this->wlineattract[i];}
      else {child.wlineattract[i] = partner.wlineattract[i];}
      if (ra.nextDouble(1.0) < crossover) {child.wlineattractpower[i] = this->wlineattractpower[i];}
      else {child.wlineattractpower[i] = partner.wlineattractpower[i];}
      if (ra.nextDouble(1.0) < crossover) {child.wlinerepel[i] = this->wlinerepel[i];}
      else {child.wlinerepel[i] = partner.wlinerepel[i];}
      if (ra.nextDouble(1.0) < crossover) {child.wlinerepelpower[i] = this->wlinerepelpower[i];}
      else {child.wlinerepelpower[i] = partner.wlinerepelpower[i];}
   }
   
   //printf("m3");
   
   for (i = 0;i < 3;i++)
   {
      if (ra.nextDouble(1.0) < crossover) {child.powerupattract[i] = this->powerupattract[i];}
      else {child.powerupattract[i] = partner.powerupattract[i];}
      if (ra.nextDouble(1.0) < crossover) {child.powerupattractpower[i] = this->powerupattractpower[i];}
      else {child.powerupattractpower[i] = partner.powerupattractpower[i];}
      if (ra.nextDouble(1.0) < crossover) {child.poweruprepel[i] = this->poweruprepel[i];}
      else {child.poweruprepel[i] = partner.poweruprepel[i];}
      if (ra.nextDouble(1.0) < crossover) {child.poweruprepelpower[i] = this->poweruprepelpower[i];}
      else {child.poweruprepelpower[i] = partner.poweruprepelpower[i];}
   }
   
  //printf("m4");
   
   if (ra.nextDouble(1.0) < crossover) {child.bulletpanic = this->bulletpanic;}
   else {child.bulletpanic = partner.bulletpanic;}
   if (ra.nextDouble(1.0) < crossover) {child.reactioncycles = this->reactioncycles;}
   else {child.reactioncycles = partner.reactioncycles;}
   
   for (i = 0;i < 3;i++)
   {
      if (ra.nextDouble(1.0) < crossover) {child.bulletsee[i] = this->bulletsee[i];}
      else {child.bulletsee[i] = partner.bulletsee[i];}
   }
   
   if (ra.nextDouble(1.0) < crossover) {child.carefulzone = this->carefulzone;}
   else {child.carefulzone = partner.carefulzone;}
   if (ra.nextDouble(1.0) < crossover) {child.gameline = this->gameline;}
   else {child.gameline = partner.gameline;}
   
   
   if (rlock != -1) {child.reactioncycles = rlock;}
   //printf("end mate\n");
   
   return child;
}

//MUTATES THIS DNA
void DNA::mutate(double chance, double severity, int rlock)
{
   int i = 0;
   
   Random hr;
   
   for (i = 0;i < 3;i++)
   {
      if (ra.nextDouble(1.0) < chance) {ebulletattract[i] += (10*severity-ra.nextDouble(10*severity*2));}
      if (ra.nextDouble(1.0) < chance) {ebulletattractpower[i] += (.05*severity-ra.nextDouble(.05*severity*2));}
      if (ra.nextDouble(1.0) < chance) {ebulletrepel[i] += (10*severity-ra.nextDouble(10*severity*2));}
      if (ra.nextDouble(1.0) < chance) {ebulletrepelpower[i] += (.05*severity-ra.nextDouble(.05*severity*2));}
      if (ebulletattract[i] <= 0) {ebulletattract[i] = .0001;}
      //if (ebulletattractpower[i] <= 0) {ebulletattractpower[i] = 0;}
      if (ebulletrepel[i] <= 0) {ebulletrepel[i] = .0001;}
      //if (ebulletrepelpower[i] <= 0) {ebulletrepelpower[i] = 0;}
   }
   
   for (i = 0;i < 3;i++)
   {
      if (ra.nextDouble(1.0) < chance) {powerupattract[i] += (10*severity-ra.nextDouble(10*severity*2));}
      if (ra.nextDouble(1.0) < chance) {powerupattractpower[i] += (.05*severity-ra.nextDouble(.05*severity*2));}
      if (ra.nextDouble(1.0) < chance) {poweruprepel[i] += (10*severity-ra.nextDouble(10*severity*2));}
      if (ra.nextDouble(1.0) < chance) {poweruprepelpower[i] += (.05*severity-ra.nextDouble(.05*severity*2));}
      if (powerupattract[i] <= 0) {powerupattract[i] = .0001;}
      //if (powerupattractpower[i] <= 0) {powerupattractpower[i] = 0;}
      if (poweruprepel[i] <= 0) {poweruprepel[i] = .0001;}
      //if (poweruprepelpower[i] <= 0) {poweruprepelpower[i] = 0;}
   }
   
   for (i = 0;i < 3;i++)
   {
      if (ra.nextDouble(1.0) < chance) {elineattract[i] += (10*severity-ra.nextDouble(10*severity*2));}
      if (ra.nextDouble(1.0) < chance) {elineattractpower[i] += (.05*severity-ra.nextDouble(.05*severity*2));}
      if (ra.nextDouble(1.0) < chance) {elinerepel[i] += (10*severity-ra.nextDouble(10*severity*2));}
      if (ra.nextDouble(1.0) < chance) {elinerepelpower[i] += (.05*severity-ra.nextDouble(.05*severity*2));}
      if (elineattract[i] <= 0) {elineattract[i] = .0001;}
      //if (elineattractpower[i] <= 0) {elineattractpower[i] = 0;}
      if (elinerepel[i] <= 0) {elinerepel[i] = .0001;}
      //if (elinerepelpower[i] <= 0) {elinerepelpower[i] = 0;}
   }
   
   for (i = 0;i < 3;i++)
   {
      if (ra.nextDouble(1.0) < chance) {wlineattract[i] += (10*severity-ra.nextDouble(10*severity*2));}
      if (ra.nextDouble(1.0) < chance) {wlineattractpower[i] += (.05*severity-ra.nextDouble(.05*severity*2));}
      if (ra.nextDouble(1.0) < chance) {wlinerepel[i] += (10*severity-ra.nextDouble(10*severity*2));}
      if (ra.nextDouble(1.0) < chance) {wlinerepelpower[i] += (.05*severity-ra.nextDouble(.05*severity*2));}
      if (wlineattract[i] <= 0) {wlineattract[i] = .0001;}
      //if (wlineattractpower[i] <= 0) {wlineattractpower[i] = 0;}
      if (wlinerepel[i] <= 0) {wlinerepel[i] = .0001;}
      //if (wlinerepelpower[i] <= 0) {wlinerepelpower[i] = 0;}
   }
   
      if (ra.nextDouble(1.0) < chance) {bulletpanic += (.01*severity-ra.nextDouble(10*severity*2));}
      if (ra.nextDouble(1.0) < chance) {reactioncycles += ((int)(2*severity-ra.nextDouble(severity*4)));}
      
      for (i = 0;i<3;i++)
      {
         if (ra.nextDouble(1.0) < chance) {bulletsee[i] += (.2*severity-ra.nextDouble(10*severity*2));}
         if (bulletsee[i] <= 0) {bulletsee[i] = .0001;}
      }
      
      if (ra.nextDouble(1.0) < chance) {carefulzone += (.1*severity-ra.nextDouble(.05*severity*2));}
      if (ra.nextDouble(1.0) < chance) {gameline += (.007*severity-ra.nextDouble(.05*severity*2));}
   
   if (gameline >= .75) {gameline = .75;}
   if (gameline <= .2) {gameline = .2;}
   if (bulletpanic <= 1) {bulletpanic = 1;}
   if (reactioncycles <= 1) {reactioncycles = 1;}
   
   if (rlock != -1) {reactioncycles = rlock;}
   
   if (carefulzone <= 1) {carefulzone = 1;}
   
   
   
   
   return;
}

double DNA::getBulletPanic()
{
   return bulletpanic;
}

double DNA::getGameLine()
{
   return gameline;
}

double DNA::getCarefulZone()
{
   return carefulzone;
}

int DNA::getReactionCycles()
{
   return reactioncycles;
}

double DNA::getBulletSee(int state)
{
   return bulletsee[state];
}

double DNA::getEBulletAttract(int state)
{
    return ebulletattract[state];
}

double DNA::getEBulletAttractPower(int state)
{
    return ebulletattractpower[state];
}

double DNA::getEBulletRepel(int state)
{
    return ebulletrepel[state];
}

double DNA::getEBulletRepelPower(int state)
{
    return ebulletrepelpower[state];
}

double DNA::getELineAttract(int state)
{
    return elineattract[state];
}

double DNA::getELineAttractPower(int state)
{
    return elineattractpower[state];
}

double DNA::getELineRepel(int state)
{
    return elinerepel[state];
}

double DNA::getELineRepelPower(int state)
{
    return elinerepelpower[state];
}

double DNA::getWLineAttract(int state)
{
    return wlineattract[state];
}

double DNA::getWLineAttractPower(int state)
{
    return wlineattractpower[state];
}

double DNA::getWLineRepel(int state)
{
    return wlinerepel[state];
}

double DNA::getWLineRepelPower(int state)
{
    return wlinerepelpower[state];
}

double DNA::getPowerUpAttract(int state)
{
    return powerupattract[state];
}

double DNA::getPowerUpAttractPower(int state)
{
    return powerupattractpower[state];
}

double DNA::getPowerUpRepel(int state)
{
    return poweruprepel[state];
}

double DNA::getPowerUpRepelPower(int state)
{
    return poweruprepelpower[state];
}
