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
#include <stdio.h>
#include <math.h>
#include <mathplus.h>
#include "layer.h"
#include "convolution.h"

double cmminifinger[]    = {  0, -1,  0,     1,  1,  1,     0, -1,  0};
double cmledge[]         = {  0,  1,  0,     1, -4,  1,     0,  1,  0};
double cmmedge[]         = { -1, -1, -1,    -1,  8, -1,    -1, -1, -1};
double cmhedge[]         = {  1, -2,  1,    -2,  4, -2,     1, -2,  1};
double cmhorprewitt[]    = { -1,  0,  1,    -1,  0,  1,    -1,  0,  1};
double cmverprewitt[]    = { -1, -1, -1,     0,  0,  0,     1,  1,  1};
double cmhorsobel[]      = { -1,  0,  1,    -2,  0,  2,    -1,  0,  1};
double cmversobel[]      = { -1, -2, -1,     0,  0,  0,     1,  2,  1};
double cmgauss[]         = {  1,  2,  1,     2,  4,  2,     1,  2,  1};
double cmenhancededge[]  = { -1, -1, -1,    -1,  9, -1,    -1, -1, -1};
double cmendy[]          = {  0, -1,  0,    -1, 10, -1,     0, -1,  0};
double cmenhancedfocus[] = { -1,  0, -1,     0,  7,  0,    -1,  0, -1};
double cmsharpen[]       = {  0, -1,  0,    -1,  5, -1,     0, -1,  0};
double cmemboss1[]       = {  1,  1,  0,     1,  0, -1,     0, -1, -1};
double cmemboss2[]       = { -1,  0,  0,     0,  0,  0,     0,  0,  1};
double cmlsoften[]       = {  6, 12,  6,    12, 25, 12,     6, 12,  6};
double cmhsoften[]       = { 11, 11, 11,    11, 11, 11,    11, 11, 11};
double cmlblur[]         = {  1,  2,  1,     2,  2,  2,     1,  2,  1};
double cmmblur[]         = {  1,  1,  1,     1,  1,  1,     1,  1,  1};
double cmlabirintXS[]    = { -2,  1, -2,     1,  5,  1,    -2,  1, -2};
double cmmsoften[]       = {  1,  1,  1,     1,  2,  1,     1,  1,  1};
double cmfinger[]        = {  0, 50,  0,  0,  0,      0,  0,-50,  0, 50,      0,-50,  1,-50,  0,      50,  0,-50,  0,  0,       0,  0,  0, 50,  0};
double cminstacfingerprint[]={0, -1,  0,  0,  0,      0,  0, -1,  0,  1,      0,  1,  1,  1,  0,       1,  0, -1,  0,  0,       0,  0,  0, -1,  0};
double cmgaussM[]        = {  1,  2,  3,  2,  1,      2,  4,  6,  4,  2,      3,  6,  9,  6,  3,       2,  4,  6,  4,  2,       1,  2,  3,  2,  1};
double cmreducedjaggies[]= {  0,  0, -1,  0,  0,      0,  0,  3,  0,  0,     -1,  3,  7,  3, -1,       0,  0,  3,  0,  0,       0,  0, -1,  0,  0};
double cmpsychedelic[]   = {  0, -1, -2, -3, -4,      0, -1,  3,  2,  1,      0, -1, 10,  2,  1,       0, -1,  3,  2,  1,       0, -1, -2, -3, -4};
double cmlitograph[]     = { -1, -1, -1, -1, -1,     -1,-10,-10,-10, -1,     -1,-10, 98,-10, -1,      -1,-10,-10,-10, -1,      -1, -1, -1, -1, -1};
double cmlabirintS[]     = { -1, -1,  1, -1, -1,     -1,  1,  2,  1, -1,      1,  2,  1,  2,  1,      -1,  1,  2,  1, -1,      -1, -1,  1, -1, -1};
double cmlabirintM[]     = { -1, -1,  1, -1, -1,     -1,  2,  2,  2, -1,      1,  2,  4,  2,  1,      -1,  2,  2,  2, -1,      -1, -1,  1, -1, -1};
double cmlabirintL[]     = { -1, -1,  1, -1, -1,     -1,  2,  4,  2, -1,      1,  4,  4,  4,  1,      -1,  2,  4,  2, -1,      -1, -1,  1, -1, -1};
double cmlabirintXL[]    = { -1, -1,  1, -1, -1,     -1,  2,  4,  2, -1,      1,  4,  4,  4,  1,      -1,  2,  4,  2, -1,      -1, -1,  1, -1, -1};
double cmbasreliefHD[]   = { -1, -1, -1, -1,  1,     -1, -1,  1,  1,  1,      1,  1,  1,  1,  1,      -1, -1,  1,  1,  1,      -1, -1, -1, -1,  1};
double cmbasreliefMD[]   = { -1,  0, -1,  0,  1,      0, -1,  0,  1,  0,      1,  0,  1,  0,  1,       0, -1,  0,  1,  0,      -1,  0, -1,  0,  1};
double cmbasreliefLD[]   = {  0,  0, -1,  0,  1,      0,  0,  0,  1,  0,     -1,  0,  0,  0,  0,       0,  0,  0,  1,  0,       0,  0, -1,  0,  1};
double cmpointilistic[]  = { -1, -1, -1, -1, -1,     -1,  2,  2,  2, -1,     -1,  2, 16,  2, -1,      -1,  2,  2,  2, -1,      -1, -1, -1, -1, -1};

double convolution(tLayerF src, int ix, int iy, int ch, double matrix[], int w, int h)
{
  double sum = 0, size = 0, pre, post, x, y;
  int n, m;
  for (n = 0; n < w-1; n++)
  {
    x = ix + n - w / 2;
    for(m = 0; m < h-1; m++)
    {
      y = iy + m - h / 2;
      pre   = getpix(src, ch, x, y);
      size += matrix[m*w + n];
      sum   = sum+pre*matrix[m*w + n];
    }
  }
  post = (size == 0) ? sum : sum/size;
  return(post);
}
