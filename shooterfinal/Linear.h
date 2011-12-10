
#ifndef LINEAR_H
#define LINEAR_H

#include <math.h>
#include <stdlib.h>

class LinearTransform
{
public:
   LinearTransform(const double *m = NULL)
   {
      if (m == NULL)
      {
         this->m[0] = this->m[4] = 1.0;
         this->m[1] = this->m[2] = this->m[3] = this->m[5] = 0.0;
      }
      else
      {
         this->m[0] = m[0]; this->m[1] = m[1]; this->m[2] = m[2];
         this->m[3] = m[3]; this->m[4] = m[4]; this->m[5] = m[5];  
      }
      return;
   }
   LinearTransform(double m0, double m1, double m2,
                   double m3, double m4, double m5)
   { m[0] = m0; m[1] = m1; m[2] = m2; m[3] = m3; m[4] = m4; m[5] = m5; }
   LinearTransform(double m0, double m1, double m3, double m4)
   { m[0] = m0; m[1] = m1; m[2] = 0.0; m[3] = m3; m[4] = m4; m[5] = 0.0; }
   ~LinearTransform()
   { return; }
   
   // this *= t
   static void mul(const LinearTransform *lhs, const LinearTransform *rhs,
      LinearTransform *r)
   { double r0 = lhs->m[0]*rhs->m[0] + lhs->m[1]*rhs->m[3],
            r1 = lhs->m[0]*rhs->m[1] + lhs->m[1]*rhs->m[4],
            r2 = lhs->m[0]*rhs->m[2] + lhs->m[1]*rhs->m[5] + lhs->m[2],
            r3 = lhs->m[3]*rhs->m[0] + lhs->m[4]*rhs->m[3],
            r4 = lhs->m[3]*rhs->m[1] + lhs->m[4]*rhs->m[4],
            r5 = lhs->m[3]*rhs->m[2] + lhs->m[4]*rhs->m[5] + lhs->m[5];
     r->m[0] = r0; r->m[1] = r1; r->m[2] = r2;
     r->m[3] = r3; r->m[4] = r4; r->m[5] = r5; }

   void mul(const LinearTransform *rhs)
   { mul(this, rhs, this); }
   void premul(const LinearTransform *lhs)
   { mul(lhs, this, this); }
   void apply(double *x, double *y)
   { double xp = (*x)*m[0]+(*y)*m[1]+m[2], yp = (*x)*m[3]+(*y)*m[4]+m[5];
     (*x) = xp; (*y) = yp;   }
   
   double det()
   { return m[0]*m[4]-m[1]*m[3]; }
   static LinearTransform getTranslate(double tx, double ty)
   {  return LinearTransform(1.0, 0.0, tx, 0.0, 1.0, ty);   }
   static LinearTransform getRotate(double theta)
   {  return getRotate(cos(theta), sin(theta));             }
   static LinearTransform getRotate(double c, double s)
   {  return LinearTransform(c, -s, s, c);                  }
   void invert()
   {  double d = det();
      if (fabs(d) < 0.00001)
         d = (d < 0) ? -0.00001 : 0.00001;
      d = 1.0/d;
      double r0 = m[4]*d, r1 = -m[1]*d, r2 = (m[1]*m[5]-m[2]*m[4])*d,
             r3 = -m[3]*d, r4 = m[0]*d, r5 = (m[3]*m[2]-m[5]*m[0])*d;
      m[0] = r0; m[1] = r1; m[2] = r2; m[3] = r3; m[4] = r4; m[5] = r5; }
   void setTo(const LinearTransform *rhs)
   {  m[0] = rhs->m[0]; m[1] = rhs->m[1]; m[2] = rhs->m[2];
      m[3] = rhs->m[3]; m[4] = rhs->m[4]; m[5] = rhs->m[5]; }
   void setToTriangleTransform(const double *src, const double *dst);
      // src and dst are in the order x0,y0,x1,y1,x2,y2
   void setToSegmentTransform(const double *src, const double *dst);

   double m[6];
};

#endif
