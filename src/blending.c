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
#include <math.h>
#include "mathplus.h"
#include "layer.h"
#include "blending.h"

#undef BLENDING
#define BLENDING(name,calc)                                                     \
void name(tMapF map0, tMapF map1, int w, int h, int fproc(int))                 \
{                                                                               \
  int x, y;                                                                     \
  float res, base, add;                                                         \
  for (y = 0; y < h; y++)                                                       \
  {                                                                             \
    if (fproc != NULL) { fproc(y * 100 / h); }                                  \
                                                                                \
    for (x = 0; x < w; x++)                                                     \
    {                                                                           \
      base = map0[y][x];                                                        \
      add  = map1[y][x];                                                        \
      calc;                                                                     \
      map0[y][x] = res;                                                         \
    }                                                                           \
  }                                                                             \
}

BLENDINGS
