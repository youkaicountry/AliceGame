
#include <math.h>
#include "Linear.h"

void LinearTransform::setToTriangleTransform(const double *src,
   const double *dst)
{
   /*
   double m0 = -y2+y1, m1 = y2-y0, m2 = y0-y1,
          m3 = x2-x1, m4 = x0-x2, m5 = x1-x0,
          m6 = x1*y2-x2*y1, m7 = x2*y0-x0*y2, m8 = x0*y1-x1*y0;
   */
   double m0 = src[3]-src[5], m1 = src[5]-src[1], m2 = src[1]-src[3],
          m3 = src[4]-src[2], m4 = src[0]-src[4], m5 = src[2]-src[0],
          m6 = src[2]*src[5]-src[4]*src[3],
          m7 = src[4]*src[1]-src[0]*src[5],
          m8 = src[0]*src[3]-src[2]*src[1];
   
   double d = m6+m7+m8;
   if (fabs(d) < 0.00001)
      d = (d < 0) ? -0.00001 : 0.00001;
   d = 1.0/d;
   m0*=d; m1*=d; m2*=d; m3*=d; m4*=d; m5*=d; m6*=d; m7*=d; m8*=d;
   m[0] = m0*dst[0]+m1*dst[2]+m2*dst[4];
   m[1] = m3*dst[0]+m4*dst[2]+m5*dst[4];
   m[2] = m6*dst[0]+m7*dst[2]+m8*dst[4];
   m[3] = m0*dst[1]+m1*dst[3]+m2*dst[5];
   m[4] = m3*dst[1]+m4*dst[3]+m5*dst[5];
   m[5] = m6*dst[1]+m7*dst[3]+m8*dst[5];
   return;   
}

void LinearTransform::setToSegmentTransform(const double *src,
   const double *dst)
{
   double a[6], b[6];
   a[0]=src[0]; a[1]=src[1]; a[2]=src[2]; a[3]=src[3];
   b[0]=dst[0]; b[1]=dst[1]; b[2]=dst[2]; b[3]=dst[3];
   // Rotate by 90 degrees:  0, -1, 1, 0
   // dx = a[2]-a[0]; dy = a[3]-a[1];
   // (a[0], a[1]) + (-dy, dx)
   a[4] = a[0]-a[3]+a[1]; a[5] = a[1]+a[2]-a[0];
   b[4] = b[0]-b[3]+b[1]; b[5] = b[1]+b[2]-b[0];
   setToTriangleTransform(a, b);
   return;   
}
