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

#ifndef DATATYPES_H_
#define DATATYPES_H_

typedef float* tLineF;
typedef tLineF* tMapF;

typedef struct
{
  int l, t, w, h;
  tMapF ch[4];
}
tLayerF;

extern tLayerF layerF(int w, int h);

float mapGetAAPix(tMapF map, float x, float y, int t, int l, int w, int h);
void mapSetPix(tMapF map, int x, int y, float pix, int t, int l, int w, int h);
float mapGetPix(tMapF map, int x, int y, int t, int l, int w, int h);

#endif
