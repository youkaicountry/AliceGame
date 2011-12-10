
#ifndef RANDOM_H
#define RANDOM_H

#ifndef RANDOM_H_64BIT_TYPE
#if defined(__GNUC__)
#define RANDOM_H_64BIT_TYPE long long int
#elif defined(_MSC_VER)
#define RANDOM_H_64BIT_TYPE __int64
#else
#error No 64-bit type is known for this compiler, please define RANDOM_H_64BIT_TYPE and recompile
#endif
#endif

class Random
{
public:
   Random();
   Random(RANDOM_H_64BIT_TYPE init_seed);
   virtual void setSeed(RANDOM_H_64BIT_TYPE seed);
   virtual int nextBits(int bits);
   virtual double nextDouble(double range = 1.0);
   template <class T> T next(T range)
   {   return (T) (range*nextDouble());      }
   virtual bool nextBoolean();
   virtual void nextBytes(char *buffer, int length);
   virtual float nextFloat(float range = 1.0f);
   virtual double nextGaussian();
   virtual int nextInt();
   virtual int nextInt(int max);

private:
   RANDOM_H_64BIT_TYPE seed;
   bool haveNextNextGaussian;
   double nextNextGaussian;

};

#endif
