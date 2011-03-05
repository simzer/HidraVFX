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

#define COLOREFFECTS \
EFFECT(none,      tar = src                  ) \
EFFECT(invert,    tar = 1.0 - src            ) \
EFFECT(pitinvert, tar = sqrt(1.0 - src*src)  ) \

#define EFFECT(name,calc)                                                       \
extern void name(tMapF map, int w, int h, int fproc(int));

COLOREFFECTS

#endif
