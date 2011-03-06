/****************************************************************************
Copyright (C) 2010 Laszlo Simon <laszlo.simon@gmail.com>

This file is part of the HidraVFX project.

HidraVFX is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

HidraVFX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with HidraVFX. If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mathplus.h"
#include "layer.h"
#include "options.h"
#include "conform.h"

#define BOLYAISPHERE {                 \
  double d, fi, d0;                    \
  d = sqrt(sqr(x - x0) + sqr(y - y0)); \
  fi = atan2(y - y0, x - x0);          \
  d0 = d * R / sqrt(sqr(d) + sqr(z0)); \
  x1 = x0 + d0 * cos(fi);              \
  y1 = y0 + d0 * sin(fi);              \
}

#define INVBOLYAISPHERE { \
  double d, fi, tmp, z, d0; \
  d = sqrt(sqr(x-x0)+sqr(y-y0)); \
  fi = atan2(y-y0,x-x0); \
  tmp = sqr(R)-sqr(x-x0)-sqr(y-y0); \
     z = sqrt(tmp)+z0; \
     d0 = (z0 < 0)  ? -z0 * d / (z - z0) : \
                       z0 * d / (z + z0); \
  x1 = x0 + d0 * cos(fi); \
  y1 = y0 + d0 * sin(fi); \
}

#define SPHERIZE {                                 \
  double alp0 = (PI/2)*factor/100;                 \
  double d = sqrt(sqr(x-x0)+sqr(y-y0));            \
  if (d>rc) {                                      \
    x1 = x;                                        \
    y1 = y;                                        \
  } else {                                         \
    double fi, R, z0, tmp, z, d0;                  \
    fi = atan2(y-y0,x-x0);                         \
    R = rc/sin(alp0);                              \
    z0 = R*cos(alp0);                              \
    tmp = sqr(R)-sqr(x-x0)-sqr(y-y0);              \
    z = sqrt(tmp)+z0;                              \
    d0 = (alp0 > 0) ? z0*d/(z-z0) : z0*d/(z+z0);   \
    x1 = x0+d0*cos(fi);                            \
    y1 = y0+d0*sin(fi);                            \
  }                                                \
}

#define SHIFT {                      \
  x1 = x + ((x < x0) ? w-x0 : -x0);  \
  y1 = y + ((y < y0) ? h-y0 : -y0);  \
}

#define POLARTODESCARTES { \
  double zx, zy, ux, uy, r, fi, rCons, fiCons; \
  rCons  = (h-1)/(sqrt(w*w+h*h)/2.0); \
  fiCons = (w-1)/(2*PI); \
  ux = (w/2.0)-1; \
  uy = (h/2.0)-1; \
  zx = x-ux; \
  zy = y-uy; \
  r = sqrt(sqr(zx)+sqr(zy)); \
  fi = atan2(zy,zx); \
  x1 = fi * fiCons; \
  y1 = h - r*rCons - 1; \
}

#define DESCARTESTOPOLAR { \
  double rCons, fiCons, ux, uy; \
  rCons  = (sqrt(w*w+h*h)/2.0)/(h-1); \
  fiCons = (2*PI)/(w-1); \
  ux = (w/2.0)-1; \
  uy = (h/2.0)-1; \
  x1 = y*rCons*cos(x*fiCons)+ux; \
  y1 = y*rCons*sin(x*fiCons)+uy; \
}

#define ROTATE_INIT \
  double o, ux, uy, rx, ry, zx, zy; \
  rx = cos(angle); \
  ry = sin(angle);
#define ROTATE { \
  zx = x-x0; \
  zy = y-y0; \
  if (ry == 0) { \
     ux =zx/rx; \
     uy =zy/rx; \
  } else { \
     o  =rx*rx+ry*ry; \
     ux =(zx*rx+zy*ry)/o; \
     uy =(zy*rx-zx*ry)/o; \
  } \
  x1 = ux+x0; \
  y1 = uy+y0; \
}

#define SWIRL_INIT \
  double r,fi,zx,zy,ux,uy,tx,ty,z2x,z2y; \
  tx = cos(angle); \
  ty = sin(angle);
#define SWIRL { \
  zx  = x-x0; \
  zy  = y-y0; \
  r   = sqrt(sqr(zx)+sqr(zy))/radial; \
  fi  = r * angle; \
  ux  = cos(fi); \
  uy  = sin(fi); \
  z2x = zx * ux - zy * uy; \
  z2y = zx * uy + zy * ux; \
  x1  = (z2x*tx+z2y*ty)+x0; \
  y1  = (z2y*tx-z2x*ty)+y0; \
}

#define PINCH { \
  double zx, zy, ux, uy, z2, r; \
  ux = (2.0 * x / w) - 1; \
  uy = (2.0 * y / h) - 1; \
  r  = sqrt(sqr(ux) + sqr(uy)); \
  z2 = pow(r, scale); \
  zx = z2 * ux / r; \
  zy = z2 * uy / r; \
  x1 = (zx+1)*(w/2.0); \
  y1 = (zy+1)*(h/2.0); \
}

#define SINUSOIDAL { \
  double ux,uy,zx,zy,arcsin; \
  arcsin = 1.0/asin(scale/100.0); \
  ux   = (x-(w/2.0))/(w/2.0); \
  uy   = (y-(h/2.0))/(h/2.0); \
  ux   = ux*scale/100.0; \
  uy   = uy*scale/100.0; \
  zx   = asin(ux)*arcsin; \
  zy   = asin(uy)*arcsin; \
  x1   = zx*(w/2.0)+(w/2.0); \
  y1   = zy*(h/2.0)+(h/2.0); \
}

#define CENTERMIRROR { \
  x1 = x0 - (x - x0);  \
  y1 = y0 - (y - y0);  \
}

#define AXISMIRROR { \
  double tx, ty, d; \
  d = sqrt(sqr(axisx)+sqr(axisy)); \
  axisx /= d; \
  axisy /= d; \
  tx = (x*axisx + y*axisy) / (d*d); \
  ty = (x*axisy - y*axisx) / (d*d); \
  x1 = (tx*axisx - ty*axisy) + x0; \
  y1 = (tx*axisy + ty*axisx) + y0; \
}

#define MISTERX { \
  double zx,zy,o; \
  zx = (x - (w / 2.0)) / rad; \
  zy = (y - (h / 2.0)) / rad; \
  o  = zx * zx + zy * zy; \
  zx = zx / o; \
  zy = -zy / o; \
  x1  = zx*rad + (w / 2.0); \
  y1  = zy*rad + (h / 2.0); \
  if (x1 <  0)   x1 = -x1-1; \
  if (x1 >= w*2) x1 = (2.0*w)*(x1/(2.0*w)-(int)(x1/(2.0*w))); \
  if (x1 >= w)   x1 = w-1-(x1-w); \
  if (y1 <  0)   y1 = -y1-1; \
  if (y1 >= h*2) y1 = (2*h)*(y1/(2.0*h)-(int)(y1/(2.0*h))); \
  if (y1 >= h)   y1 = h-1-(y1-h); \
}

#define TUBE_INIT \
  double d, fi, d0, dmax, fio, rmin, rmax; \
  fio  = atan2(h/2.0-x0,w/2.0-y0); \
  rmin = sqrt(sqr(w/2.0)+sqr(h/2.0))-sqrt(sqr(x0-w/2.0)+sqr(y0-h/2.0)); \
  rmax = sqrt(sqr(w/2.0)+sqr(h/2.0))+sqrt(sqr(x0-w/2.0)+sqr(y0-h/2.0));
#define TUBE { \
  fi   =  atan2(y-y0,x-x0); \
  dmax =  rmin+(rmax-rmin)*(1-cos(fi-fio))/2.0; \
  d    =  sqrt(sqr(x-x0) + sqr(y-y0)) / dmax; \
  d0   =  (d == 0) ? 0 : rad / d; \
  x1   = x0 + numX * d0 * dmax + w*dX/100.0; \
  y1   = y0 + numY * (fi/PI)*h + h*dY/100.0; \
  if (x1 <  0)   x1 = -x1 - 1; \
  if (x1 >= w*2) x1 = (2.0*w)*(x1/(2.0*w)-(int)(x1/(2.0*w))); \
  if (x1 >= w)   x1 = w-1-(x1-w); \
  if (y1 <  0)   y1 = -y1-1; \
  if (y1 >= h*2) y1 = (2*h)*(y1/(2.0*h)-(int)(y1/(2.0*h))); \
  if (y1 >= h)   y1 = h-1-(y1-h); \
}


#undef EFFECT
#define EFFECT(name, params, init, calc)  \
void name(tMapF map, tMapF res, int w, int h, int fproc(int))                   \
{                                                                               \
  int aa = (opt_get("aa") != NULL) ? opt_getl("aa") : 0;                        \
  params                                                                        \
  int ix, iy;                                                                   \
  double x, y;                                                                  \
  double x1, y1;                                                                \
  init                                                                          \
  for (iy = 0; iy < h; iy++)                                                    \
  {                                                                             \
    if (fproc != NULL) { fproc(y * 100 / h); }                                  \
                                                                                \
    if (aa == 0)                                                                \
    {                                                                           \
      for (ix = 0; ix < w; ix++)                                                \
      {                                                                         \
        x = ix; y = iy;                                                         \
        calc                                                                    \
        res[iy][ix] = mapGetAAPix(map, x1, y1, 0, 0, w, h);                     \
      }                                                                         \
    }                                                                           \
    else                                                                        \
    {                                                                           \
      for (ix = 0; ix < w; ix++)                                                \
      {                                                                         \
        float rescol = 0.0;                                                     \
        x = ix-0.25; y = iy-0.25;                                               \
        calc                                                                    \
        rescol += mapGetAAPix(map, x1, y1, 0, 0, w, h);                         \
        x = ix+0.25; y = iy-0.25;                                               \
        calc                                                                    \
        rescol += mapGetAAPix(map, x1+0.25, y1-0.25, 0, 0, w, h);               \
        x = ix-0.25; y = iy+0.25;                                               \
        calc                                                                    \
        rescol += mapGetAAPix(map, x1-0.25, y1+0.25, 0, 0, w, h);               \
        calc                                                                    \
        x = ix+0.25; y = iy+0.25;                                               \
        rescol += mapGetAAPix(map, x1+0.25, y1+0.25, 0, 0, w, h);               \
        res[iy][ix] = rescol/4.0;                                               \
      }                                                                         \
    }                                                                           \
  }                                                                             \
}

CONFORMS
