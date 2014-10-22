/* srmtrblk.c:
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */ 
#include <stdio.h>
#include <ctype.h>

/* --------------------------------------------------------------------- */

/* srmtrblk: remove trailing blanks from string s
 *  Returns pointer to last non-null character or
 *  NULL pointer if none
 */
char *srmtrblk(char *s)
{
char *ss;

for(ss= s; *ss; ++ss);	/* find end of string */
for(--ss; ss >= s && isspace(*ss) && *ss != '\f'; --ss) *ss= '\0';

return ss? ss : NULL;
}

/* --------------------------------------------------------------------- */
