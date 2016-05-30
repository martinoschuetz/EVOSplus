/*
 *        getparam: easy-to-use parameter processin
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
/*
 *    getparam.c
 *    ----------
 *
 *    Read parameters from a given input file, and from the command line.
 *    If the same parameter is defined twice, the one from the command
 *    line is taken.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "getparam.h"

#if !defined(EXIT_FAILURE)
#define EXIT_FAILURE 1
#endif

extern param_ascii_t *param;

static char stypes[][MAXKEY] =
{
    "string",
    "real",
    "integer",
    "boolean",
    "enum"
};

#define GETINT(p,v,r) (sscanf((v),"%d",(int *)((char *)(r)+(p)->offset)))
/* #define GETSTR(p,v,r) (sscanf((v),"%s",(char *)((char *)(r)+(p)->offset))) */
#define GETSTR(p,v,r) (strcpy((char *)((char *)(r)+(p)->offset),(v)))

#define GETDBL(p,v,r) (sscanf((v),"%lg",(double *)((char *)(r)+(p)->offset)))
#define GETBLN(p,v,r) (GETENM((p),(v),(r)))

int
GETENM(param_ascii_t * p, char *v, void *r)
{
    char *s, *s1;
    int pos;

    pos = 0;

    if ((s1 = (char *) malloc(strlen(p->val) + 1)) == NULL) {
	fprintf(stderr, "memory allocation failed in %s\n", __FILE__);
	exit(EXIT_FAILURE);
    }
    strcpy(s1, p->val);
    s = strtok(s1, "|");
    while (strncmp(s, v, strlen(s)) && (s = strtok(NULL, "|")))
	pos++;

    free(s1);

    if (s == NULL) {
	return 0;
    } else {
	*((int *) ((char *) (r) + (p)->offset)) = pos;
	return 1;
    }
}

int
splitline(char *line, char *key, char *value)
{
    char *s;

    if (sscanf(line, "%[^ \t=]", key) != 1)
	return 0;

    s = strchr(line, '=');
    while (s && *++s && isspace(*s) && *s != '\"');
    if (!s || !*s)
	return 0;
    if (*s == '\"') {
	for (s++; *s && *s != '\"'; *value++ = *s++);
	*value = '\0';
    } else {
	sscanf(s, "%[^\t# ]", value);
    }
    return (*s != '\0');
}

void
Usage(param_ascii_t * p, char *s)
{
    param_ascii_t *tmp;
    int h, key_width = 0, dsc_width = 0, val_width = 0;

    for (tmp = p; tmp->key[0] != '\0'; tmp++) {
	if ((h = strlen(tmp->key)) > key_width)
	    key_width = h;
	if ((h = strlen(tmp->dsc)) > dsc_width)
	    dsc_width = h;
	if ((h = strlen(tmp->val)) > dsc_width)
	    val_width = h;
    }
    fprintf(stderr, "# usage: %s [param-file] {key=value}\n\n", s);
    fprintf(stderr, "# valid keys are (key, description, type, values default):\n");
    fprintf(stderr, "#\n");
    for (; p->key[0] != '\0'; p++) {
	if (p->type == LABEL) {
	    fprintf(stderr, "LABEL %-*s \"%-s\"\n", key_width, p->key, p->dsc);
	} else {
	    fprintf(stderr, "%-*s %c \"%*s\" %-10s %-*s %-s\n",
		    key_width, p->key, p->set ? '*' : '!', dsc_width,
		    p->dsc, stypes[p->type], val_width, p->val, p->def);
	}
    }
    exit(EXIT_FAILURE);
}

void
ParamError(param_ascii_t * p, char *s)
{
    fprintf(stderr, "%s: format error\n", s);
    fprintf(stderr, "    Parameter   : %s\n", p->key);
    fprintf(stderr, "    Type        : %s\n", stypes[p->type]);
    fprintf(stderr, "    Description : %s\n", p->dsc);
    fprintf(stderr, "    Values      : %s\n", p->val);
    fprintf(stderr, "    Default     : %s\n", p->def);
    fprintf(stderr, "    Mandatory   : %s\n", p->set ? "no" : "yes");

    exit(EXIT_FAILURE);
}

char **
getparam(void *result, param_ascii_t * param, char **argv)
{
    FILE *f = NULL;
    param_ascii_t *p, *defptr;
    char *name, config[256];
    char key[MAXKEY], value[MAXKEY];
    char line[2 * MAXKEY];
    char *ptr;
    int ok;
    unsigned int setmask;

    name = *argv++;
    if (*argv && (*argv)[0] == '-' && (*argv)[1] == 'h') {
	Usage(param, name);
    }
    if (*argv && strchr(*argv, '=') == NULL && strcmp(*argv, "--")) {
	sprintf(config, "%s.in", *argv);
	if ((f = fopen(config, "r")) == NULL) {
	    if ((f = fopen(*argv, "r")) == NULL) {
		fprintf(stderr, "%s: cannot open configuration "
			"file %s[.in]\n", name, *argv);
		exit(EXIT_FAILURE);
	    }
	}
	argv++;
    }
    defptr = param;
    for (;;) {
	value[0] = '\0';
	if (defptr->key[0]) {
	    if (!defptr->def[0]) {
		defptr++;
		continue;
	    }
	    strncpy(key, defptr->key, MAXKEY);
	    strncpy(value, defptr->def, MAXKEY);
	    defptr++;
	    setmask = SET_DEFAULT;
	} else if (f && fgets(line, 2 * MAXKEY + 1, f) != NULL) {
	    for (ptr = line; *ptr && isspace(*ptr); ptr++);
	    if (!*ptr || *ptr == '#')
		continue;

	    if (!splitline(line, key, value)) {
		fprintf(stderr, "%s: format error in %s:\n"
			">>> %s\n", name, config, line);
	    }
	    setmask = SET_FILE;
	} else {
	    if (*argv == NULL)
		break;
	    if (strcmp(*argv, "--") == 0) {
		argv++;
		break;
	    }
	    if ((ptr = strchr(*argv, '=')) == NULL) {
		fprintf(stderr, "%s: format error in %s:\n"
			">>> %s\n", name, config, *argv);
	    }
	    *ptr = '\0';
	    strcpy(key, *argv);
	    *ptr = '=';
	    strcpy(value, ptr + 1);
	    argv++;
	    setmask = SET_COMMAND;
	}
	ok = 0;
	for (p = param; p->key[0] && !ok; p++) {
	    if (strncmp(p->key, key, MAXKEY) == 0) {
		switch (p->type) {
		case INT:
		    if (!GETINT(p, value, result))
			ParamError(p, name);
		    break;

		case STRING:
		    if (!GETSTR(p, value, result))
			ParamError(p, name);
		    break;

		case ENUM:
		    if (!GETENM(p, value, result))
			ParamError(p, name);
		    break;

		case DOUBLE:
		    if (!GETDBL(p, value, result))
			ParamError(p, name);
		    break;

		case BOOLEAN:
		    if (!GETBLN(p, value, result))
			ParamError(p, name);
		    break;

		case LABEL:
		    fprintf(stderr,
			    "%s: %s is not a valid parameter name\n",
			    name, p->key);
		    break;

		default:
		    fprintf(stderr,
			    "%s: Undefined parameter "
			    "type for %s\n", name, p->key);
		    break;
		}
		ok = 1;
		p->set |= setmask;
	    }
	}
	if (!ok)
	    fprintf(stderr,"%s: Unknown key identifier: %s.\n", name, key);
/*	    Usage(param, name);*/
    }
    ok = 1;
    for (p = param; p->key[0]; p++) {
	if (!p->set && p->type != LABEL) {
	    fprintf(stderr, "parameter '%s' not set\n", p->key);
	    ok = 0;
	}
    }
    if (!ok)
	exit(EXIT_FAILURE);
    if (f)
	fclose(f);
    return argv;
}

int
putparam(void *result, param_ascii_t * param, char *fname)
{
    FILE *f;
    param_ascii_t *p;
    int i, pos;
    char *s1, *s2;

    if ((f = fopen(fname, "w")) == NULL)
	return 0;
    for (p = param; p->key[0]; p++) {
/*	if (p->set < 2) {
	    fprintf(f, "# %-20s = %20s # %s\n", p->key, "<not set>", p->dsc);
	    continue;
	}*/
	switch (p->type) {
	case INT:
	    fprintf(f, "%-20s = %20d # %s\n",
		    p->key, *(int *) ((char *) result + p->offset), p->dsc);
	    break;

	case STRING:
	    if(strlen((char *) result + p->offset) < 1)
		fprintf(f, "# %-20s = %20s # %s\n",
			p->key, "<not set>", p->dsc);
	    else
		fprintf(f, "%-20s = \"%s\" # %s\n",
		    p->key, (char *) result + p->offset, p->dsc);
            break;

	case ENUM:
	case BOOLEAN:
	    pos = *(int *) ((char *) result + p->offset);
	    for (s1 = p->val, i = 0; i < pos; s1 = strchr(s1, '|') + 1, i++);
		if ((s2 = strchr(s1,'|'))) *s2 = '\0';
	    fprintf(f, "%-20s = %20s # %s\n", p->key, s1, p->dsc);
		if (s2) *s2 = '|';
		break;

	case DOUBLE:
	    fprintf(f, "%-20s = %20g # %s\n",
		 p->key, *(double *) ((char *) result + p->offset), p->dsc);
	    break;

	case LABEL:
	    fprintf(f, "# %s\n", p->dsc);
	    break;
	}
    }
    fclose(f);
    return 1;
}

int
gpIsSet(char *s, param_ascii_t * param)
{
    while (param->key[0] && strncmp(s, param->key, MAXKEY))
	param++;
    return param->key[0] ? param->set : 0;
}
