
/* panic.h -- error handler for noninteractive utilities

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

/* stripped from `error.c' by David MacKenzie */

/* 
 * $Log $
 *
 */



#ifndef __PANIC_H__
#define __PANIC_H__

#define A_FATAL		(-2)	/* fatal error from application */
#define A_WARN		(2)	/* warning from application */

#define E_FATAL		(-1)	/* fatal system error */
#define E_WARN		(1)	/* warning from system */

extern char *program_name;	/* pointer to argv[0] */

#ifdef __STDC__
int panic (int level, char *caller, char *message, ...);
#else
int panic ();
#endif

#endif /* __PANIC_H__ */
