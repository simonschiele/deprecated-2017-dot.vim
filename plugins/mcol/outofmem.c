/* outofmem.c
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#include <stdio.h>
#include "xtdio.h"

/* ---------------------------------------------------------------------- */

/* outofmem: tests if ptr is null.  If it is, the format and arguments
 * a la printf are put to the stdout and then the program exits
 */
void outofmem(void *ptr,char *fmt,...)
{
va_list args;

/* check if ptr is not null */
if(ptr) return;

/* initialize for variable arglist handling */
va_start(args,fmt);
fprintf(stderr,"***out of memory*** ");
vfprintf(stderr,fmt,args);
va_end(args);

(*error_exit)(1);
}

/* ---------------------------------------------------------------------- */
