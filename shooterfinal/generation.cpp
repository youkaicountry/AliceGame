#include "generation.h"
#include <list>
#include <vector>
#include "random.h"
#include "dna.h"
#include "aiplayer.h"
#include "keystate.h"
#include "gamespace.h"
#include <math.h>

Generation::Generation(char* filename, int nseed, int nrlock)
{
   seed = nseed;
   reactionlock = nrlock; 
   for (int i = 0;i < 30;i++)
   {
      DNA a;a.load(filename);
      dnavect.push_back(a);
      fitness.push_back(-1);
      //printf("fitness size: %d", fitness.size());
   }
   return;
}

Generation::~Generation()
{
   return;
}

Generation Generation::formNextGeneration(double crossover, double mutationchance, double severity, int tourneysize, int gen)
{
   Generation g("stock.dna", seed, reactionlock);
   for (int j = 0;j < this->fitness.size();j++)
   {
      //printf("sim %d\n", j);
      this->simulate(j);
   }
   
   printf("Generation: %d, Best: %d, Worst: %d, Mean: %g, StdDev: %g\n", gen, this->bestFitness(), this->worstFitness(), this->meanFitness(), this->standardDeviation());
   
   int tourney[tourneysize];
   int selected[5]; //the index of tourney selected dudes
   Random ran;
   
   
   //pick best 5 from the tourney
   for (int a = 0;a < 5;a++)
   {
         //select sample for tourney
      for (int ii = 0;ii < tourneysize; ii++)
      {
         tourney[ii] = ran.nextInt(30);
      }
      int highestfit = -1;int highestfitindex = 0;
      for (int b = 0;b < tourneysize;b++)
      {
         if (fitness[tourney[b]] > highestfit) {highestfit = fitness[tourney[b]];highestfitindex = tourney[b];}
      }
      selected[a] = highestfitindex;
   }
   
   //printf("best selected into selected[]\n");
   
   //straight breed the best 5 with each other and fill the first ten slots in g
   for (int ind = 0;ind < 10;ind++)
   {
      //printf("%d\n", ind);
      //printf("%d, %d, %d, %d, %d\n", selected[0], selected[1], selected[2], selected[3], selected[4]);
      int aa = ran.nextInt(5); int bb = ran.nextInt(5);
      if (aa == bb) {bb++;if (bb == 5) {bb = 0;} }
      //printf("aa = %d, bb = %d\n", aa, bb);
      g.dnavect[ind] = this->dnavect[selected[aa]].mate(this->dnavect[selected[bb]], crossover, reactionlock);
   }
   
   //printf("straight breeding done\n");
   
   //breed and mutate x1
   for (int indb = 10;indb < 20;indb++)
   {
      int aa = ran.nextInt(5); int bb = ran.nextInt(5);
      if (aa == bb) {bb++;if (bb == 5) {bb = 0;} }
      g.dnavect[indb] = this->dnavect[selected[aa]].mate(dnavect[selected[bb]], crossover, reactionlock);
      g.dnavect[indb].mutate(mutationchance, severity, reactionlock);
   }
   
   //printf("mutate breeding done\n");
   
   //breed and mutate x2
   for (int indc = 20;indc < 30;indc++)
   {
      g.dnavect[indc] = this->dnavect[selected[ran.nextInt(5)]].mate(dnavect[selected[ran.nextInt(5)]], crossover, reactionlock);
      g.dnavect[indc].mutate(mutationchance, severity * 2, reactionlock);
   }
   
   //printf("mutate x2 breeding done\n");
   
   return g;
}

void Generation::simulateAll()
{
   for (int i = 0;i < 30;i++)
   {
      this->simulate(i);
   }
   return;
}

void Generation::simulate(int num)
{
   AIPlayer ai;
   KeyState ks;
   //Random ran;
   GameSpace gs(1, 0, 800, 0, 600, seed, true);
   while (gs.updateGameState(ks) == 1)
	{
      ks = ai.update(&gs, &gs.thePlayer, dnavect[num], ks);
   }
   fitness[num] = gs.thePlayer.getScore();
   printf("fitness[%d] = %d ; cycle = %d\n", num, fitness[num], gs.cycle);
   if (fitness[num] < 0) {dnavect[num].save("bad.dna");}
   return;
}

int Generation::bestFitness()
{
   int i = 0;
   int highest = -10000;
   for(i = 0;i < fitness.size();i++)
   {
      if (fitness[i] > highest) {highest = fitness[i];}
   }
   return highest;
}

int Generation::worstFitness()
{
   int i = 0;
   int lowest = -1;
   for(i = 0;i < fitness.size();i++)
   {
      if ((fitness[i] < lowest) || lowest == -1) {lowest = fitness[i];}
   }
   return lowest;
}

double Generation::standardDeviation()
{
    double mean = meanFitness();
    double variance = 0;
    for (int i = 0;i < 30;i++)
    {
        variance += pow((fitness[i] - mean),2);
    }
    variance /= 30;
    return sqrt(variance);
}

double Generation::meanFitness()
{
    int sum = 0;
    for (int i = 0;i < 30;i++)
    {
        sum += fitness[i];
    }
    return (((double)sum) / 30);
}

void Generation::saveBest(char* filename)
{
   int i = 0;
   int highest = -10000;int highestnum = 0;
   for(i = 0;i < fitness.size();i++)
   {
      if (fitness[i] > highest) {highest = fitness[i];highestnum = i;}
   }
   dnavect[highestnum].save(filename);
   return;
}
