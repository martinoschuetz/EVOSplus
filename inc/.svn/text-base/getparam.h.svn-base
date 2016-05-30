/*
 *      SES - Simple Evolution Strategy
 *
 *      Copyright (C) 1994 Joachim Sprave
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


/*
 *      See README for details of ES.
 *      Send bugs (better: bug descriptions) and comments to
 *
 * /---------------------------------------------------------------------\
 * | Joachim Sprave                  joe@ls11.informatik.uni-dortmund.de |
 * |                      //////\\                                       |
 * | Univ. Dortmund      /        \        44221 Dortmund                |
 * | Dept. CS           _|  _   _ |_       Tel.: +49-231-755 4678        |
 * | Systems Analysis  |.|-(.)-(.)+.|      Fax : +49-231-755 2450        |
 * \------------------  \|    J   |/  -----------------------------------/
 *                       \   ---  /
 *                        \      /
 *                         "####"
 */

#ifndef GETPARAM_H
#define GETPARAM_H

#include <stdlib.h>

#define MANDATORY 0
#define OPTIONAL  1

#define SET_COMMAND	2
#define SET_FILE	4
#define SET_DEFAULT	8

#define gpSetByCommand(s,p)	(gpIsSet(s,p) & SET_COMMAND)
#define gpSetByFile(s,p)	(gpIsSet(s,p) & SET_FILE)
#define gpSetByDefault(s,p)	(gpIsSet(s,p) & SET_DEFAULT)

  typedef enum {
      STRING, DOUBLE, INT, BOOLEAN, ENUM, LABEL
  } type_t;

#define MAXKEY 2048

typedef struct {
      char key[MAXKEY];		/* keyword */
      char dsc[MAXKEY];
      type_t type;		/* type, one of STRING, DOUBLE, INT, BOOLEAN, ENUM	*/
      char val[MAXKEY];
      char def[MAXKEY];
      int set;			/* == 1 if this entry must not be set, else 0 */
      size_t offset;		/* offset to the beg. of the par. struct */
  }
param_ascii_t;

#define END_PARAMS  { "","",INT,"","",OPTIONAL,0}

char  **getparam(void *result, param_ascii_t * param, char **argv);
int     putparam(void *result, param_ascii_t * param, char *fname);
int	gpIsSet(char *s, param_ascii_t *param);

#if !defined(offsetof)
#define offsetof(type,member) ((size_t) &(((type *)0)->member))
#endif

/*
 * for compatibilty to ver 1.1
 */
#define gpGetOpt getparam
#define gpPutOpt getparam

#endif /* GETPARAM_H */
