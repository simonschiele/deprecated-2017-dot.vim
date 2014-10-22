/* multicol.c: prints out multiple columns of data
 *
 *  External Variable Modifiers:
 *  int   multicol_len         length of screen
 *  char *multicol_leader      leader string used for all lines
 *  char *multicol_oneleader   leader string first line, subsequent ones are blank
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "xtdio.h"
#ifdef __WIN32__
# include <io.h>
#else
# include <unistd.h>
#endif

#ifdef MCH_AMIGA
# include <fcntl.h>
#endif

#if defined(MSDOS) || defined(__BORLANDC__)
# define msdos
#endif

#ifdef msdos
# include <io.h>
#endif

/* -------------------------------------------------------------------------
 * Definitions:
 */
#define FMTSIZE			128
#define MULTICOL_LEN	80	/* default window width for multicol */

/* -------------------------------------------------------------------------
 * Global Data:
 *
 * The global multicol_xxx variables below may be used to modify the multicol
 * function behavior.
 *
 *  char *multicol_render(char *table_entry,int itable):
 *      If itable >= 0, it will be called to return a string which will
 *      precede the printing of the table entry.  When itable < 0,
 *      it returns a string to "restore" the table entry.
 */
char  multicol_moreflag              = 0;		/* have multicol pause every screenheight-1 lines	*/
char *multicol_leader                = NULL;	/* print out before every line						*/
char *multicol_oneleader             = NULL;	/* print out before 1st line, blanks after			*/
char *multicol_section               = NULL;	/* allow a section of text to be unaltered			*/
int   multicol_len                   = -1;		/* maximum width of multicolumn output				*/
int   multicol_sectioncol            = -1;		/* begin output of section at/after this column		*/
int   multicol_transpose             =  1;      /* column/row oriented table                        */
#ifdef __PROTOTYPE__
char *(*multicol_render)(char *,int) = NULL;	/* ptr to func ret ptr to char		*/
#else
char *(*multicol_render)()           = NULL;
#endif

/* -------------------------------------------------------------------------
 * Source Code:
 */

/* multicol: this routine prints out multiple columns of data
 * ncol  :  #columns of output (<=0: determined by multicol)
 * table :  list of strings to be multi-column'ed
 * ntable:  number of strings in table
 * fmt   :  column separation string (don't use %...)
 * fp    :  output goes to this file
 *
 *  Returns: the number of lines printed
 */
int multicol(
  int    ncol,
  char **table,
  int    ntable,
  char  *fmt,
  FILE  *fp)
{
char   *lb;
char    locbuf[FMTSIZE];
char    impfmt[FMTSIZE];		/* implied format (from tmpmaxlen and strings)	*/
char    nosepfmt[FMTSIZE];		/* no separation format: used for last column	*/
char   *f         = NULL;
char   *leader    = NULL;
char ***maxtbl    = NULL;
char ***tbl       = NULL;
char  **ptbl      = NULL;
int     big       = 0;
int     col       = 0;
int     didwork   = 0;
int     i         = 0;
int     itbl      = 0;
int     leaderlen = 0;
int     len       = 0;
int     plen      = 0;
int     rem       = 0;
int     row       = 0;
int     tmpmaxlen = multicol_len;	/* max printable length of output	*/


/* stupidity check - no columns requested! */
if(ntable <= 0) {
	return 0;
	}

/* if multicol_len < 0: check out environment variable SCREENWIDTH or COLUMNS */
if(multicol_len < 0) {
	char *mcol_env= NULL;

	multicol_len  = MULTICOL_LEN;
	mcol_env      = getenv("SCREENWIDTH");
	if(!mcol_env) mcol_env= getenv("COLUMNS");
	if     (!mcol_env && screenwidth > 0) multicol_len= screenwidth;
	else if( mcol_env && mcol_env[0]) sscanf(mcol_env, "%d",&multicol_len);

	tmpmaxlen     = multicol_len;
	}

/* handle optional multicol_leader / multicol_oneleader
 *  The multicol_oneleader takes precedence
 */
if(multicol_oneleader) {
	leaderlen= pstrlen(0,multicol_oneleader);
	if(leaderlen < 0) {
		return 0;
		}

	leader= (char *) calloc((size_t) leaderlen+1,sizeof(char));
	if(!leader) {
		error(XTDIO_WARNING,"unable to allocate a %d byte leader\n",leaderlen+1);
		return 0;
		}

	for(i= 0; i < leaderlen; ++i) leader[i]= ' ';
	leader[i]= '\0';
	}

else if(multicol_leader) {
	leader   = multicol_leader;
	leaderlen= pstrlen(0,multicol_leader);
	}

else leader= NULL;

/* account for reduction in column width available to print entries */
tmpmaxlen-= leaderlen;
if(tmpmaxlen <= 0) {
	if(multicol_oneleader) {
		if(leader) free(leader);
		multicol_leader= NULL;
		}
	return 0;
	}

/* figure out a fmt code to use */
if(ncol <= 0) {
	int ltbl0;
	int ptbl0;
	int pfmt;


	/* plen is non-zero only when escape codes are used or tabs in the table
	 * Such codes must be present in each table entry for multicol to handle
	 * the table correctly.  Otherwise, different format statements for each
	 * table entry would be required.
	 */
	ltbl0= strlen(table[0]);
	ptbl0= pstrlen(0,table[0]);
	plen = ltbl0 - ptbl0;


	/* look for biggest (longest) printable string in table */
	for(big= i= 0; i < ntable; ++i) {
		len= pstrlen(0,table[i]);
		if(len > big) big= len;
		}
	pfmt= pstrlen(0,fmt);
	ncol= (tmpmaxlen + pfmt)/(big + pfmt);
	if(ncol <= 0) ncol= 1;	/* user probably chose/has screenwidth set too small for given words */

	sprintf(impfmt,"%%-%ds%s",big + plen,fmt? fmt : "");
	sprintf(nosepfmt,"%%-%ds",big + plen);
	fmt= impfmt;
	}
else {
	nosepfmt[0]= '\0';
	f          = (char *) strchr(fmt,'%');

	if(!f) { /* must compute an implied format using ncol */
		plen= pstrlen(0,fmt);
		big = (tmpmaxlen - plen*(ncol-1))/ncol;
		sprintf(impfmt,"%%-%ds%s",big,fmt? fmt : "");
		sprintf(nosepfmt,"%%-%ds",big);
		fmt= impfmt;
		}
	}


/* itbl is qty of entries per column for the last ncol - rem columns.
 * The first "rem" columns have "itbl+1" entries
 */
itbl= ntable/ncol;
rem = ntable % ncol;	/* remainder of ntable/ncol */

if(multicol_transpose) {
	/* allocate temporary memory for table pointers */
	tbl   = (char ***) calloc((size_t) ncol,sizeof(char **));
	outofmem((char *) tbl,"multicol tbl");
	maxtbl= (char ***) calloc((size_t) ncol,sizeof(char **));
	outofmem((char *) maxtbl,"multicol maxtbl");

	/* set up pointers to the top of each column in the table */
	for(i= 1, tbl[0]= table; i < ncol; ++i) {
		tbl[i]= tbl[i-1] + itbl;
		if(rem) {
			++tbl[i];
			--rem;
			}
		maxtbl[i-1]= tbl[i];
		}
	maxtbl[ncol - 1]= table + ntable;
	}
else ptbl= table;

/* print out the table */
row  = 1;
col  = 0;
ptbl = table;
do {
	didwork= 0;
	for(i= 0; i < ncol; ++i) {
		if(multicol_transpose) {
			ptbl= tbl[i];
			if(ptbl >= maxtbl[i]) continue;
			}
		else if(ptbl >= table+ntable) break;

		if(!didwork && leader) {
			if(row == 1 && multicol_oneleader) fputs(multicol_oneleader,fp);
			else                               fputs(leader,fp);
			}

		if(multicol_render) {
			char *lbend;
			int   lblen;
			fputs((*multicol_render)(*ptbl,(ptbl - table)),fp);
			sprintf(locbuf,(i == ncol-1 && nosepfmt[0])? nosepfmt : (fmt? fmt : "%s"),*ptbl);
			lblen= strlen(locbuf);
			lbend= locbuf + lblen;		/* points to terminating null byte */

			/* insert multicol_section if there is one */
			if(multicol_section && col >= 0) {
				col += lblen;
				sprintf(locbuf, (i == ncol-1 && nosepfmt[0])? nosepfmt : (fmt? fmt : "%s"), *ptbl);
				col+= strlen(locbuf);
				if(col >= multicol_sectioncol) fputs(multicol_section,fp);
				col= -1;
				}

			/* render just the non-whitespace */
			for(lb= lbend - 1; lb > locbuf; --lb) if(!isspace(*lb)) break;

			if(lb > locbuf && lb < lbend - 1) {	/* handle trailing blanks */
				++lb;
				*lb= '\0';
				fputs(locbuf,fp);
				fputs((*multicol_render)(*ptbl,-1),fp);
				*lb= ' ';
				fputs(lb,fp);
				}
			else {									/* no trailing blanks		*/
				fputs(locbuf,fp);
				fputs((*multicol_render)(*ptbl,-1),fp);
				}
			}

		else if(multicol_section && col >= 0) {
			sprintf(locbuf, (i == ncol-1 && nosepfmt[0])? nosepfmt : (fmt? fmt : "%s"), *ptbl);
			col+= strlen(locbuf);
			if(col >= multicol_sectioncol) fputs(multicol_section,fp);
			fputs(locbuf,fp);
			col= -1;
			}

		else fprintf(fp, (i == ncol-1 && nosepfmt[0])? nosepfmt : (fmt? fmt : "%s"), *ptbl);
		if(multicol_transpose) ++tbl[i];
		else                   ++ptbl;
		didwork= 1;
		}

	if(didwork) {
		fputs("\n",fp);
		++row;
		col= 0;
		if(multicol_moreflag && isatty(fileno(stdin)) && (row%(screenheight-1) == 0)) {
			printf("%s---More---%s",YELLOW,NRML);	/* allow user to examine listing before going on	*/
			fgetc(stdin);							/* pause until <CR>									*/
			printf("\033[A\033[K\033[A");			/* ansi escape sequence to remove "---More---" line	*/
			}
		}
	if(!multicol_transpose && ptbl >= table+ntable) break;
	} while(didwork);

/* free up the temporary storage space */
if(tbl)    free((char *) tbl);
if(maxtbl) free((char *) maxtbl);
if(multicol_oneleader && leader) free(leader);

/* adjust row -- it has one more than actually displayed */
if(row > 0) --row;

return row;
}

/* ===================================================================== */
/* ===================================================================== */
