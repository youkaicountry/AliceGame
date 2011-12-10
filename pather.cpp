#include "pather.h"
#include "TwoVector.h"
#include <Math.h>
#include <vector.h>

PathPiece::PathPiece()
{
   return;
}

PathPiece::~PathPiece()
{
   return;
}

double PathPiece::getLength()
{
   return 0.0;
}

void PathPiece::getPoint(double x, double y, double n, TwoVector* tv)
{
   tv->setX(0.0);
   tv->setY(0.0);
   return;
}

void PathPiece::getStart(TwoVector* tv)
{
   tv->setX(0.0);
   tv->setY(0.0);
   return;
}

void PathPiece::getEnd(TwoVector* tv)
{
   tv->setX(0.0);
   tv->setY(0.0);
   return;
}

LinePiece::LinePiece(double nx1, double ny1, double nx2, double ny2)
{
   this->x1 = nx1;
   this->y1 = ny1;
   this->x2 = nx2;
   this->y2 = ny2;
   double a = nx2-nx1;
   double b = ny2-ny1;
   this->length = sqrt((a*a)+(b*b));
   return;
}
   
LinePiece::~LinePiece()
{
   return;
}

double LinePiece::getLength()
{
   return this->length;
}

void LinePiece::getPoint(double x, double y, double n, TwoVector* tv)
{
   tv->setX(((n*(this->x2-this->x1))+x1)+x);
   tv->setY(((n*(this->y2-this->y1))+y1)+y);
}

void LinePiece::getStart(TwoVector* tv)
{
   tv->setX(this->x1);
   tv->setY(this->y1);
   return;
}

void LinePiece::getEnd(TwoVector* tv)
{
   tv->setX(this->x2);
   tv->setY(this->y2);
   return;
}



Pather::Pather()
{
   return;
}

Pather::~Pather()
{
   return;
}

void Pather::calcPath()
{
   if (path.size() == 0) {return;}
   
   double l = 0;
   for(int i = 0;i < path.size(); i++)
   {
      l += path[i]->getLength();
   }
   this->length = l;
   
   double nn = 0;
   for(int i = 0;i < path.size(); i++)
   {
      nn += path[i]->getLength();
      pathnend[i] = nn / this->length;
   }
   return;
}

double Pather::getLength()
{
   return this->length;
}

void Pather::addLine(double xend, double yend)
{
   TwoVector tv;
   if (this->path.size() > 0)
   {
      this->path[this->path.size()-1]->getEnd(&tv);
   }
   else
   {
      tv.setX(0.0);
      tv.setY(0.0);
   }
   this->path.push_back(new LinePiece(tv.getX(), tv.getY(), xend, yend));
   this->pathnend.push_back(0);
   this->calcPath();
}

void Pather::getPoint(double x, double y, double endx, double endy, double n, TwoVector* tv)
{
   if (n > 1.0) {n = 1.0;}
   if (n < 0.0) {n = 0.0;}
   if (this->path.size() == 0) {tv->setX(x);tv->setY(y);return;}
   double last = 0;
   double here = 0;
   double sizer = 0;
   double np = 0;
   for (int i = 0;i < this->path.size();i++)
   {
      if (i > 0) {last = this->pathnend[i-1];}
      else {last = 0.0;}
      here = this->pathnend[i];
      if (n <= here) 
      {
         sizer = here - last;
         np = (n - last)/(here - last);
         this->path[i]->getPoint(0, 0, np, tv);
         double theta = atan2(endy-y, endx-x);
         double tx = tv->getX();
         double ty = tv->getY();
         tv->setX((tx/(endx-x)) + x);
         tv->setY((ty/(endy-y)) + y);
         
         break; 
      }
   }
   return;
}

void Pather::getPoint(double x, double y, double n, TwoVector* tv)
{
   if (n > 1.0) {n = 1.0;}
   if (n < 0.0) {n = 0.0;}
   if (this->path.size() == 0) {tv->setX(x);tv->setY(y);return;}
   double last = 0;
   double here = 0;
   double sizer = 0;
   double np = 0;
   for (int i = 0;i < this->path.size();i++)
   {
      if (i > 0) {last = this->pathnend[i-1];}
      else {last = 0.0;}
      here = this->pathnend[i];
      if (n <= here)
      {
         sizer = here - last;
         np = (n - last)/(here - last);
         this->path[i]->getPoint(0, 0, np, tv);
         break;
      }
   }
   return;
}
