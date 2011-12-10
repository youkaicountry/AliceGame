#include "genepool.h"
#include <vector>
#include "random.h"
#include "dna.h"
#include "aiplayer.h"
#include "keystate.h"
#include "gamespace.h"
#include <math.h>

GenePool::GenePool(char* filename, int nseed, int nrlock, int simtype, int runs, int smult, int lmult)
{
   seed = nseed;
   reactionlock = nrlock;
   //for (int i = 0;i < 30;i++)
   //{
      DNA a;a.load(filename);
      dnavect.push_back(a);
      
      
      int addfit = 0;
      for (int aja = 0;aja < runs;aja++)
      {
         AIPlayer ai;
         KeyState ks;
      //Random ran;
         GameSpace gs(1, 0, 800, 0, 600, (seed-1) + aja, true, "test.lua", "shinku.lua");
         while (gs.updateGameState(ks) == 1)
	      {
            ks = ai.update(&gs, gs.thePlayer, dnavect[0], ks);
         }
      addfit += gs.thePlayer->getScore()*smult;
      addfit += gs.thePlayer->getLives()*lmult;
      }
      fitness.push_back(addfit / runs);
   
   return;
}

GenePool::~GenePool()
{
   return;
}

//void GenePool::updatePool(double crossover, double mutationchance, double severity, int tourneysize, int gen)
void GenePool::doPool(int maxsize, int deltype, int tourneysize, double crossover, double mutationchance, double severity, int numgens, double mutdev, double jostlechance, int simtype, int runs, int smult, int lmult)
{
   int top = 1;
   DNA thedna; //set by mutate/breed
   
   for (int fill = 1;fill < maxsize;fill++)
   {
      dnavect.push_back(thedna);
      fitness.push_back(-1);
   }
   
   
   //printf("fitness[%d] = %d ; cycle = %d\n", num, fitness[num], gs.cycle);
   //if (fitness[num] < 0) {dnavect[num].save("bad.dna");}
   
   //delete if needed
   
   
   int tourney[tourneysize];
   Random ran;
   
   
   for (int vvi = 0;vvi < numgens;vvi++)
   {
   
   //int selected[5]; //the index of tourney selected dudes
   //printf("ms1\n");
   int sa = 0;int sb = 0; //the two selected to mate 

   //pick best 'tourneysize' from the tourney
      //printf("ms2\n");
         //select sample for tourney
      for (int ii = 0;ii < tourneysize; ii++)
      {
         tourney[ii] = ran.nextInt(top);
      }
      int highestfit = -1;int highestfitindex = 0;
      //printf("ms3\n");
      for (int b = 0;b < tourneysize;b++)
      {
         if (fitness[tourney[b]] > highestfit) {highestfit = fitness[tourney[b]];highestfitindex = tourney[b];}
      }
      sa = highestfitindex;
      //printf("ms4\n");
      for (int ii = 0;ii < tourneysize; ii++)
      {
         tourney[ii] = ran.nextInt(top);
      }
      highestfit = -1;highestfitindex = 0;
      //printf("ms5\n");
      for (int b = 0;b < tourneysize;b++)
      {
         if (fitness[tourney[b]] > highestfit) {highestfit = fitness[tourney[b]];highestfitindex = tourney[b];}
      }
      sb = highestfitindex;

      //printf("ms6\n");
   //breed and mutate x1
      int inf1 = vvi;int inf2 = sa;int inf3 = fitness[sa];int inf4 = sb;int inf5 = fitness[sb];
      thedna = this->dnavect[sa].mate(dnavect[sb], crossover, reactionlock);
      //printf("msvv\n");
      double fmut = ran.nextGaussian()*mutdev+mutationchance;
      thedna.mutate(fmut, severity, reactionlock, jostlechance);
      //printf("ms7\n");
      int putwhere = 0;
      if (top == maxsize)
      {
         if (deltype == 0)
         { 
            int lowest = -1;
            int lowestindex = 0;
            for(int i = 0;i < top;i++)
            {
               if ((fitness[i] < lowest) || lowest == -1) {lowest = fitness[i]; lowestindex = i;}
            }
         
         //printf("ms8\n");
         putwhere = lowestindex;
         dnavect[putwhere] = thedna;
         }
         
         if (deltype == 1) //random del
         {
            putwhere = ran.nextInt(top);
            dnavect[putwhere] = thedna;
         }
         
         if (deltype == 2)
         {
            for (int ii = 0;ii < tourneysize; ii++)
            {
               tourney[ii] = ran.nextInt(top);
            }
            int lowfit = -1;int lowfitindex = 0;

            for (int b = 0;b < tourneysize;b++)
            {
               if (fitness[tourney[b]] < lowfit || lowfit == -1) {lowfit = fitness[tourney[b]];lowfitindex = tourney[b];}
            }
            
            putwhere = lowfitindex;
            dnavect[putwhere] = thedna;
         }
            
      }
      else
      {
         putwhere = top;top++;
         dnavect[putwhere] = thedna;
         //dnavect.push_back(thedna);
      }

      //printf("ms9\n");
      
      int inf6 = putwhere;int inf7=fitness[putwhere];
      this->simulate(putwhere, simtype, runs, smult, lmult);
      printf("Creature: %d\n", inf1);
      printf("mate1: %d, mate1fit: %d,  mate2: %d,  mate2fit: %d\n",inf2, inf3, inf4, inf5);
      printf("Final Mutation Chance: %lf\n", fmut);
      printf("Fitness of this creature: %d\n", fitness[putwhere]);
      printf("Overwrite Number: %d,  Overwrite Fitness: %d\n", inf6, inf7);
      printf("POOL INFO: Best: %d, Worst: %d, Mean: %g, StdDev: %g\n\n\n", this->bestFitness(top), this->worstFitness(top), this->meanFitness(top), this->standardDeviation(top));

      //do milestone save here
      
}


}



/*void Generation::simulateAll()
{
   for (int i = 0;i < 30;i++)
   {
      this->simulate(i);
   }
   return;
}
*/
void GenePool::simulate(int num, int simtype, int runs, int smult, int lmult)
{
   int addfit = 0;
   for (int aja = 0;aja < runs;aja++)
   {
      AIPlayer ai;
      KeyState ks;
   //Random ran;
      GameSpace gs(1, 0, 800, 0, 600, (seed-1) + aja, true, "test.lua", "shinku.lua");
      while (gs.updateGameState(ks) == 1)
	   {
         ks = ai.update(&gs, gs.thePlayer, dnavect[num], ks);
      }
   addfit += gs.thePlayer->getScore()*smult;
   addfit += gs.thePlayer->getLives()*lmult;
   }
   fitness[num] = addfit / runs;
   //printf("fitness[%d] = %d ; cycle = %d\n", num, fitness[num], gs.cycle);
   //if (fitness[num] < 0) {dnavect[num].save("bad.dna");}
   return;
}

int GenePool::bestFitness(int top)
{                         
   int i = 0;
   int highest = -10000; 
   for(int z = 0; z != top;z++)
   {
       if (fitness[z] > highest) {highest = fitness[z];}
   }         
   return highest;
}


int GenePool::worstFitness(int top)
{
   int i = 0;
   int lowest = -1;
   for(int z = 0;z != top;z++)
   {
      if ((fitness[z] < lowest) || lowest == -1) {lowest = fitness[z];}
   }
   return lowest;
}


double GenePool::standardDeviation(int top)
{
    double mean = meanFitness(top);
    double variance = 0;
    for (int i = 0;i < top;i++)
    {
        variance += pow((fitness[i] - mean),2);
    }
    variance /= top;
    return sqrt(variance);
}

double GenePool::meanFitness(int top)
{
    int sum = 0;
    for (int i = 0;i < top;i++)
    {
        sum += fitness[i];
    }
    return (((double)sum) / top);
}

void GenePool::saveBest(char* filename, int top)
{
   int i = 0;
   int highest = -10000;int highestnum = 0;
   for(i = 0;i < top;i++)
   {
      if (fitness[i] > highest) {highest = fitness[i];highestnum = i;}
   }
   dnavect[highestnum].save(filename);
   return;
}
