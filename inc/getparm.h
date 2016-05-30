
/* getparm.h --  for JAZZ-C's device managers (interface)

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
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 * Revision 1.1  1995/04/19  14:56:37  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 *
 * Revision 1.1  1994/04/18  10:41:36  schuetz
 * Initial revision
 * */

#ifndef __GETPARM_H__
#define __GETPARM_H__

#define GP_PARMSEP		","
#define GP_VALSEP		"\n\t\v ="
#define GP_EMPTY		"<empty>"
#define GP_NOMATCH		'?'

struct option
  {
    char *name;			/* parameter name */
    char *sepchars;		/* chars between <var-name> and <var-val> */
    int flag;			/* flag to return when matched */
  };

#if defined(__STDC__) || defined(__cplusplus)
int getparm (char *s, struct option opts[], char *optarg);
#else
int getparm (/* char *s, struct option opts[], char *optarg */);
#endif

#endif	/* __GETPARM_H__ */

