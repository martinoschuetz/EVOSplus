
/* panic.c -- error handler for noninteractive utilities

   Copyright (C) 1991 Free Software Foundation, Inc.
   Copyright (C) 1992, 1993, 1994 Joerg Heitkoetter
		 1994 Martin Schuetz

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
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* based on `error.c' by David MacKenzie */

/*
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:41:22  schuetz
 * pvm integrated
 *
 * Revision 1.4  1994/07/06  07:10:23  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.4  1994/07/06  07:10:23  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.3  1994/06/06  16:29:59  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  14:47:42  schuetz
 * consistent version.
 *
 * Revision 1.1  1994/04/18  10:17:44  schuetz
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include <errno.h>
#include <time.h>
#include "define.h"
#include "panic.h"


#ifdef EDDIE
static char *adv[] =
{
  "Sirius Cybernetics(TM)",
  "charming",
  "core dumping",
  "dusty",
  "extraordinary",
  "faulty",
  "funny",
  "friendly",
  "humble",
  "irresistable",
  "joking",
  "marvellous",
  "mostly harmless",
  "old and tired",
  "rusty",
  "stupid",
  "terminating",
};
#define ADVSIZ	(sizeof(adv)/sizeof(char *))
#endif

#ifndef VPRINTF_MISSING

#ifdef __STDC__
#include <stdarg.h>
#define VA_START(args, lastarg) va_start(args, lastarg)
#else /* not __STDC__ */
#include <varargs.h>
#define VA_START(args, lastarg) va_start(args)
#endif /* __STDC__ */

#else /* not VPRINTF_MISSING */

#ifndef DOPRNT_MISSING
#define va_alist args
#define va_dcl int args;
#else /* DOPRNT_MISSING */
#define va_alist a1, a2, a3, a4, a5, a6, a7, a8
#define va_dcl char *a1, *a2, *a3, *a4, *a5, *a6, *a7, *a8;
#endif /* DOPRNT_MISSING */

#endif /* VPRINTF_MISSING */

#ifdef STDC_HEADERS
#include <stdlib.h>
#include <string.h>
#else /* not STDC_HEADERS */
void exit ();
#endif /* STDC_HEADERS */

#ifdef STRERROR_MISSING
static char *
private_strerror (errnum)
     int errnum;
{
  extern char *sys_errlist[];
  extern int sys_nerr;

  if (errnum > 0 && errnum < sys_nerr)
    return sys_errlist[errnum];
  return "Unknown system error";
}

#define strerror private_strerror
#endif /* STRERROR_MISSING */

/* Print the program name and error message MESSAGE, which is a printf-style
   format string with optional args.
   If ERRNUM is nonzero, print its corresponding system error message.
   Exit with status STATUS if it is nonzero. */
/* VARARGS */
int

#if !defined (VPRINTF_MISSING) && defined (__STDC__)
panic (int level, char *caller, char *message,...)
#else				/* VPRINTF_MISSING or not __STDC__ */
panic (level, caller, message, va_alist)
     int level;
     char *caller;
     char *message;
     va_dcl
#endif /* not VPRINTF_MISSING or __STDC__ */
{

#ifndef VPRINTF_MISSING
  va_list args;
#endif /* VPRINTF_MISSING */

#ifdef EDDIE
  srand (time (0));
  fprintf (stderr, "\n\007*** DON'T PANIC\n");
  fprintf (stderr, "Hi there, this is Eddie your %s ", adv[rand () % ADVSIZ]);
  fprintf (stderr, "shipboard computer\n");
  fprintf (stderr, "I really don't want to bother you, but I received\n");
  if ((program_name != NULL) && (*program_name != '\0'))
    fprintf (stderr, "the following error message from level %d while running `%s'...\n", level, program_name);
  else
    fprintf (stderr, "the following error message from level %d while running...\n", level);
#endif

  if (program_name != NULL && *program_name != '\0')
    fprintf (stderr, "%s: ", program_name);

  if (caller != NULL && *caller != '\0')
    fprintf (stderr, "%s: ", caller);

#ifndef VPRINTF_MISSING
  VA_START (args, message);
  vfprintf (stderr, message, args);
  va_end (args);
#else /* VPRINTF_MISSING */

#ifndef DOPRNT_MISSING
  _doprnt (message, &args, stderr);
#else /* DOPRNT_MISSING */
  fprintf (stderr, message, a1, a2, a3, a4, a5, a6, a7, a8);
#endif /* DOPRNT_MISSING */

#endif /* VPRINTF_MISSING */

  if (level == E_WARN || level == E_FATAL)
    {
      if (errno)
	fprintf (stderr, ": %s", (char *) strerror (errno));
    }

  if(level == A_WARN)
	fprintf (stderr, ": internal warning");
  else
    	fprintf (stderr, ": internal error");

  fprintf (stderr, ".\n");

#ifdef EDDIE
  fprintf (stderr, "***\n");
#endif

  fflush (stderr);

#ifdef EGREP_COMPAT
  if (level < 0)
	exit (2);			/* e?grep fatal return code */
#else
  if (level < 0)
	exit (1);
#endif

  return (level);
}
