/* stpblk:
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#include <stdio.h>
#include <ctype.h>

/* --------------------------------------------------------------------- */
  
/* stpblk: skips blanks (white space) */
char *stpblk(char *p) 
{
while(isspace(*p)) ++p;
return p;
}

/* --------------------------------------------------------------------- */
