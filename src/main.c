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
#include "../bin/effects.h"

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
    "   --aa=N             NxN anti alias if applicable (default = 1).\n"
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

tLayerF getOpt(char *name)
{
  tLayerF res;
  if  (opt_get(name) != NULL)
  {
    int err = pfm_load(opt_get(name), &res);
    if (err != 0)
    {
      res = layerbg(opt_getf(name));
    }
    else
    {/*
      if ((res.w != image.w) || (res.h != image.h))
      {
        err = 1;
        fprintf(stderr, "error %d: size of input pictures are not match\n", err);
        return(err);
      }*/
    }
  }
  else
  {
    res = layerbg(0.0);
  }
  return(res);
}

int main(int argc, char *argv[])
{
  int err;
  int i;
  char *inFile;
  char *outFile;
  char *command;
  tLayerF image;
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
    char err = 1;
    char *helpcommand = opt_get("2");
    if(helpcommand == NULL)
    {
      printf("%s", help_str);
      err = 0;
    }
    else
    {
      if (0 == strcmp(helpcommand, "commands"))
      {
        for(i = 0; i < effectnum; i++)
        {
          printf("  %-20s   %s\n", effectlist[i], effectdescs[i]);
        }
        printf("\n");
        err = 0;
      }
      for (i = 0; i < effectnum; i++)
      {
        if (0 == strcmp(helpcommand, effectlist[i]))
        {
          int n;
          printf("Command: %s\n  %s\n\n", effectlist[i], effectdescs[i]);
          printf("Available options for command %s:\n", effectlist[i]);
          for(n = 0; n < paramnums[i]; n++)
          {
            char buffer[50];
            int index = paramindices[i] + n;
            sprintf(buffer, "--%s=VALUE", paramlist[index]);
            printf("  %-15s   %s\n", buffer, paramdescs[index]);
          }
          printf("\n");
          err = 0;
        }
      }
      if (err != 0)
      {
        fprintf(stderr, "error %d: unknown command %s\n", err, helpcommand);
        return(err);
      }
    }
    opt_free();
    return(0);
  }

  outFile  = opt_get("out");
  inFile   = opt_get("2");

  if (inFile == NULL) { inFile = "--"; }
  err = pfm_load(inFile, &image);
  if (err != 0)
  {
    fprintf(stderr, "error %d: Could not read file %s\n", err, inFile);
    return(err);
  }

  err = 1;

  result = layerF(image.w, image.h);

#include "../bin/cmdproc.i"

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
