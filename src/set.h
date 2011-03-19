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

#ifndef SET_H_
#define SET_H_

typedef struct { double x, y; } tsetpoint;
typedef struct sset             tsetformula;
typedef struct ssetcoloring     tsetcoloring;
typedef struct ssetmodel        tsetmodel;

typedef tsetpoint (*tsetformulastep)(tsetpoint p, tsetformula sf);
typedef void      (*tsetcoloringstep)(tsetpoint p, tsetcoloring *psc);
typedef double    (*tsetcoloringget)(tsetcoloring sc);

struct sset
{
  tsetpoint c;
  tsetpoint prev;
  int       mode;
  tsetformulastep  step;
};

struct ssetcoloring
{
  double value;
  double mindistance;
  double maxdistance;
  int    iternum;
  tsetpoint last;
  tsetpoint min;
  tsetpoint prev;
  tsetpoint prev2;
  tsetcoloringstep step;
  tsetcoloringget  get;
};

struct ssetmodel
{
  tsetformula  fset;
  tsetcoloring fcoloring;
  int    maxiteration;
  double maxdistance;
  tsetpoint min, max;
};

extern tsetpoint    setpoint(double x, double y);
extern tsetformula  setformulaCreate(int mode, tsetpoint p, int type);
extern tsetcoloring setcoloringCreate(int type);
extern tsetmodel setmodelCreate(tsetformula  sf,
                                tsetcoloring sc,
                                int maxiteration,
                                tsetpoint min,
                                tsetpoint max);

extern double setiteration(tsetpoint p, tsetmodel sm);

#endif
