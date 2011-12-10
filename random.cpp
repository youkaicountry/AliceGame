
#include <math.h>
#include <time.h>
#include "Random.h"

static int static_constants_inited = 0;

static RANDOM_H_64BIT_TYPE mul_value;
static RANDOM_H_64BIT_TYPE mask_value;
static double dbl_divisor;
static float flt_divisor;

#define RANDOM_H_USE_RDTSC

#if defined(RANDOM_H_USE_RDTSC)
#include "rdtsc.h"
#endif

static void check_static()
{
   if (static_constants_inited != 0)
      return;
   static_constants_inited = 1;
   mul_value = 0x5DEE;
   mul_value <<= 20;
   mul_value |= 0xCE66D;
   mask_value = 1;
   mask_value <<= 48;
   mask_value--;
   dbl_divisor = (double) (((RANDOM_H_64BIT_TYPE) 1) << 53);
   flt_divisor = (float) (1 << 30);
   return;
}

Random::Random()
{
   RANDOM_H_64BIT_TYPE seed = 0;
#if (defined(RANDOM_H_USE_TIME_H) || !defined(RANDOM_H_USE_RDTSC))
   clock_t cpu_time = time(NULL);
   seed = -(long)(cpu_time);
#elif (defined(RANDOM_H_USE_RDTSC))
   GetTimestamp(&seed);
#else
#warning Can't determine timer method to use for random number seed, using default seed=0
#endif
   check_static();
   setSeed(seed);
   return;
}

Random::Random(RANDOM_H_64BIT_TYPE init_seed)
{
   check_static();
   setSeed(init_seed);
   return;
}

void Random::setSeed(RANDOM_H_64BIT_TYPE seed)
{
   this->seed = (seed^mul_value) & mask_value;
   this->haveNextNextGaussian = false;
   this->nextNextGaussian = 0.0;
   return;
}

int Random::nextBits(int bits)
{
   seed = (seed*mul_value + 0xB) & mask_value;
   return (int) (seed >> (48-bits));
}

void Random::nextBytes(char *buffer, int length)
{
   int i;
   int r;
   for(i=0;i<length;i++)
   {
      if ((i&3) == 0)
         r = nextBits(32);
      else
         r >>= 8;
      buffer[i] = (r & 0xFF);
   }
   return;
}

double Random::nextDouble(double range)
{
   RANDOM_H_64BIT_TYPE r;
   r = nextBits(26);
   r <<= 27;
   r += nextBits(27);
   return r*range/dbl_divisor;
}

bool Random::nextBoolean()
{
   if (nextBits(1) != 0)
      return true;
   else
      return false;
}

float Random::nextFloat(float range)
{
   return nextBits(30) / flt_divisor;
}

double Random::nextGaussian()
{
   if (haveNextNextGaussian)
   {
      haveNextNextGaussian = false;
      return nextNextGaussian;
   }
   double v1, v2, s;
   do
   {
      v1 = 2*nextDouble() - 1;
      v2 = 2*nextDouble() - 1;
      s = v1*v1+v2*v2;
   } while (s >= 1 || s == 0);
   double multiplier = sqrt(-2*log(s)/s);
   nextNextGaussian = v2*multiplier;
   haveNextNextGaussian = true;
   return v1*multiplier;
}

int Random::nextInt()
{
   return nextBits(32);
}

int Random::nextInt(int n)
{
   if (n <= 0)
      return 0;

   if ((n & -n) == n)
      return (int) ((n * (RANDOM_H_64BIT_TYPE) nextBits(31)) >> 31);
   int bits, val;
   do
   {
      bits = nextBits(31);
      val = bits % n;
   } while (bits - val + (n-1) < 0);
   return val;
}
