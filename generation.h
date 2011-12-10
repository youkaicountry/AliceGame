#ifndef _GENERATION__
#define _GENERATION__

#include "random.h"
#include "dna.h"
#include <vector>

using namespace std;

class Generation
{
   public:
      Generation(char* filename, int nseed, int nrlock);
      ~Generation();
      
      vector<DNA> dnavect;
      vector<int> fitness;
      
      int seed;
      int reactionlock;
      
      Generation formNextGeneration(double crossover, double mutationchance, double severity, int tourneysize, int gen, double mjost);
      int bestFitness();
      double meanFitness();
      double standardDeviation();
      int worstFitness();
      void saveBest(char* filename);
      void simulate(int num);
      void simulateAll();
      
};      
   

#endif
