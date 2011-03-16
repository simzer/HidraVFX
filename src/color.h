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

#ifndef COLOR_H_
#define COLOR_H_

#define CHANNELS 4

typedef float tcolor[CHANNELS];

typedef float tcolorconv[CHANNELS][CHANNELS];

extern tcolorconv ccYIQ2RGB;
extern tcolorconv ccRGB2YIQ;
extern tcolorconv ccLMS2RGB;
extern tcolorconv ccRGB2LMS;
extern tcolorconv ccRGB2XYZ;
extern tcolorconv ccXYZ2RGB;
extern tcolorconv ccYCbCr2RGB;
extern tcolorconv ccRGB2YCbCr;

extern void ccRGB2HSV(tcolor src, tcolor tar);
extern void ccHSV2RGB(tcolor src, tcolor tar);
extern void ccRGB2LAB(tcolor src, tcolor tar);
extern void ccLAB2RGB(tcolor src, tcolor tar);
extern void ccRGB2HSI(tcolor src, tcolor tar);
extern void ccRGB2YC1C2(tcolor src, tcolor tar);

extern void recolor(float c0, float c1, float c2, float c3, tcolor res);
extern void decolor(tcolor src, float *c0, float *c1, float *c2, float *c3);

extern void colorconv(tcolor source, tcolorconv conv, tcolor target);


#endif
