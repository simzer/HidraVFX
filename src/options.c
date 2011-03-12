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

static char** opt_keys = NULL;
static char** opt_vals = NULL;
static int optc = 0;

void opt_free(void)
  {
  int i;

  for(i = 0; i < optc; i++)
    {
    free(opt_keys[i]);
    free(opt_vals[i]);
    }

  free(opt_keys);
  free(opt_vals);
  }

int opt_init(int argc, char *argv[])
  {
  int i;

  char *key;
  int key_len;
  char *val;
  int val_len;
  int argnum = 0;
  char *p_eq;

  optc = argc;

  opt_keys = malloc(optc * sizeof(char *));
  opt_vals = malloc(optc * sizeof(char *));

  if (NULL == opt_keys) return(1);
  if (NULL == opt_vals) return(1);

  for(i = 0; i < argc; i++)
    {
    key = NULL;
    val = NULL;

    if (   (argv[i][0] == '-')
        && (argv[i][1] == '-') )
      {
      p_eq = strchr(argv[i], '=');

      if (p_eq != NULL)
        {
        key_len = p_eq - argv[i] - 2 /* -- */ + 1 /* \0 */;
        val_len = argv[i] + strlen(argv[i]) - p_eq;

        key = malloc(key_len);
        val = malloc(val_len);

        if (NULL == key) return(1);
        if (NULL == val) return(1);

        strncpy(key, argv[i] + 2, key_len);
        key[key_len-1]='\0';
        strncpy(val, p_eq + 1, val_len);
        }
      else
        {
        /* no value assigned to key */
        key_len = strlen(argv[i]) - 2 /* -- */ + 1 /* \0 */;
        val_len = 1+1;

        key = malloc(key_len);
        val = malloc(val_len);

        if (NULL == key) return(1);
        if (NULL == val) return(1);

        strncpy(key, argv[i] + 2, key_len);
        strncpy(val, "1", val_len);
        }
      }
    else
      {
      /* no standard long option */
      val_len = strlen(argv[i]) + 1 /* \0 */;
      key_len = 5+1;

      key = malloc(key_len);
      val = malloc(val_len);

      if (NULL == key) return(1);
      if (NULL == val) return(1);

      strncpy(val, argv[i], val_len);
      sprintf(key, "%d", argnum);
      argnum++;
      }

    opt_keys[i] = key;
    opt_vals[i] = val;
    }

  return(0);
  }

int opt_get_id(char* key)
  {
  int i;

  if (opt_keys != NULL)
    {
    for (i = 0; i < optc; i++)
      {
      if (   (opt_keys[i] != NULL)
          && (strcmp(opt_keys[i],key) == 0) )
        {
        return(i);
        }
      }
    }

  return(-1);
  }

char* opt_gets(char* key)
  {
  int i = opt_get_id(key);

  if (i != -1)
    {
    return(opt_vals[i]);
    }
  else
    {
    return(NULL);
    }
  }

float opt_getf(char* key)
  {
  char *val = opt_gets(key);
  return((val != NULL) ? strtof(val, NULL) : 0.0/0.0);
  }

long int opt_getl(char* key)
  {
  char *val = opt_gets(key);
  return((val != NULL) ?strtol(val, NULL, 10) : 0);
  }
