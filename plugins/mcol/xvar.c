/* xvar.c: this file contains settings, flags, etc for the xtdio library
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#include <stdio.h>
#include "xtdio.h"

#if defined(MSDOS) || defined(__BORLANDC__)
# define msdos
#endif

/* ---------------------------------------------------------------------
 * Rdcolor support:
 */
int   screenheight      = 25;		/* rows    on the screen						*/
int   screenwidth       = 80;		/* columns in a line available to matout		*/
int   use_escapes       = 1;		/* (don't) use ANSI escape sequences			*/

/* ---------------------------------------------------------------------
* Outofmem and Error Support
*/
#ifdef __PROTOTYPE__
void exit(int);
void (*error_exit)(int) = exit;
#else
void (*error_exit)()    = exit;
#endif
FILE *errfp             = NULL;

/* ---------------------------------------------------------------------
* Rdcolor support
*/
char *BLACK             = "";
char *RED               = "";
char *GREEN             = "";
char *YELLOW            = "";
char *BLUE              = "";
char *MAGENTA           = "";
char *CYAN              = "";
char *WHITE             = "";

/* since some systems just have to use BLACK, ..., WHITE for themselves... */
char *RD_BLACK          = "";
char *RD_RED            = "";
char *RD_GREEN          = "";
char *RD_YELLOW         = "";
char *RD_BLUE           = "";
char *RD_MAGENTA        = "";
char *RD_CYAN           = "";
char *RD_WHITE          = "";
char *RD_CLEAR          = "";

char *UBLACK            = "";
char *URED              = "";
char *UGREEN            = "";
char *UYELLOW           = "";
char *UBLUE             = "";
char *UMAGENTA          = "";
char *UCYAN             = "";
char *UWHITE            = "";

char *RVBLACK           = "";
char *RVRED             = "";
char *RVGREEN           = "";
char *RVYELLOW          = "";
char *RVBLUE            = "";
char *RVMAGENTA         = "";
char *RVCYAN            = "";
char *RVWHITE           = "";

char *ITBLACK           = "";
char *ITRED             = "";
char *ITGREEN           = "";
char *ITYELLOW          = "";
char *ITBLUE            = "";
char *ITMAGENTA         = "";
char *ITCYAN            = "";
char *ITWHITE           = "";

char *BOLDBLACK         = "";
char *BOLDRED           = "";
char *BOLDGREEN         = "";
char *BOLDYELLOW        = "";
char *BOLDBLUE          = "";
char *BOLDMAGENTA       = "";
char *BOLDCYAN          = "";
char *BOLDWHITE         = "";

char *CLEAR             = "";
char *BOLD              = "";
char *NRML              = "";

char *PYELLOW           = "";
char *PRED              = "";
char *PCYAN             = "";
char *PBLACK            = "";

/* ---------------------------------------------------------------------
* Getarg support:
*/
GA_Codes ga_codes[]     = {
/*	 fmt   d x o f								*/
	{"%d", 1,0,0,0},	/* GA_BOOLEAN    : 0	*/
	{"%c", 0,0,0,0},	/* GA_CHAR       : 1	*/
	{"%lf",0,0,0,1},	/* GA_DOUBLE     : 2	*/
	{"%f", 0,0,0,1},	/* GA_FLOAT      : 3	*/
	{"%x", 0,1,0,0},	/* GA_HEX        : 4	*/
	{"%d", 1,0,0,0},	/* GA_INT        : 5	*/
	{"??", 0,0,0,0},	/* GA_LINE       : 6	*/
	{"%d", 1,0,0,0},	/* GA_LOGICAL    : 7	*/
	{"%ld",1,0,0,0},	/* GA_LONG       : 8	*/
	{"%lx",0,1,0,0},	/* GA_LONGHEX    : 9	*/
	{"%lo",0,0,1,0},	/* GA_LONGOCTAL  : 10	*/
	{"%o", 0,0,1,0},	/* GA_OCTAL      : 11	*/
	{"%hx",0,1,0,0},	/* GA_SHORTHEX   : 12	*/
	{"%ho",0,0,1,0},	/* GA_SHORTOCTAL : 13	*/
	{"%s", 0,0,0,0},	/* GA_STRING     : 14	*/
	{"??", 0,0,0,0},	/* GA_STRUCT     : 15	*/
	{"%x", 0,1,0,0},	/* GA_UCHAR      : 16	*/
	{"%u", 1,0,0,0},	/* GA_UINT       : 17	*/
	{"%lu",1,0,0,0},	/* GA_ULONG      : 18	*/
	{"%hu",1,0,0,0}		/* GA_USHORT     : 19	*/
	};

/* --------------------------------------------------------------------- */
