
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "TimeSensor.h"

#define BUFFER_SIZE 1000000

int main(void)
{
   TimeSensor *sensor = TimeSensor::getNewClockSensor();
   int n = 0;
   double *buffer;

   buffer = (double *) malloc(BUFFER_SIZE * sizeof(double));

   sensor->setFrequency(30);
   sensor->setLambda(0.070);
   sensor->reset();

   double freq = sensor->getTickFrequency();
   double start = sensor->getSeconds();
   double t;
   int m;

   do
   {
      sensor->wait();
      t = sensor->getSeconds()-start;
      buffer[n] = t;
      printf("%3d %5.2lf", n, t);
      for(m=1;n-m>=0;m+=m)
         printf(" %5.2lf", m/(buffer[n]-buffer[n-m]));
      printf("\n");
      n++;
   } while (t < 5);

   free(buffer);
   delete sensor;
   return 0;
}
