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

#ifndef CONFORM_H_
#define CONFORM_H_

#include "effect.h"

#define CONFORMS \
EFFECT(bolyaiSphere,     PF(x0) PF(y0) PF(z0) PF(R),         ,            BOLYAISPHERE) \
EFFECT(spherize,         PF(x0) PF(y0) PF(rc) PF(factor),    ,            SPHERIZE) \
EFFECT(invbolyaiSphere,  PF(x0) PF(y0) PF(z0) PF(R),         ,            INVBOLYAISPHERE) \
EFFECT(polarToDescartes, ,                                   ,            POLARTODESCARTES) \
EFFECT(descartesToPolar, ,                                   ,            DESCARTESTOPOLAR) \
EFFECT(rotate,           PF(angle) PF(x0) PF(y0),            ROTATE_INIT, ROTATE) \
EFFECT(swirl,            PF(angle) PF(radial) PF(x0) PF(y0), SWIRL_INIT,  SWIRL) \
EFFECT(pinch,            PF(scale),                          ,            PINCH) \
EFFECT(sinusoidal,       PF(scale),                          ,            SINUSOIDAL) \
EFFECT(centermirror,     PF(x0) PF(y0),                      ,            CENTERMIRROR) \
EFFECT(axismirror,       PF(x0) PF(y0) PF(axisx) PF(axisy),  ,            AXISMIRROR) \
EFFECT(misterx,          PF(rad),                            ,            MISTERX) \
EFFECT(tube,             PF(x0) PF(y0) PL(numX) PL(numY)\
                         PF(rad) PL(dX) PL(dY),              TUBE_INIT,   TUBE) \
EFFECT(shift,            PF(x0) PF(y0),                      ,            SHIFT)

CONFORMS

#endif /* CONFORM_H_ */
