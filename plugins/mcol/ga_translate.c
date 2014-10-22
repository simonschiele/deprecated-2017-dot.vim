/* ga_translate.c: ga_translate handles translation of GetArg types
 * into memory
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#include <stdio.h>
#include <ctype.h>
#include "xtdio.h"

/* --------------------------------------------------------------------- */

/* ga_translate: translates GA_INT and string into a memory location
 *  Returns 0: ok
 *          1: couldn't translate
 */
int ga_translate(
  void *ptr,
  int   type,
  char *src)
{
int ok;
int iuchar;


/* sanity check */
ok= 0;
if(ga_codes[type].floating) {
	if(isdigit(*src) || *src == '.' || *src == '-' || *src == '+') ok= 1;
	else error(XTDIO_WARNING,"ga_translate: src<%s> not floating-point\n",sprt(src));
	}
else if(ga_codes[type].hex) {
	if(ishex(*src)) ok= 1;
	else error(XTDIO_WARNING,"ga_translate: src<%s> not hexadecimal\n",sprt(src));
	}
else if(ga_codes[type].oct) {
	if(isoct(*src)) ok= 1;
	else error(XTDIO_WARNING,"ga_translate: src<%s> not octal\n",sprt(src));
	}
else if(ga_codes[type].decimal) {
	if(isdigit(*src) || *src == '-' || *src == '+') ok= 1;
	else error(XTDIO_WARNING,"ga_translate: src<%s> not decimal\n",sprt(src));
	}
else ok= 1;

if(ok) switch(type) {

case GA_LINE:	/* enter a whole line*/
	strcpy((char *) ptr,src);
	break;

case GA_STRUCT:	/* user-defined structure entry	*/
	((void (*)(char *)) ptr)(src);
	break;

case GA_UCHAR:
	sscanf((char *) src,"%x",&iuchar);
	*((unsigned char *) ptr)= iuchar;
	break;

default: /* usual format-using entry		*/
	sscanf((char *) src,ga_codes[type].fmt,ptr);
	break;
	}

return !ok;
}

/* --------------------------------------------------------------------- */
