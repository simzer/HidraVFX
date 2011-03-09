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
#include "conform.h"

static char *help_str =
    "HidraVFX is a high dynamic range visual effect command line application."
    "\n"
    "Usage: hidravfx COMMAND [options] INPUTFILE\n"
    "\n"
    "File formats:\n"
    "   PFM                Portable Float Map.\n"
    "\n"
    "Options:\n"
    "   help               print this help page\n"
    "   help commands      prints command list\n"
    "   help COMMAND       prints option list for COMMAND\n"
    "   INPUTFILE          Input PFM format file. stdin used if not specified.\n"
    "   --out=FILE         Output PFM format file. stdout used if not specified.\n"
    "   --aa=#             anti alias switch 0=off, 1=on\n"
    "   --add=FILE         addition file for blendings.\n"
    "\n"
    "For bug reporting instructions see README.\n"
    "\n";

int print_process(int progress)
{
  if (progress < 100)
  {
    fprintf(stderr, "\033[0Gprogress: %d %%", progress);
  }
  else
  {
    fprintf(stderr, "\033[0Gprogress: %d %%, finished.\n", progress);
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
  tLayerF result;

  opt_init(argc, argv);

  command = opt_get("1");
  if (command == NULL)
  {
    err = 1;
    fprintf(stderr, "error %d: command not specified. Type 'hidravfx help' for usage.\n", err);
    return(err);
  }

  if (0 == strcmp(command, "help"))
  {
    command = opt_get("2");
    if(command == NULL)
    {
      printf("%s", help_str);
    }
    else if (0 == strcmp(command, "commands"))
    {
#undef  EFFECT
#undef  BLENDING
#define EFFECT(name, params, init, calc) printf("      " #name "\n");
#define BLENDING(name,calc)              printf("      " #name "\n");
      printf("\n   Effects:\n");       COLOREFFECTS
      printf("\n   Distortions:\n"); CONFORMS
      printf("\n   Blendings:\n");   BLENDINGS
    }
#undef  PF
#undef  PL
#undef  EFFECT
#define PF(name) "  " #name "\n"
#define PL(name) "  " #name "\n"
#define EFFECT(name, params, init, calc) \
    else if (0 == strcmp(command, #name)) { \
      printf("Available options for command " #name ":\n" params); \
    }
    COLOREFFECTS
    CONFORMS
    else
    {
      err = 1;
      fprintf(stderr, "error %d: unknown command %s\n", err, command);
      return(err);
    }

    opt_free();
    return(0);
  }

  outFile  = opt_get("out");
  inFile   = opt_get("2");
  addFile  = opt_get("add");

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
    if ((addimg.w != image.w) || (addimg.h != image.h))
    {
      err = 1;
      fprintf(stderr, "error %d: size of input pictures are not match\n", err);
      return(err);
    }
  }

  err = 1;

  result = layerF(image.w, image.h);

#undef EFFECT
#define EFFECT(name, params, init, calc) \
  if (0 == strcmp(command, #name))                                              \
  {                                                                             \
    name(image.ch[0], result.ch[0], image.w, image.h, print_process);           \
    name(image.ch[1], result.ch[1], image.w, image.h, print_process);           \
    name(image.ch[2], result.ch[2], image.w, image.h, print_process);           \
    print_process(100);                                                         \
    err = 0;            \
  }

  COLOREFFECTS
  CONFORMS

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
    result = image;     \
    err = 0;            \
  }

  BLENDINGS

  if (err != 0)
  {
    err = 1;
    fprintf(stderr, "error %d: unknown command %s\n", err, command);
    return(err);
  }

  err = pfm_save(outFile, &result);
  if (err != 0)
  {
    fprintf(stderr, "error %d: Could not write file %s\n", err, outFile);
    return(err);
  }

  opt_free();

  return(0);
}
