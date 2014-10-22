/* pstrlen.c: returns lengthof string as printed on a terminal
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#include <stdio.h>
#include <ctype.h>
#include "xtdio.h"

int tabshift=8;	/* corresponds to tabstops every 8th character */

/* ----------------------------------------------------------------------- */

/* pstrlen: this function returns the length of the string as it will appear
 *  on a terminal.  Note that tabs are assumed to be expanded to the (next)
 *  8'th character and that <ESC>...[alphabetic character] sequences are
 *  ignored.  The first column is column=0.
 */
int pstrlen(int column,char *s)
{
int cnt;


/* take care of null pointer or 0-length string real quick */
if(!s || !*s) {
	return column;
	}

for(cnt= column; *s; ++s) {
	if(*s == '\t') {
		cnt/= tabshift;
		cnt = (cnt + 1)*tabshift;
		}
	else if(*s == '\033') { /* skip over ansi escape sequences */
		while(*s && !isalpha(*s)) ++s;
		if(!*s) break;
		}
	else ++cnt;
	}

return cnt;
}

/* --------------------------------------------------------------------- */


/* --------------------------------------------------------------------- */
