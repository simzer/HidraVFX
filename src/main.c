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

#include "options.h"
#include "layer.h"
#include "pnm.h"
#include "colorfx.h"
#include "blending.h"

static char *help_str =
    "Usage: hidravfx [command] [options]\n"
    "Options:\n"
    "  --cmd=<command>          Apply <command> effect on the input image\n"
    "                           (mandatory option)\n"
    "  --in=<file>              Input <file> PFM format file. stdin used if not specified.\n"
    "  --out=<file>             Output <file> PFM format file. stdout used if not specified.\n"
    "  --help                   print this help page"
    "\n"
    "For bug reporting instructions see README.\n"
    "\n";

int print_process(int progress)
{
  if (progress < 100)
  {
    printf("\033[0Gprogress: %d %%", progress);
  }
  else
  {
      printf("\033[0Gprogress: %d %%, finished.\n", progress);
  }
  return(1);
}

int main(int argc, char *argv[])
{
  int err;

  char *inFile;
  char *addFile;
  char *outFile;
  char *command;
  tLayerF image;
  tLayerF addimg;

  opt_init(argc, argv);

  if (opt_get("help") != NULL)
  {
    printf("%s", help_str);
    opt_free();
    return(0);
  }

  outFile = opt_get("out");
  inFile  = opt_get("in");
  addFile  = opt_get("add");
  command  = opt_get("cmd");

  err = pfm_load(inFile, &image);
  if (err != 0)
  {
    fprintf(stderr, "error %d: Could not read file %s\n", err, inFile);
    return(err);
  }

  if (addFile != NULL)
  {
    err = pfm_load(addFile, &addimg);
    if (err != 0)
    {
      fprintf(stderr, "error %d: Could not read file %s\n", err, addFile);
      return(err);
    }
  }

  err = 1;

#undef EFFECT
#define EFFECT(name,calc) \
  if (0 == strcmp(command, #name))                                              \
  {                                                                             \
    name(image.ch[0], image.w, image.h, print_process);                         \
    name(image.ch[1], image.w, image.h, print_process);                         \
    name(image.ch[2], image.w, image.h, print_process);                         \
    print_process(100);                                                         \
    err = 0;            \
  }

  COLOREFFECTS

#undef BLENDING
#define BLENDING(name,calc) \
  if (0 == strcmp(command, #name))                                              \
  {                                                                             \
    if (addFile == NULL)                                                        \
    {                                                                           \
      err = 1;                                                                  \
      fprintf(stderr, "error %d: additional file not specified.\n", err);       \
      return(err);                                                              \
    }                                                                           \
    name(image.ch[0], addimg.ch[0], image.w, image.h, print_process);           \
    name(image.ch[1], addimg.ch[1], image.w, image.h, print_process);           \
    name(image.ch[2], addimg.ch[2], image.w, image.h, print_process);           \
    print_process(100);                                                         \
    err = 0;            \
  }

  BLENDINGS

  if (err != 0)
    {
    fprintf(stderr, "error %d: unknown command %s\n", err, command);
    return(err);
    }

  err = pfm_save(outFile, &image);
  if (err != 0)
  {
    fprintf(stderr, "error %d: Could not write file %s\n", err, outFile);
    return(err);
  }

  opt_free();

  return(0);
}
