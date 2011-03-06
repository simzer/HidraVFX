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
#include "interpol.h"
#include "layer.h"

tLayerF layerF(int w, int h)
{
  tLayerF layer;
  int i, y;

  layer.l = 0;
  layer.t = 0;
  layer.w = w;
  layer.h = h;

  for (i = 0; i < 4; i++)
  {
    /* todo: check malloc return value */
    layer.ch[i] = malloc(h * sizeof(tMapF));
  }

  for (y = 0; y < h; y++)
  {
    for (i = 0; i < 4; i++)
    {
      /* todo: check malloc return value */
      layer.ch[i][y] = malloc(w * sizeof(tLineF));
    }
  }

  return(layer);
}

float mapGetPix(tMapF map, int x, int y, int t, int l, int w, int h)
{
  return( ((x>=l) && (x<l+w) && (y>=t) && (y<t+h))
          ? map[x-l][y-t] : 0.0/0.0 );
}

void mapSetPix(tMapF map, int x, int y, float pix, int t, int l, int w, int h)
{
  if ((x>=l) && (x<l+w) && (y>=t)  && (y<t+h)) map[x-l][y-t] = pix;
}

float mapGetAAPix(tMapF map, float x, float y, int t, int l, int w, int h)
{
  float x0,y0;
  int x1,y1,x2,y2;
  if ((x>=l) && (x<=l+w-1) && (y>=t) && (y<=t+h-1))
  {
     x1 = x;
     x0 = x-x1;
     y1 = y;
     y0 = y-y1;
     x1 = x1-l;
     y1 = y1-t;
     x2 = (x1==x) ? x1 : x1+1;
     y2 = (y1==y) ? y1 : y1+1;
     return linear2(map[y1][x1],map[y1][x2],map[y2][x1],map[y2][x2],x0,y0);
  }
  else
  {
    return(0.0/0.0);
  }
}



