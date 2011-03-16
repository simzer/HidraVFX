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

#ifndef LAYER_H_
#define LAYER_H_

#include "color.h"

typedef float* tLineF;
typedef tLineF* tMapF;

#define CHANNELS 4

typedef struct
{
  int l, t, w, h;
  tMapF ch[CHANNELS];
  float bg[CHANNELS];
}
tLayerF;

extern tLayerF layerF(int w, int h);
extern tLayerF layerbg(float bg);
extern tLayerF layerbgs(float bgs[]);

float getaapix(tLayerF l, int ch, float x, float y);
void  setpix(tLayerF l, int ch, int x, int y, float pix);
float getpix(tLayerF l, int ch, int x, int y);

typedef struct
{
  float min[CHANNELS]; /**< minimum value per channel*/
  float max[CHANNELS]; /**< maximum value per channel*/
  float mean[CHANNELS];/**< mean value per channel*/
  float intmin;        /**< minimum intensity value */
  float intmax;        /**< maximum intensity value */
  float intmean;       /**< mean intensity value */
  int   visible;       /**< visible pixels */
}
tLayerStats;

extern int stats(tLayerF srcimg, tLayerStats *stats);

#endif
