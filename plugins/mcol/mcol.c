/* mcol: this function is a filter which takes a list of words and produces
 *  a multi-column-ized list.  It uses the xtdio.a library's multicol
 *  function.
 *
 *  Author:  Dr. Charles E. Campbell, Jr.
 *  Date:    Oct 13, 2006
 *
 *  Modification History: {{{1
 *    v2   : 01/28/05    included folding in source
 *    v1.03: 10/ 3/2000  fixed lcol,rcol swap bug
 *    v1.02:  7/29/1997  implemented -b, removed -S
 *                       implemented -c
 */
/* Header Files: {{{1 */
#include <stdio.h>
#include <ctype.h>
#include "xtdio.h"

/* -----------------------------------------------------------------------
 * Local Definitions: {{{2
 */
#define BUFSIZE 256
/* #define RENDER_TEST */

/* -----------------------------------------------------------------------
 * Global Data: {{{2
 */
static char *bflag= NULL;		/* separate based on this break character	*/
static int   tflag= 1;		    /* control multicol_transpose               */

/* -----------------------------------------------------------------------
 * Prototypes: {{{2
 */
int main(int,char **);                            /* mcol.c */
int options(char **,char **);                     /* mcol.c */
void fprior(int,PARMDEF *);                       /* mcol.c */
void mcol(char *);                                /* mcol.c */

#ifdef RENDER_TEST
void rendertst(char *,int);
#endif

/* -----------------------------------------------------------------------
 * Data Structure Definitions: {{{2
 */
typedef struct Word_str Word;
struct Word_str {
	char *word;
	Word *nxt,*prv;
	};

/* -----------------------------------------------------------------------
 * Global Information: {{{2
 */
Word        *whd     = NULL;
Word        *wtl     = NULL;
static char *usage[] = {
	XYELLOW,"mcol",
	XCYAN," [",
	XGREEN,"-n#",XCYAN,"|",XGREEN,"-w#",XCYAN,"] [",
	XGREEN,"-%fmt",
	XCYAN,"] [",XGREEN,"files",XCYAN,"]\n",

	XCYAN,"\nOptions:\n",
	XCYAN," -b   ",XGREEN,": separate words based on whitespace\n",
	XCYAN," -b...",XGREEN,": separate words based on string\n",
	XCYAN," -n#  ",XGREEN,": number of columns\n",
	XCYAN," -w#  ",XGREEN,": max width of output (in characters)\n",
	XCYAN," -s#  ",XGREEN,": set screenwidth columns\n",
	XCYAN," -t   ",XGREEN,": toggle table transpose\n",
	XCYAN," -%   ",XGREEN,": C format specifier\n",

	XCYAN,"\nExplanation:\n",XGREEN,
	"  Produces multicolumn listings of input words\n",

	"\n",XWHITE,"Author",XGREEN,"   : Dr. Charles E. Campbell, Jr.\n",
	     XWHITE,"Version",XGREEN,"  : 1.03\n",
	     XWHITE,"Copyright",XGREEN,": 1999,2000,2001  Charles E. Campbell, Jr.\n",
	"",""};
char *fmt     = " ";
char *section = NULL;
int ncol      = 0;
int lcol      = -1;
int rcol      = -1;

/* -----------------------------------------------------------------------
 * Source Code: {{{1
 */

/* main: begin here {{{2 */
int main(
  int    argc,
  char **argv)
{
char **table   = NULL;
int    i;
int    ntable;
Word  *w       = NULL;

rdcolor();					/* get color sequences initialized	*/

#ifdef RENDER_TEST
multicol_render= rendertst;
#endif

/* process command line */
getarg(argc,argv,0,(PARMDEF *) NULL,usage,options,fprior,mcol,1,(char *) NULL);

/* allocate a table */
for(w= whd, ntable= 0; w; w= w->nxt, ++ntable) ;
table= (char **) calloc((size_t) ntable,sizeof(char *));
if(!table) error(XTDIO_ERROR,"unable to allocate %d table entries\n",ntable);

/* initialize table */
for(w= whd, i= 0; w; w= w->nxt, ++i) table[i]= w->word;

/* perform multi-column listing of words */
multicol(ncol,table,ntable,fmt,stdout);

return 0;
}

/* ----------------------------------------------------------------------- */

/* options: this function processes all options {{{2 */
int options(
  char **s,
  char **a)
{
int ret= 0;


switch(**s) {

case 'b':	/* -b -or- -b_ : break up line based on whitespace/specified character	*/
	if(s[0][1]) {
		bflag= s[0] + 1;
		ret  = -1;
		}
	else bflag= " \t";
	break;

case 'c':	/* -c#  -c,#  -c#,# : restrict mcol action to specified columns */
	if(isdigit(s[0][1])) {
		char *comma;
		comma= strchr(s[0]+1,',');

		if(comma && isdigit(s[0][1])) { /* -c#,# */
			sscanf(s[0]+1,"%d,%d",&lcol,&rcol);

			/* sanity maintenance */
			if(lcol < 0 || rcol < 0) lcol= rcol= -1;
			else if(rcol < lcol) {	/* swap 'em */
				int swap;
				swap= lcol;
				lcol= rcol;
				rcol= swap;
				}
			}

		else { /* -c# */
			sscanf(s[0]+1,"%d",&lcol);
			if(rcol < 0) lcol= rcol= -1;
			else         rcol= 0;
			}
		}

	/* -c,# */
	else if(s[0][1] == ',' && isdigit(s[0][2])) {
		sscanf(s[0] + 2,"%d",&rcol);
		if(rcol < 0) lcol= rcol= -1;
		else         lcol= 1;
		}
	++lcol; ++rcol;	/* assuming first column is column 0 */
	ret= -1;
	break;

case 'f':
	fmt= *s+1;
	while(**s) ++*s;
	--*s;
	if(s[0][1] == '%') {
		fmt= s[0] + 1;
		ret= -1;
		}
	else if(s[1][0] == '%') {
		fmt= a[1];
		ret= 1;
		}
	else error(XTDIO_WARNING,"missing format specifier\n");
	break;

case 'n':
	if(isdigit(s[0][1])) {
		sscanf(s[0]+1,"%d",&ncol);
		ret= -1;
		}
	else {
		sscanf(a[1],"%d",&ncol);
		ret= 1;
		}
	break;

case 's':	/* -s# : reset screenwidth */
	if(isdigit(s[0][1])) {
		sscanf(s[0]+1,"%d",&screenwidth);
		ret= -1;
		}
	else {
		sscanf(a[1],"%d",&screenwidth);
		ret= 1;
		}
	break;

case 't':
	tflag= !tflag;
	break;

case 'w':
	if(isdigit(s[0][1])) {
		sscanf(s[0]+1,"%d",&multicol_len);
		ret= -1;
		}
	else {
		sscanf(a[1],"%d",&multicol_len);
		ret= 1;
		}
	break;

default:
	error(XTDIO_WARNING,"unimplemented option <%c>\n",**s);
	break;
	}

return ret;
}

/* ----------------------------------------------------------------------- */

/* fprior: this function executes before any files are processed with mcol() {{{2 */
void fprior(int parmqty,PARMDEF *parms)
{

multicol_len       = screenwidth; /* initialize default output length           */
multicol_transpose = tflag;       /* control whether table is transposed or not */

}

/* --------------------------------------------------------------------- */

/* mcol: constructs a linked list of WordS {{{2 */
void mcol(char *filename)
{
char *b             = NULL;
char  buf[BUFSIZE];
FILE *fp            = NULL;


/* open file */
if(!strcmp(filename,"stdin")) fp= stdin;
else {
	fp= fopen(filename,"r");
	if(!fp) {
		error(XTDIO_WARNING,"unable to read file <%s>\n",filename);
		return;
		}
	}

/* read in words */
while(fgets(buf,BUFSIZE,fp)) {

	/* remove columns based on -c */
	if(lcol > 0) {
		int rightcol= rcol;
		if(rcol < 0) rightcol= strlen(buf) - 1;
		if(!section) {
			section= (char *) calloc((size_t) rightcol - lcol + 2,sizeof(char));
			strncpy(section,buf + lcol - 1,rightcol - lcol + 1);
			section[rightcol - lcol + 1]= '\0';
			}
		memcpy(buf + lcol - 1,buf + rightcol,strlen(buf) + 1 - (rightcol - lcol + 1));
		multicol_section    = section;
		multicol_sectioncol = lcol;
		}

	/* remove leading and trailing blanks from word */
	srmtrblk(buf);
	b= stpblk(buf);
	if(!*b) continue;

	/* break up string based on given -b flag */
	if(bflag) {
		char *word;
		for(word= strtok(b,bflag); word; word= strtok((char *) NULL,bflag)) {
			/* Allocate, link,and initialize a Word:
			 * allocate a string in the Word and copy buffer into it
			 */
			double_link(Word,whd,wtl,"out of memory while allocating a Word\n");
			stralloc(wtl->word,word,"while allocating a word\n");
			}
		}

	else {
		/* Allocate, link,and initialize a Word:
		 * allocate a string in the Word and copy buffer into it
		 */
		double_link(Word,whd,wtl,"out of memory while allocating a Word\n");
		stralloc(wtl->word,b,"while allocating a word\n");
		}
	}

/* close file */
if(fp != stdin) fclose(fp);

}

/* ----------------------------------------------------------------------- */
/* rendertst: {{{2 */
#ifdef RENDER_TEST
void rendertst(char *entry,int bgn)
{

}
#endif

/* --------------------------------------------------------------------- */
/* vim: ts=4 fdm=marker
 */
