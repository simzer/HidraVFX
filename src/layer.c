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

  for (i = 0; i < CHANNELS; i++)
  {
    /* todo: check malloc return value */
    layer.ch[i] = malloc(h * sizeof(tMapF));
    layer.bg[i] = 0.0/0.0;
  }

  for (y = 0; y < h; y++)
  {
    for (i = 0; i < CHANNELS; i++)
    {
      /* todo: check malloc return value */
      layer.ch[i][y] = malloc(w * sizeof(tLineF));
    }
  }

  return(layer);
}

tLayerF layerbgs(float bgs[])
{
  tLayerF layer;
  int i;

  layer.l = 0;
  layer.t = 0;
  layer.w = 0;
  layer.h = 0;

  for (i = 0; i < CHANNELS; i++)
  {
    layer.ch[i] = NULL;
    layer.bg[i] = bgs[i];
  }

  return(layer);
}

tLayerF layerbg(float bg)
{
  tLayerF layer;
  int i;

  layer.l = 0;
  layer.t = 0;
  layer.w = 0;
  layer.h = 0;

  for (i = 0; i < CHANNELS; i++)
  {
    layer.ch[i] = NULL;
    layer.bg[i] = bg;
  }

  return(layer);
}

float getpix(tLayerF l, int ch, int x, int y)
{
  return( ( (l.ch[ch] != NULL)
            && (x>=l.l) && (x<l.l+l.w) && (y>=l.t) && (y<l.t+l.h))
          ? l.ch[ch][y-l.t][x-l.l] : l.bg[ch] );
}

void setpix(tLayerF l, int ch, int x, int y, float pix)
{
  if ((l.ch[ch] != NULL)
      && (x>=l.l) && (x<l.l+l.w) && (y>=l.t)  && (y<l.t+l.h))
    l.ch[ch][y-l.t][x-l.l] = pix;
}

float getaapix(tLayerF l, int ch, float x, float y)
{
  float x0,y0;
  int x1,y1,x2,y2;
  if ((l.ch[ch] != NULL)
      && (x>=l.l) && (x<=l.l+l.w-1) && (y>=l.t) && (y<=l.t+l.h-1))
  {
     x1 = x;
     y1 = y;
     if((x1 == x) && (y1 == y))
     {
       return(l.ch[ch][y1][x1]);
     }
     else
     {
       x0 = x-x1;
       y0 = y-y1;
       x1 = x1-l.l;
       y1 = y1-l.t;
       x2 = (x1==x) ? x1 : x1+1;
       y2 = (y1==y) ? y1 : y1+1;
       return linear2(l.ch[ch][y1][x1],l.ch[ch][y1][x2],
                      l.ch[ch][y2][x1],l.ch[ch][y2][x2],
                      x0,y0);
     }
  }
  else
  {
    return(l.bg[ch]);
  }
}

/** Calculate statistics about image:
 *  \return error value */
int stats(tLayerF srcimg, tLayerStats *stats)
{
  int err = 0;
  int ix, iy, ch;
  int w = srcimg.w;
  int h = srcimg.h;
  int count = 0;
  for (ch = 0; ch < CHANNELS; ch++)
  {
    stats->min[ch]  = 0.0/0.0;
    stats->max[ch]  = 0.0/0.0;
    stats->mean[ch] = 0.0/0.0;
  }
  for (iy = 0; iy < h; iy++)
  {
    for (ix = 0; ix < w; ix++)
    {
      if(srcimg.ch[3][iy][ix] > 0.0)
      {
        for (ch = 0; ch < CHANNELS; ch++)
        {
          float src = srcimg.ch[ch][iy][ix];
          if (   (stats->min[ch] != stats->min[ch])
              || (src < stats->min[ch])) {
            stats->min[ch] = src;
          }
          if (   (stats->max[ch] != stats->max[ch])
              || (src > stats->max[ch])) {
            stats->max[ch] = src;
          }
          stats->mean[ch] = (stats->mean[ch] != stats->mean[ch])
                            ? src : stats->mean[ch] + src;
          count++;
        }
      }
    }
  }
  for (ch = 0; ch < CHANNELS; ch++)
  {
    stats->mean[ch] = stats->mean[ch]/count;
  }
  stats->visible = count;

  return(err);
}


