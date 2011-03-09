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

#ifndef COLORFX_H_
#define COLORFX_H_

#include "effect.h"

#define COLOREFFECTS \
EFFECT(none,      ,          , tar = src;                               ) \
EFFECT(invert,    ,          , tar = 1.0 - src;                         ) \
EFFECT(geoinvert, ,          , tar = 0.001/sqrt(src);                   ) \
EFFECT(pitinvert, ,          , tar = sqrt(1.0 - src*src);               ) \
EFFECT(upshift,   PF(shift), , tar = src + shift; tar = tar - (int)tar; ) \
EFFECT(bright,    PF(bright),, tar = src + bright;                      ) \
EFFECT(contrast,  PF(gain),  , tar = (src - 0.5) * gain + 0.5;          ) \
EFFECT(bright2,   PF(bright),, tar = (bright < 0) ? src*(1.0+bright) \
                                                  : src+(1.0-src)*bright; ) \
EFFECT(stone,     PF(power),  , tar = 1.0 - pow(1.0-src, power);        ) \
EFFECT(cloud,     PF(limit) PF(xmax), , \
  tar = src<=limit ? 0 : log(xmax*(src-limit)/(1.0-limit)+1)/log(xmax+1); ) \



COLOREFFECTS

#endif
