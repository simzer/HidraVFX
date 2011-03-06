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

#ifndef INTERPOL_H_
#define INTERPOL_H_

static inline float linear1(float x1, float x2, float u)
{
  return(x1*(1-u)+x2*u);
}

static inline float linear2(float x11, float x21, float x12, float x22, float u,float v)
{
  return ((1-u)*x11+u*x21)*(1-v)+v*((1-u)*x12+u*x22);
}

static inline float cosine1(float x1, float x2,float u)
{
  u = (1-cos(u*PI))*0.5;
  return (x1*(1-u)+x2*u);
}

static inline float cosine2(float x11, float x21, float x12, float x22, float u, float v)
{
  u = (1-cos(u*PI))*0.5;
  v = (1-cos(v*PI))*0.5;
  return ((x11*(1-u)+x21*u)*(1-v)+(x12*(1-u)+x22*u)*v);
}

static inline float cubic1(float x1, float x2, float u)
{
  u =(4/9)*pow(u,6)-(17/9)*pow(u,4)+(22/9)*sqr(u);
  return(x1*(1-u)+x2*u);
}

static inline float cubic2(float x11, float x21, float x12, float x22, float u, float v)
{
  u = (4/9)*pow(u,6)-(17/9)*pow(u,4)+(22/9)*sqr(u);
  v = (4/9)*pow(v,6)-(17/9)*pow(v,4)+(22/9)*sqr(v);
  return((x11*(1-u)+x21*u)*(1-v)+(x12*(1-u)+x22*u)*v);
}

#endif
