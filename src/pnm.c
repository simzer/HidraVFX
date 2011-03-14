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
#include <string.h>

#include "layer.h"
#include "pnm.h"

int pfm_load(char *inFile, tLayerF *image)
{
  char buffer[1024];
  FILE *in = NULL;
  int x, y, w, h;
  float factor;
  char c;

  if (inFile != NULL)
  {
    in = (0 == strcmp(inFile, "--"))
         ? stdin
         : fopen(inFile, "r");
  }

  if (in == NULL) return(1);

  fgets(buffer, 1024, in);
  sscanf(buffer, "P%c", &c);
  while ((fgets(buffer, 1024, in) != NULL) && buffer[0] == '#');
  sscanf(buffer, "%d %d", &w, &h);
  while ((fgets(buffer, 1024, in) != NULL) && buffer[0] == '#');
  sscanf(buffer, "%f\n", &factor);

  *image = layerF(w, h);

  for (y = image->t; y < image->t + image->h; y++)
  {
    for (x = image->l; x < image->l + image->w; x++)
    {
      fread(&((image->ch[0][y])[x]), sizeof(float), 1, in);
      fread(&((image->ch[1][y])[x]), sizeof(float), 1, in);
      fread(&((image->ch[2][y])[x]), sizeof(float), 1, in);
      image->ch[3][y][x] = 1.0;
    }
  }

  fclose(in);

  return(0);
}

int pfm_save(char *outFile, tLayerF *image)
{
  FILE *out;
  int x, y;
  int res = 0;

  if (outFile != NULL)
  {
    out = fopen(outFile, "w");
    if (out == NULL) return(1);
  }
  else
  {
    out = stdout;
  }

  fprintf(out, "PF\n");
  fprintf(out, "%d %d\n", image->w, image->h);
  fprintf(out, "-1.0\n");

  for (y = image->t; y < image->t + image->h; y++)
  {
    for (x = image->l; x < image->l + image->w; x++)
    {
      fwrite(&((image->ch[0][y])[x]), sizeof(float), 1, out);
      fwrite(&((image->ch[1][y])[x]), sizeof(float), 1, out);
      fwrite(&((image->ch[2][y])[x]), sizeof(float), 1, out);
    }
  }

  fclose(out);

  return(res);
}
