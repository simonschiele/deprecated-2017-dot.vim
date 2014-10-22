/* fopenv.c : this function attempts to open a file based on the
 *   environment variable if an fopen in the current directory fails.
 *   The environment string can have ";" as separators for multiple
 *   path searching.  Returns a NULL pointer if unsuccessful.
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#include <stdio.h>
#include <ctype.h>
#include "xtdio.h"

/* -----------------------------------------------------------------------
 * Definitions:
 */
#define CTRLBUF	32
#ifdef unix
# define PATHSEP ":"
#endif

#ifdef _AIX
# define PATHSEP ":"
#endif

#ifdef vms
# define PATHSEP ";"
#endif

#ifdef AZTEC_C
# define PATHSEP ";,"
#endif

#if defined(MSDOS) || defined(__BORLANDC__)
# define msdos
# define PATHSEP ";,"
#endif

#ifndef PATHSEP
# define PATHSEP ":"
#endif

/* -----------------------------------------------------------------------
 * Global Variable:
 */
char *fopenvfile= NULL;	/* points to allocate opened-filename storage */

/* -----------------------------------------------------------------------
 * Source Code:
 */

/* fopenv: opens file for read/write based on environment variable
 *	char *filename : name of file to be opened
 *	char *ctrl     : "r", "w", etc.
 *	                 "R", "W", "A" will cause fopenv to only attempt to
 *	                 open the file using "r", "w", "a" in directories along
 *	                 the env_var path (if either env or env_var are null,
 *	                 then opening with the current directory is attempted
 *	                 anyway).
 *	char *env_var  : environment variable to be used
 *
 * Side Effect: fopenvfile will point to any successfully opened file
 *  There is only one copy.  Its memory will be automatically freed upon
 *  entry to this routine.
 */
FILE *fopenv(char *filename,char *ctrl,char *env_var)
{
FILE *fp       = NULL;
char  charhold;
char  ctrlbuf[CTRLBUF];
char *brk      = NULL;
char *endchar  = NULL;
char *env      = NULL;
char *s        = NULL;
int   buflen   = 0;
int   fnlen;


/* free up old fopenvfile */
if(fopenvfile) {
	free(fopenvfile);
	fopenvfile= NULL;
	}

#ifdef msdos
/* an exception for "good" old stupid msdos */
for(s= env_var; *s; ++s) if(islower(*s)) *s= toupper(*s);
#endif

/* check out the environment variable */
env= (env_var && *env_var)? getenv(env_var) : NULL;

/* see if file can be opened in current directory first */
strcpy(ctrlbuf,ctrl);
if(!isupper(ctrlbuf[0])) fp= fopen(filename,ctrlbuf);
else {
	ctrlbuf[0]= tolower(ctrlbuf[0]);
	if(!env) fp= fopen(filename,ctrlbuf);
	}
if(fp) {
	stralloc(fopenvfile,filename,"fopenv");
	return fp;
	}

/* attempt to open filename using environment search */
if(env) {

	/* fnlen used to compute buflen requirements */
	fnlen= strlen(filename);

	for(s= brk= env; brk; s= brk + 1) {

		/* determine end-of-token pointers brk and endchar */
		brk    = stpbrk(s,PATHSEP);
		endchar= brk? brk-1 : s+strlen(s)-1;

		/* allocate memory (as needed) to hold token */
		if(endchar - s + 4 + fnlen > buflen) {
			if(fopenvfile) free(fopenvfile);
			buflen    = endchar - s + fnlen + 4;
			fopenvfile= (char *) calloc((size_t) buflen,sizeof(char));
			}

		/* terminate token with null byte */
		charhold  = endchar[1];
		endchar[1]= '\0';

#ifdef vms
		if(*endchar == ':' || *endchar == ']') sprintf(fopenvfile,"%s%s",s,filename);
		else                                   sprintf(fopenvfile,"[%s]%s",s,filename);
#endif
#ifdef unix
		if(*endchar == '/')  sprintf(fopenvfile,"%s%s",s,filename);
		else                 sprintf(fopenvfile,"%s/%s",s,filename);
#endif
#ifdef LATTICE
		if(*endchar == '\\') sprintf(fopenvfile,"%s%s",s,filename);
		else                 sprintf(fopenvfile,"%s\\%s",s,filename);
#endif
#ifdef DESMET
		if(*endchar == '\\') sprintf(fopenvfile,"%s%s",s,filename);
		else                 sprintf(fopenvfile,"%s\\%s",s,filename);
#endif
#ifdef msdos
		if(*endchar == '\\') sprintf(fopenvfile,"%s%s",s,filename);
		else                 sprintf(fopenvfile,"%s\\%s",s,filename);
#endif
#ifdef AZTEC_C
		if(*endchar == ':' || *endchar == '/') sprintf(fopenvfile,"%s%s",s,filename);
		else                                   sprintf(fopenvfile,"%s/%s",s,filename);
#endif

		/* attempt to open file given the path */
		fp= fopen(fopenvfile,ctrlbuf);

		if(fp) { /* successfully opened file */
			return fp;
			}
		endchar[1]= charhold;
		}

	/* free up memory holding unsuccessfully opened filename */
	if(fopenvfile) {
		free(fopenvfile);
		fopenvfile= NULL;
		}
	}	/* if env ... */

/* return NULL pointer, thereby indicating a modest lack of success */
return (FILE *) NULL;
}

/* -----------------------------------------------------------------------
 * Test Code:
 */

/* --------------------------------------------------------------------- */
