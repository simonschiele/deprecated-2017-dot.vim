/* strprintf.c: this function acts like a member of the printf family,
 *  except that it produces its output onto an internal buffer
 *  and returns a pointer to it.
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#include <stdio.h>
#include "xtdio.h"

/* ----------------------------------------------------------------------
 * Definitions:
 */
#define BUFSIZE 256

/* ---------------------------------------------------------------------- */

/* strprintf: */
char *strprintf(char *fmt,...)
{
va_list        args;
size_t         flen;
static char   *buf1 = NULL;
static char   *buf2 = NULL;
static char   *buf3 = NULL;
static char   *buf4 = NULL;
static char  **buf  = &buf1;
static size_t *len = NULL;
static size_t  len1 = 0;
static size_t  len2 = 0;
static size_t  len3 = 0;
static size_t  len4 = 0;

/* return old buffer when format is null pointer */
if(!fmt) return *buf;

/* get new buffer */
if     (*buf == buf1) buf= &buf2, len= &len2;
else if(*buf == buf2) buf= &buf3, len= &len3;
else if(*buf == buf3) buf= &buf4, len= &len4;
else                  buf= &buf1, len= &len1;

/* automatic buffer (re-)allocation */
flen= strlen(fmt);
if(flen + BUFSIZE > *len) {
	*len= flen + BUFSIZE;
	if(!*buf) *buf= (char *) malloc(*len);
	else      *buf= realloc(*buf,*len);
	}

va_start(args,fmt);
vsprintf(*buf,fmt,args);
va_end(args);

return *buf;
}

/* ===================================================================== */
/* ===================================================================== */
