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
