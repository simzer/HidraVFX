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

#ifndef EFFECT_H_
#define EFFECT_H_

#define PF(var) float var = opt_getf(#var);
#define PL(var) int   var = opt_getl(#var);

#define EFFECT(name, params, init, calc) \
extern void name(tMapF map, tMapF res, int w, int h, int fproc(int));

#endif /* EFFECT_H_ */
