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

#ifndef BLENDING_H_
#define BLENDING_H_

#define BLENDINGS \
BLENDING(allanon,     res = (base+add)/2                                    ) \
BLENDING(multiply,    res = base*add                                        ) \
BLENDING(bleach,      res = (1-base)*(1-add)                                ) \
BLENDING(screen ,     res = 1-(1-base)*(1-add)                              ) \
BLENDING(divide,      res = base / add                                      ) \
BLENDING(add,         res = base + add                                      ) \
BLENDING(sub,         res = base - add                                      ) \
BLENDING(diff,        res = fabs(base-add)                                   ) \
BLENDING(difference,  res = base - add + 1                                  ) \
BLENDING(paralel,     res = 2/(1/base+1/add)                                ) \
BLENDING(darken,      res = add < base ? add : base                         ) \
BLENDING(lighten,     res = add > base ? add : base                         ) \
BLENDING(texture,     res = base + add - 0.5                                ) \
BLENDING(light,       res = base*(1-add)+add*add                            ) \
BLENDING(dark,        res = base*add+(1-add)*add                            ) \
BLENDING(ekvivalence, res = 1 - fabs(base-add)                               ) \
BLENDING(addSub,      res = fabs(base*base-add*add)                          ) \
BLENDING(pitagoras,   res = sqrt(base*base+add*add)/sqrt(2)                 ) \
BLENDING(arctan,      res = atan(2*atan2(add,1-base)/PI)                    ) \
BLENDING(exclusion,   res = base + add - 2 * base * add                     ) \
BLENDING(geomMean,    res = sqrt(base * add)                                ) \
BLENDING(gammaDark,   res = pow(base,add)                                   ) \
BLENDING(gammaLight,  res = pow(base,1/add)                                 ) \
BLENDING(burn,        res = base + add - 1                                  ) \
BLENDING(linearLight, res = base + 2 * add - 1                              ) \
BLENDING(colorDodge,  res = base / (1-add)                                  ) \
BLENDING(colorBurn,   res = 1-(1-base)/add                                  ) \
BLENDING(pinLight,    res = max(2*add-1,min(base,2*add))                    ) \
BLENDING(hardLight,   res = add < 0.5 ? 2*base*add : 1-2*(1-base)*(1-add)   ) \
BLENDING(softLight,   res = pow(base,pow(2,(2*(0.5-add))))                  ) \
BLENDING(vividLight,  res = add < 0.5 ? 1-(1-base)/(2*add) : base/(2*(1-add))) \
BLENDING(overlay,     res = add > 0.5 ? 2*base*add : 1-2*(1-base)*(1-add)   )

#define BLENDING(name,calc)                                                    \
extern void name(tMapF map0, tMapF map1, int w, int h, int fproc(int));

BLENDINGS

#endif /* BLENDING_H_ */

