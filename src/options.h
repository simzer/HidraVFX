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

#ifndef OPTIONS_H_
#define OPTIONS_H_

#define opt_get(param) opt_gets(param)

/** Initialise options. */
extern int opt_init(int argc, char *argv[]);

/** Gets option index for key */
int opt_get_id(char* key);

/** Checks if option exists */
int opt_exists(char* key);

/** Gets option string for key */
extern char* opt_gets(char* key);

/** Gets option in different format  */
float opt_getf(char* key);
long int opt_getl(char* key);

/** Free memory allocated by opt. */
extern void opt_free(void);

#endif /* OPTIONS_H_ */
