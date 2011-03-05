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
#include "layer.h"
#include "colorfx.h"

#undef EFFECT
#define EFFECT(name,calc)                                                       \
void name(tMapF map, int w, int h, int fproc(int))                              \
{                                                                               \
  int x, y;                                                                     \
  float src, tar;                                                               \
                                                                                \
  for (y = 0; y < h; y++)                                                       \
  {                                                                             \
    if (fproc != NULL) { fproc(y * 100 / h); }                                  \
                                                                                \
    for (x = 0; x < w; x++)                                                     \
    {                                                                           \
      src = map[y][x];                                                          \
      calc;                                                                     \
      map[y][x] = tar;                                                          \
    }                                                                           \
  }                                                                             \
}

#include "colorfx.inc"
