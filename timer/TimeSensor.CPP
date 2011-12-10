
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <math.h>
#include "TimeSensor.h"

TimeSensor::TimeSensor(void)
{
   sensor = 0.0;
   k = 0.0;
   max_sensor = 0.0;
   critical_value = 0.0;
   hasMadeObservation = false;
   t_last_observation.QuadPart = 0;
   for(int i=0;i<TIMESENSOR_LOOKUP_SIZE;i++)
      emkt_lookup[i] = 0.0;
   LN_2 = log(2.0);
   return;
}

void TimeSensor::init_emkt_lookup(void)
{
   for(int i=0;i<TIMESENSOR_LOOKUP_SIZE;i++)
      emkt_lookup[i] = exp(-k*i);
   return;
}

void TimeSensor::setFrequency(double hertz)
{
   critical_value = hertz / getTickFrequency();
   max_sensor = critical_value - (k / 2.0);
   return;
}

void TimeSensor::setLambda(double lambda)
{
   k = LN_2 / (lambda * getTickFrequency());
   max_sensor = critical_value - (k / 2.0);
   init_emkt_lookup();
   return;
}

void TimeSensor::reset(void)
{
   sensor = critical_value;
   hasMadeObservation = false;
   return;
}

bool TimeSensor::poll(void)
{
   LARGE_INTEGER t_now;
   getTicks(&t_now);
   if (!hasMadeObservation)
   {
      t_last_observation.QuadPart = t_now.QuadPart;
      hasMadeObservation = true;
   }
   LARGE_INTEGER dt;
   dt.QuadPart = t_now.QuadPart - t_last_observation.QuadPart;
   if ((dt.HighPart == 0) && (dt.LowPart < TIMESENSOR_LOOKUP_SIZE))
      sensor *= emkt_lookup[dt.LowPart];
   else
      sensor *= exp(-k*((double) dt.QuadPart));
   t_last_observation = t_now;
   if (sensor >= max_sensor)
      return false;
   sensor += k;
   return true;
}

double TimeSensor::getSeconds(void)
{
   LARGE_INTEGER t;
   getTicks(&t);
   return ((double) (t.QuadPart)) / getTickFrequency();
}

TimeSensor::~TimeSensor(void)
{
   return;
}

void TimeSensor::wait(void)
{
   while(!poll())
      killTime();
   return;
}

void TimeSensor::killTime(void)
{
   return;
}

class Win32_TimeSensor : public TimeSensor
{
public:
   Win32_TimeSensor(void);
   ~Win32_TimeSensor(void);
   virtual void killTime(void);
};

Win32_TimeSensor::Win32_TimeSensor(void)
{
   return;
}

Win32_TimeSensor::~Win32_TimeSensor(void)
{
   return;
}

void Win32_TimeSensor::killTime(void)
{
   Sleep(1);
   return;
}

class Win32_MilliSensor : public Win32_TimeSensor
{
public:
   Win32_MilliSensor(void);
   ~Win32_MilliSensor(void);

   virtual void getTicks(LARGE_INTEGER *ticks);
   virtual double getTickFrequency(void);
};

Win32_MilliSensor::Win32_MilliSensor(void)
{
   return;
}

Win32_MilliSensor::~Win32_MilliSensor(void)
{
   return;
}

void Win32_MilliSensor::getTicks(LARGE_INTEGER *ticks)
{
   ticks->LowPart = GetTickCount();
   ticks->HighPart = 0;
   return;
}

double Win32_MilliSensor::getTickFrequency(void)
{
   return 1000.0;
}

class Win32_HPSensor : public Win32_TimeSensor
{
public:
   Win32_HPSensor(void);
   ~Win32_HPSensor(void);

   virtual void getTicks(LARGE_INTEGER *ticks);
   virtual double getTickFrequency(void);
   static bool isSupported(void);
};

Win32_HPSensor::Win32_HPSensor(void)
{
   return;
}

Win32_HPSensor::~Win32_HPSensor(void)
{
   return;
}

bool Win32_HPSensor::isSupported(void)
{
   LARGE_INTEGER freq;
   return (QueryPerformanceFrequency(&freq) != 0);
}

void Win32_HPSensor::getTicks(LARGE_INTEGER *ticks)
{
   QueryPerformanceCounter(ticks);
   return;
}

double Win32_HPSensor::getTickFrequency(void)
{
   LARGE_INTEGER freq;
   QueryPerformanceFrequency(&freq);
   return ((double) freq.QuadPart);
}


TimeSensor *TimeSensor::getNewClockSensor(void)
{
   if (Win32_HPSensor::isSupported())
      return new Win32_HPSensor();
   return new Win32_MilliSensor();
}
