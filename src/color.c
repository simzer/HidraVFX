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
#include "color.h"

tcolorconv ccYIQ2RGB =
{{1, 0.95568806036115671171,  0.61985809445637075388,  0},
 {1, -0.27158179694405859326, -0.64687381613840131330, 0},
 {1, -1.1081773266826619523,  1.7050645599191817149,   0},
 {0, 0,                       0,                       1}};

tcolorconv ccRGB2YIQ =
{{0.299,   0.587,   0.114,   0},
 {0.596,  -0.275,  -0.321,   0},
 {0.212,  -0.523,   0.311,   0},
 {0,       0,       0,       1}};

tcolorconv ccLMS2RGB =
{{4.4679, -3.5873,  0.1193,  0},
 {-1.2186, 2.3809, -0.1624,  0},
 {0.0497, -0.2439,  1.2045,  0},
 {0,       0,       0,       1}};

tcolorconv ccRGB2LMS =
{{0.3811,  0.5783,  0.0402,  0},
 {0.1967,  0.7244,  0.0782,  0},
 {0.0241,  0.1288,  0.8444,  0},
 {0,       0,       0,       1}};

tcolorconv ccRGB2XYZ =
{{0.5141,  0.3239,  0.1604,  0},
 {0.2651,  0.6702,  0.0641,  0},
 {0.0241,  0.1228,  0.8444,  0},
 {0,       0,       0,       1}};

tcolorconv ccXYZ2RGB =
{{2.5655, -1.1668, -0.3988,  0},
 {-1.0220, 1.9780,  0.0440,  0},
 {0.0754, -0.2543,  1.1893,  0},
 {0,       0,       0,       1}};

tcolorconv ccYCbCr2RGB =
{{1.164,   0,       1.596,  -222.912/255},
 {1.164,  -0.392,  -0.813,   135.616/255},
 {1.164,   2.017,   0,      -276.8/255},
 {0,       0,       0,       1}};

tcolorconv ccRGB2YCbCr =
{{0.257,   0.504,   0.098,  1/16},
{-0.148,  -0.291,   0.439,  0.5},
{0.439,   -0.368,  -0.071,  0.5},
{0,        0,       0,      1}};

void recolor(float c0, float c1, float c2, float c3, tcolor res)
{
  res[0] = c0;
  res[1] = c1;
  res[2] = c2;
  res[3] = c3;
}

void decolor(tcolor src, float *c0, float *c1, float *c2, float *c3)
{
  *c0 = src[0];
  *c1 = src[1];
  *c2 = src[2];
  *c3 = src[3];
}

void colorconv(tcolor source, tcolorconv conv, tcolor target)
{
  int i, j;

  for(i = 0; i < CHANNELS; i++)
  {
    target[i] = 0;
    for (j = 0; j < CHANNELS; j++)
    {
      target[i] += conv[i][j] * source[j];
    }
  }
}

void ccRGB2HSV(tcolor src, tcolor tar)
{
  double R, G, B, H, S, V, minC, R1, G1, B1;
  R = src[0];
  G = src[1];
  B = src[2];
  H = 0;
  V = max(R,max(G,B));
  minC = min(R,min(G,B));
  S = (V != 0) ? (V-minC)/V : 0;
  if (S != 0) {
    R1=(R-minC)/(V-minC);
    G1=(G-minC)/(V-minC);
    B1=(B-minC)/(V-minC);
    H = (R == V) ? ((G == minC) ? 6-B1 : G1)
                 : ((G == V) ? ((B == minC) ? 2-R1 : 2+B1)
                             : ((R == minC) ? 4-G1 : 4+R1));
  };
  recolor(H/6, S, V, src[3], tar);
}

void ccHSV2RGB(tcolor src, tcolor tar)
{
  int I;
  double R, G, B, H, V, S, H1, F;
  double A[6];

  H = src[0];
  S = src[1];
  V = src[2];
  H1= H*6;
  I = (int)(H1);
  F = H1-I ;
  A[0] = A[1] = V;
  A[2] = V*(1-(S*F));
  A[3] = V*(1-S);
  A[4] = A[3];
  A[5] = V*(1-(S*(1-F)));
  I = (I>3) ? I-4 : I+2;
  R=A[I];
  I = (I>3) ? I-4 : I+2;
  B=A[I];
  I = (I>3) ? I-4 : I+2;
  G=A[I];
  recolor(R, G, B, src[3], tar);
}

void ccRGB2LAB(tcolor src, tcolor tar)
{
  double lum,alpha,beta,logL,logM,logS;
  tcolor LMS;
  colorconv(src, ccRGB2LMS, LMS);
  logL = (LMS[0]>0) ? log(LMS[0]) : 0;
  logM = (LMS[1]>0) ? log(LMS[1]) : 0;
  logS = (LMS[2]>0) ? log(LMS[2]) : 0;
  lum   = (1/sqrt(3)) * (logL+logM+logS);
  alpha = (1/sqrt(6)) * (logL+logM-2*logS);
  beta  = (1/sqrt(2)) * (logL-logM);
  recolor(lum, alpha, beta, src[3], tar);
}

void ccLAB2RGB(tcolor src, tcolor tar)
{
  double lum,alpha,beta,logL,logM,logS, s3,s6,s2;
  tcolor LMS;
  s3    = sqrt(3)/3;
  s6    = sqrt(6)/6;
  s2    = sqrt(2)/2;
  lum   = src[0];
  alpha = src[1];
  beta  = src[2];
  logL  = s3*lum+s6*alpha+s2*beta;
  logM  = s3*lum+s6*alpha-s2*beta;
  logS  = s3*lum-2*s6*alpha;
  recolor(exp(logL), exp(logM), exp(logS), src[3], LMS);
  colorconv(LMS, ccLMS2RGB, tar);
}

void ccRGB2HSI(tcolor src, tcolor tar)
{
  tcolor YC1C2;
  ccRGB2YC1C2(src, YC1C2);
  tar[2] = YC1C2[0];
  tar[1] = sqrt(sqr(YC1C2[1])+sqr(YC1C2[2]));
  tar[0] = (YC1C2[1] >= 0) ? acos(YC1C2[2]/tar[1]) : 2*PI-acos(YC1C2[2]/tar[1]);
  tar[0] /= (2*PI);
  tar[3] = src[3];
}

void ccRGB2YC1C2(tcolor src, tcolor tar)
{
  tar[0] = src[0]/3 + src[1]/3 + src[2]/3;
  tar[1] = src[0]   - src[1]/2 - src[2]/2;
  tar[2] = -sqrt(3)*src[1]/2-sqrt(3)*src[2]/2;
  tar[3] = src[3];
}
