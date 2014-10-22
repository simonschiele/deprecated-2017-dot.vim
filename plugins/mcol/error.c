/* error.c: this file contains an error function
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 *
 *  error(XTDIO_SEVERE,"format",vars);  -- terminates after issuing printf-style
 *  error(XTDIO_ERROR,"format",vars);   -- terminates after issuing printf-style
 *  error(XTDIO_WARNING,"format",vars); -- issues printf-style and returns
 *  error(XTDIO_NOTE,"format",vars);    -- issues printf-style and returns
 *
 * "terminates": actually calls (*error_exit)(1)
 *               which defaults to error(int), but the programmer can
 *               override.
 *
 *   Author: Dr. Charles E. Campbell, Jr.
 */
#include <stdio.h>
#include <ctype.h>
#include "xtdio.h"

/* ------------------------------------------------------------------------
 * Definitions:
 */
#define TERMINATE	1

/* ------------------------------------------------------------------------
 * Global Variables:
 */

/* ------------------------------------------------------------------------ */

/* error: print out an error message:
 *		error(severity,fmt,...)
 * or	error(severity,errfunc,fmt,...)
 *
 * where
 *
 *	severity: severity of error
 *		XTDIO_SEVERE   : severe error    - will terminate
 *		XTDIO_ERROR    : error           - will terminate
 *		XTDIO_WARNING  : warning message
 *		XTDIO_NOTE     : notification
 *		XTDIO_USAGE    : provides a usage note
 *		XTDIO_ERRORMORE: continuation line (for XTDIO_WARNING and XTDIO_NOTE)
 *
 *	fmt    : printf format specification
 *	...    : arguments for the fmt
 *
 *	errfunc: 
 *	         will be called
 */
/*VARARGS*/
void error(
  int   severity,
  char *fmt,
  ...)
{
va_list args;
static struct mesgstr {
	char *bgn_color;
	char *message;
	char *end_color;
	int  flags;
	} mesg[]={
	{XRED,    "severe error",XGREEN,TERMINATE},				/* XTDIO_SEVERE		*/
	{XRED,    "error",       XGREEN,TERMINATE},				/* XTDIO_ERROR		*/
	{XYELLOW, "warning",     XGREEN,0},						/* XTDIO_WARNING		*/
	{XCYAN,   "note",        XGREEN,0},						/* XTDIO_NOTE			*/
	{XCYAN,   "usage",       XGREEN,0},						/* XTDIO_USAGE		*/
	{XYELLOW, "   \"   ",    XGREEN,0},						/* XTDIO_ERRORMORE	*/
	{XCYAN,   " \"  ",       XGREEN,0},						/* XTDIO_ERRORMORE	*/
	{XCYAN,   " \"  ",       XGREEN,0}						/* XTDIO_ERRORMORE	*/
	};
static int nmesg     = sizeof(mesg)/sizeof(struct mesgstr);
static int errormore = 0;

if(!errfp) errfp= stderr;

/* severity sanity check and setting up of errormore */
if     (severity < 0 || severity >= nmesg) severity= XTDIO_SEVERE;
else if(severity == XTDIO_ERRORMORE)             severity= errormore;

#ifdef vms
if(errfp != stdout) fflush(stdout);
#endif

rdcputs(mesg[severity].bgn_color,errfp);
fprintf(errfp,"***%s*** ",mesg[severity].message);
rdcputs(mesg[severity].end_color,errfp);

if     (severity == XTDIO_WARNING)  errormore= XTDIO_ERRORMORE;
else if(severity == XTDIO_NOTE)     errormore= XTDIO_ERRORMORE + 1;
else if(severity == XTDIO_USAGE)    errormore= XTDIO_ERRORMORE + 2;
else if(severity < XTDIO_ERRORMORE) errormore= 0;

/* initialize for variable arglist handling */
va_start(args,fmt);
vfprintf(errfp,fmt,args);


va_end(args);

/* terminate */
if(mesg[severity].flags & TERMINATE) (*error_exit)(1);
}

/* ========================================================================
 * Debug Code:
 */

/* --------------------------------------------------------------------- */

