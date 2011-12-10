#ifndef _PATHER__
#define _PATHER__

#include "twovector.h"
#include <vector.h>

class PathPiece
{
   public:
   PathPiece();
   virtual ~PathPiece();
   
   virtual double getLength();
   virtual void getPoint(double x, double y, double n, TwoVector* tv);
   virtual void getStart(TwoVector* tv);
   virtual void getEnd(TwoVector* tv);
};

class LinePiece : public PathPiece
{
   public:
   LinePiece(double nx1, double ny1, double nx2, double ny2);
   virtual ~LinePiece();
   double getLength();
   void getPoint(double x, double y, double n, TwoVector* tv);
   void getStart(TwoVector* tv);
   void getEnd(TwoVector* tv);
   

   double x1, y1, x2, y2;
   double length;
};

class Pather
{
   public:
   Pather();
   ~Pather();
   
   vector<PathPiece*> path;
   vector<double>     pathnend;
   
   double length;
   
   void calcPath();
   
   double getLength();
   void getPoint(double x, double y, double n, TwoVector* tv);
   void getPoint(double x, double y, double endx, double endy, double n, TwoVector* tv);
   
   void addLine(double xend, double yend);
   
};

#endif
