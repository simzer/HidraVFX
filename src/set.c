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
#include <mathplus.h>
#include "set.h"

/*
 *  PROTOTYPES
 */

static tsetpoint setformulaInit(tsetpoint p, tsetformula *psf);

static tsetpoint setfMandelbrot(tsetpoint p, tsetformula sf);
static tsetpoint setfSqrMandelbrot(tsetpoint p, tsetformula sf);
static tsetpoint setfPhoenix(tsetpoint p, tsetformula sf);
static tsetpoint setfNewton(tsetpoint p, tsetformula sf);
static tsetpoint setfSzegedi(tsetpoint p, tsetformula sf);
static tsetpoint setfSzegedi2(tsetpoint p, tsetformula sf);

static void      setcoloringInit(tsetpoint p, tsetcoloring *psc);
static void      setcGeneralStep(tsetpoint p, tsetcoloring *psc);
static void      setcCurveEstimateStep(tsetpoint p, tsetcoloring *psc);

static double    setcTimeEscapeGet(tsetcoloring sc);
static double    setcPotentialGet(tsetcoloring sc);
static double    setcCurveEstimateGet(tsetcoloring sc);
static double    setcEscapeAngleGet(tsetcoloring sc);
static double    setcEscapeDistanceGet(tsetcoloring sc);

/*
 *  GLOBALS
 */

tsetpoint pointnull = { 0, 0 };

/*
 *  FUNCTIONS
 */

/*-----------------------------------------------------------------------------
 * Set
 */

tsetpoint setpoint(double x, double y)
{
  tsetpoint res;
  res.x = x;
  res.y = y;
  return(res);
}

tsetmodel setmodelCreate(tsetformula sf,
                         tsetcoloring sc,
                         int maxiteration,
                         tsetpoint min,
                         tsetpoint max)
{
  tsetmodel res;
  res.fset         = sf;
  res.fcoloring    = sc;
  res.maxiteration = maxiteration;
  res.maxdistance  = (sc.step == &setcCurveEstimateStep) ? 1.0/0.0 : 16;
  res.min = min;
  res.max = max;
  return(res);
}

double setiteration(tsetpoint p, tsetmodel sm)
{
  int it = 0;
  p.x = p.x*(sm.max.x-sm.min.x) + sm.min.x;
  p.y = p.y*(sm.max.y-sm.min.y) + sm.min.y;
  setformulaInit(p, &sm.fset);
  setcoloringInit(sm.fset.prev, &sm.fcoloring);
  do
  {
     p = sm.fset.step(p, sm.fset);
     it++;
     sm.fcoloring.step(p, &sm.fcoloring);
  }
  while((sqr(p.x)+sqr(p.y) < sm.maxdistance) && (it <= sm.maxiteration));
  return(sm.fcoloring.get(sm.fcoloring));
}

/*-----------------------------------------------------------------------------
 *  Set formulas
 */

tsetformula setformulaCreate(int mode, tsetpoint p, int type)
{
  tsetformula res;
  res.c = p;
  res.mode = mode;
  res.step = type == 0 ? &setfMandelbrot    :
             type == 1 ? &setfSqrMandelbrot :
             type == 2 ? &setfPhoenix       :
             type == 3 ? &setfNewton        :
             type == 4 ? &setfSzegedi       :
                         &setfSzegedi2;
  return res;
}

static tsetpoint setformulaInit(tsetpoint p, tsetformula *psf)
{
  tsetpoint res;

  if (psf->mode == 0)
  {
    psf->c = p;
    psf->prev = res = pointnull;
  } else {
    psf->prev = res = p;
  }
  return(res);
}

static tsetpoint setfMandelbrot(tsetpoint p, tsetformula sf)
{
  tsetpoint r;
  r.x = p.x * p.x - p.y * p.y + sf.c.x;
  r.y = 2.0 * p.x * p.y + sf.c.y;
  return(r);
}

static tsetpoint setfSqrMandelbrot(tsetpoint p, tsetformula sf)
{
  tsetpoint r = setfMandelbrot(p, sf);
  return(setfMandelbrot(r, sf));
}

static tsetpoint setfPhoenix(tsetpoint p, tsetformula sf)
{
  tsetpoint r;
  r.x    = p.x*p.x - p.y*p.y + sf.c.x + sf.c.y*sf.prev.x;
  r.y    = 2.0*p.x*p.y + sf.c.y*sf.prev.y;
  sf.prev = p;
  return(r);
}

static tsetpoint setfNewton(tsetpoint p, tsetformula sf)
{
  double o;
  tsetpoint p3, p4, r = p;
  p3.x = p.x*p.x*p.x-3*p.x*p.y*p.y;
  p3.y =-p.y*p.y*p.y+3*p.x*p.x*p.y;
  p4.x = ((p.x*p3.x-p3.y*p.y)+1)/2;
  p4.y = ((p.x*p3.y+p3.x*p.y)+0)/2;
  o = p3.x*p3.x+p3.y*p3.y;
  if (o != 0) {
    r.x =p.x-(p3.x*p4.x + p3.y*p4.y)/o;
    r.y =p.y-(p3.x*p4.y - p4.x*p3.y)/o;
  }
  return(r);
}

static tsetpoint setfSzegedi(tsetpoint p, tsetformula sf)
{
  tsetpoint r;
  r.x=sqr(p.y) - sqrt(abs(p.x)) + sf.c.x;
  r.y=sqr(p.x) - sqrt(abs(p.y)) + sf.c.y;
  return(r);
}

static tsetpoint setfSzegedi2(tsetpoint p, tsetformula sf)
{
  tsetpoint r;
  r.x = sqr(p.x) - sqrt(abs(p.y)) + sf.c.x;
  r.y = sqr(p.y) - sqrt(abs(p.x)) + sf.c.y;
  return(r);
}

/*-----------------------------------------------------------------------------
 *  Set Colorings
 */

tsetcoloring setcoloringCreate(int type)
{
  tsetcoloring res;
  res.step = type == 2 ? &setcCurveEstimateStep  :
                         &setcGeneralStep;
  res.get  = type == 0 ? &setcTimeEscapeGet      :
             type == 1 ? &setcPotentialGet       :
             type == 2 ? &setcCurveEstimateGet   :
             type == 3 ? &setcEscapeAngleGet     :
                         &setcEscapeDistanceGet;
  return(res);
}

static void setcoloringInit(tsetpoint p, tsetcoloring *psc)
{
  psc->prev2   = psc->prev = psc->last = p;
  psc->min     = pointnull;
  psc->value   = 0;
  psc->iternum = 0;
  psc->mindistance = 1.0/0.0;
  psc->maxdistance = 0;
}

static void setcGeneralStep(tsetpoint p, tsetcoloring *psc)
{
  psc->iternum++;
  psc->last = p;
}

static void setcCurveEstimateStep(tsetpoint p, tsetcoloring *psc)
{
  tsetpoint a, b, c;
  double o, res;
  psc->iternum++;
  a.x = p.x - psc->prev.x;
  a.y = p.y - psc->prev.y;
  b.x = psc->prev.x - psc->prev2.y;
  b.y = psc->prev.x - psc->prev2.y;
  o = b.x*b.x + b.y*b.y;
  if (o != 0) {
    c.x = (a.x*b.x+a.y*b.y)/o;
    c.y = (a.y*b.x-a.x*b.y)/o;
    res = atan2(c.y, c.x);
  } else { res = 0; }
  if (res<0) { res = 2*PI - res; }
  psc->value += res;
  psc->prev2  = psc->prev;
  psc->prev   = p;
}

static double setcTimeEscapeGet(tsetcoloring sc)
{
  return(sc.iternum);
}

static double setcPotentialGet(tsetcoloring sc)
{
  double r = sqrt(sqr(sc.last.x) + sqr(sc.last.y));
  return ( (r==0) ? 0 : log(r)/pow(2,sc.iternum) );
}

static double setcCurveEstimateGet(tsetcoloring sc)
{
  return ( sc.value/sc.iternum );
}

static double setcEscapeAngleGet(tsetcoloring sc)
{
  return ( atan2(sc.last.y, sc.last.x) );
}

static double setcEscapeDistanceGet(tsetcoloring sc)
{
  return ( sqrt(sqr(sc.last.x)+sqr(sc.last.y)) );
}
