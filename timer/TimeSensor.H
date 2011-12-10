
#ifndef TIMESENSOR_H
#define TIMESENSOR_H

#define TIMESENSOR_LOOKUP_SIZE 128

class TimeSensor
{
protected:
   TimeSensor(void);

   double sensor;
   double k;
   double max_sensor;
   double critical_value;
   bool hasMadeObservation;
   LARGE_INTEGER t_last_observation;

private:
   void init_emkt_lookup(void);
   double LN_2;
   double emkt_lookup[TIMESENSOR_LOOKUP_SIZE];

public:
   virtual void setFrequency(double hertz);
   virtual void setLambda(double lambda);
   virtual void reset(void);
   virtual bool poll(void);
   virtual void wait(void);
   virtual double getSeconds(void);
   virtual double getTickFrequency(void) = 0;
   virtual void getTicks(LARGE_INTEGER *ticks) = 0;
   virtual void killTime(void);
   virtual ~TimeSensor(void);

   static TimeSensor *getNewClockSensor();
};

#endif
