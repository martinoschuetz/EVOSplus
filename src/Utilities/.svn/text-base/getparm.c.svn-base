
/* getparm.c --  for JAZZ-C's device managers (implementation)

   Copyright (C) 1994 Joerg Heitkoetter

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

/* $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:41:22  schuetz
 * pvm integrated
 *
 * Revision 1.3  1995/02/06  08:14:08  schuetz
 * GUI version
 *
 * Revision 1.2  1994/06/06  16:29:59  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  16:29:59  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/04/18  10:17:44  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/04/18  10:17:44  schuetz
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "getparm.h"


/* searchopt -- looks up paramter `p' in the optionlist `opts', iff
   the parameter list `p' point to is not exhausted; if a match is
   encountered the associate flag is returned, otherwise GP_NOMATCH,
   indicates a failure of the search */

static int
searchopt (opts, optarg, p)
     struct option opts[];
     char *optarg;
     char *p;
{
  int i;

  if (p == NULL)
    return (EOF);

  for (i = 0; opts[i].name != NULL; i++)
    {
      while (isspace (*p))
	p++;
      if (!strncmp (opts[i].name, p, strlen (opts[i].name)))
	{
	  p += strlen (opts[i].name);
	  while (strchr (opts[i].sepchars, *p) != NULL)
	    p++;
	  strcpy (optarg, p);
	  return (opts[i].flag);
	}
    }
  return (GP_NOMATCH);
}


/* getparm -- implements a getopt alike parameter string parser:

     `s' contains the parameter string of the EBFN form:

	<var-string>	::= <var-def> {<GP_PARMSEP> <var-def>}
        <var-def>	::= <var-name> [<val-sepchars>] <var-val>
	<val-sepchars>	::= <GP_VALSEP>

     `opts' holds the option description triple:

	<var-name> <GP_VALSEP> <var-flag>

     the latter is the return value of getparm, when that parameter is
     matched.

     `optarg' is filled with <var-val>, i.e., the parameter's value,
     so it must be capable to hold sizeof(<var-val>) characters.

     In case no mtach is found, getparm returns the GP_NOMATCH char ('?'),
     and `optarg' is assigned the value of GP_EMPTY string ("<empty>"). */

int
getparm (s, opts, optarg)
     char *s;
     struct option opts[];
     char *optarg;
{
  static int getparminit = 1, c;
  static char buf[BUFSIZ];

  strcpy (optarg, GP_EMPTY);
  if (getparminit)
    {
      strcpy (buf, s);
      getparminit = 0;
      if ((c = searchopt (opts, optarg, strtok (buf, GP_PARMSEP))) == EOF)
	getparminit = 1;
    }
  else
    {
      if ((c = searchopt (opts, optarg, strtok (NULL, GP_PARMSEP))) == EOF)
	getparminit = 1;
    }
  return (c);
}


#ifdef TEST
static struct option opts[] =
{
  {"bba", GP_VALSEP, 'b'},
  {"noise", GP_VALSEP, 'n'},
  {0, 0, 0}
};

char *parms = "bba = on, noise = on";

int bbaflag;
int noiseflag;

main (argc, argv)
     int argc;
     char **argv;
{
  char optarg[BUFSIZ];
  int c;

  fprintf (stderr, "%s\n", parms);
  while ((c = getparm (parms, opts, optarg)) != EOF)
    {
      switch (c)
	{
	case 'b':
	  bbaflag = strcmp ("off", optarg) ? 1 : 0;
	  break;

	case 'n':
	  noiseflag = strcmp ("off", optarg) ? 1 : 0;
	  break;

	default:
	  fprintf (stderr, "error: `%c', %s\n", c, optarg);
	}
    }

  fprintf (stderr, "bbaflag: %d, noiseflag: %d\n", bbaflag, noiseflag);
}
#endif
