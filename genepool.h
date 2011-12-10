#ifndef _GENEPOOL__
#define _GENEPOOL__

#include "random.h"
#include "dna.h"
#include <list>
#include <vector>

using namespace std;

class GenePool
{
   public:
      GenePool(char* filename, int nseed, int nrlock, int simtype, int runs, int smult, int lmult);
      ~GenePool();

      vector<DNA> dnavect;
      vector<int> fitness;

      int seed;
      int reactionlock;

      //Generation formNextGeneration(double crossover, double mutationchance, double severity, int tourneysize, int gen);
      void doPool(int maxsize, int deltype, int tourneysize, double crossover, double mutationchance, double severity, int numgens, double mutdev, double jostlechance, int simtype, int runs, int smult, int lmult);
      int bestFitness(int top);
      void simulate(int num, int simtype, int runs, int smult, int lmult);
      double meanFitness(int top);
      double standardDeviation(int top);
      int worstFitness(int top);
      void saveBest(char* filename, int top);

};


#endif
