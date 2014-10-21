/* getarg.c: contains functions which handle command line arguments and
 *  passing them along to programmer specified functions.
 *
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 *
 * I. Command Line Argument Processing
 *
 *  0) "?": If there is only one argument, and that argument is the string
 *     "?", then getarg() will print out the *usage[] string array and then
 *     exit.  The getarg() program will interpret XGREEN, etc. using the
 *     rdcputs() function for ansi escape strings controlling color,
 *     underlining, etc.  The *usage[] array should be terminated by *two*
 *     null strings: "",""}; (since some terminals will have "" as their
 *     `ansi escape sequences'.
 *
 *  1) Options are looked for (assuming that the options function
 *     is not NULL); they are assumed to begin with "-" or "+" followed
 *     by one or more alphabetic characters.
 *
 *       -options: are passed along, one character at a time, to
 *                 (*options)(char **s,char **a) prior to all other actions.
 *
 *       +options: are passed along, one character at a time, to
 *                 (*options)(char **s,char **a) interspersed with
 *               parameter processing and calls to (*dofile)(char *filename)
 *
 *     The (*options)() function may modify option strings via *s or *a,
 *     return a 0        : normal options processing (every letter),
 *     return a + integer: to skip that many subsequent arguments,
 *     return a - integer: to terminate the processing of the current argument.
 *
 *  2) Parameters: the getarg program *requires* parameters to be acquired
 *     either from the command line arguments, or, if insufficient or of
 *     the wrong type, via prompts issued to the program user.
 *
 *     If parmqty is > 0, parameter processing ensues. The parms[] array is
 *     used to specify parameters.
 *
 *     Parameters may be entered on the command line via "parmname=value",
 *     or will be expected/prompted for in the sequence appearing in the
 *     PARMDEF list.
 *
 *     Arguments past +| will *not* be examined for fulfilling parameter
 *     requirements (ie. will be treated only as filename(s)).  This means
 *     that a user can use +| to force getarg to treat subsequent arguments
 *     as filenames, and to satisfy its parameter needs by arguments preceding
 *     the +| *OR BY ISSUING PROMPTS FOR THEM*.
 *
 *  3) If fprior is not null, call (*fprior)(int parmqty,PARMDEF *parms)
 *     prior to processing remaining arguments.
 *
 *  4) Finally, all those entries on the command line not used as
 *     an option (1) or in parameter definition (2) are then passed
 *     to (*dofile)(filename), also supplied by the user (if not NULL),
 *     one at a time (assuming dofile is not NULL).
 *
 *     If no arguments are left by (1) and (2), and there's a fprompt,
 *     then if the stdin is a terminal (ie. not a pipe or redirected
 *     file) then a prompt will be given (for those systems which support
 *     the isatty() function) and the user can enter by hand any files.
 *     If wild is true, those files will be interpreted for wildcards.
 *
 *  Note: for vms, getarg also supports: wildcards, > < >> i/o redirection
 *     and appending, and & for self-spawning.
 *
 *
 * II. Getarg Function Variables
 *
 *	argc   : count of arguments on command line
 *	argv   : list of strings from command line
 *	parmqty: quantity of command line parameters
 *	parms  : PARMDEF-type description of command line parameters
 *	usage  : list of strings describing usage of program (NULL string
 *	         terminates the list)
 *	dofile : the function to be called with "filename" strings.  This function
 *	         will receive filenames one at a time.  It must be able to handle
 *	         "stdin" as a no-filenames-present indicator (often means read
 *	         stdin).
 *	options: the function to be called with option characters
 *	wild   : if true, then "filename" arguments are checked first
 *	         for wildcard characters (?*); matching filenames
 *	         from the user's directory are passed to (*dofile)().
 *	fprompt: this is a pointer to a string to be used for a prompt often of
 *	         the style:
 *                 "Enter Filename(s): "
 *
 *	         If    fprompt is null -or- fprompt[0] is '\0':
 *	         or    ga_prompts != parmqty (ie. not all prompts given),
 *           or    (on some systems) if stdin is not a terminal,
 *	         then  no "fprompt" will be issued.  getarg will
 *	               then call (*dofile)("stdin")
 *
 *           Otherwise, if no filename(s) appear on the command line,
 *	         then fprompt will be given and the resulting string parsed for
 *	         substrings separated by white space and passed one at a time to
 *
 *	         (*dofile)(char *filename)    -- (if no wildcards or wild == 0)
 *           (ga_dofilewild)(char *files) -- wildcards present and wild == 1
 *
 *	         The latter function will expand the wildcards and pass the
 *	         resulting files, one at a time, to (*dofile)(char *filename).
 *
 *
 * III. Routines Included:
 *
 *    void getarg( int argc,  char **argv,  int parmqty,  PARMDEF *parms,
 *        char **usage,  int (*options)(char **,char **),
 *        void (*fprior)(int,PARMDEF *),  void (*dofile)(char *),  int wild,
 *        char *fprompt)
 *    void ga_dofilewild( void (*dofile)(), char *filespec)
 *    int ga_haswild(char *fspec)
 *
 * vms only:
 *    int spawn( int argc, char **argv)
 *
 *
 * IV. Parameters
 *
 * Parameters are described as a PARMDEF:
 *
 *		typedef struct {
 *		    void *p;            // a "generic" pointer to the parameter
 *		    int   type;         // an integer indicating type of parameter
 *		    int  *skip_option;  // ptr to parameter can cause skip of parameter
 *		    char *prompt;       // promptstring to show user for variable entry
 *		    } PARMDEF;
 *
 * Parameter Types are:
 *
 *		GA_CHAR     0	// p points to a  char   (use %c)
 *		GA_STRING   1	// p points to a  char * (use %s)
 *		GA_LINE     2	// p points to a  char * (use %s from arg, fgets prompt)
 *		GA_INT      3	// p points to an int    (use %d)
 *		GA_BOOLEAN  3	// p points to an int    (use %d)
 *		GA_LOGICAL  3	// p points to an int    (use %d)
 *		GA_LONG     4	// p points to a  long   (use %ld)
 *		GA_FLOAT    5	// p points to a  float  (use %f)
 *		GA_DOUBLE   6	// p points to a  double (use %lf)
 *		GA_OCTAL    7	// p points to an int    (use %o)
 *		GA_HEX      8	// p points to an int    (use %x)
 *		GA_STRUCT	9	// p points to user-specified data structure parser (*)
 *		GA_UCHAR	10	// p points to unsigned char
 *		GA_USHORT	11	// p points to unsigned short
 *		GA_UINT		12	// p points to unsigned int
 *		GA_ULONG	13	// p points to unsigned long
 *
 *		(*) In the case of a GA_STRUCT, the p points to a user-specified
 *		    function which translates a line into a user-supplied data structure.
 *
 * V. Global Parameters and Variables
 *
 *  The getarg() function will set up the following globally accessable
 *  variables for subsequent programmer's use:
 *
 *		int    ga_filenames		// qty args which are filenames
 *		int    ga_fprompt		// yes/no: filename prompt issued
 *		int    ga_options		// qty args processed as options
 *		int    ga_prompts		// qty parm prompts issued
 *		int   *ga_skip			// skip arg vector
 *		int    ga_getargc		// qty filenames in ga_getargv
 *		char **ga_getargv		// filename list (ie. not parameter, option)
 */
#include <stdio.h>
#include <ctype.h>
#include "xtdio.h"
#ifdef AZTEC_C
# include <fcntl.h>
#endif
#ifdef unix
# ifdef sgi
#  include <sys/time.h>
#  include <sys/uio.h>
# endif
# include <unistd.h>
#endif
#ifdef __WIN32__
# include <io.h>
#endif

#ifdef USE_JMALLOC
# define JMALLOC_PRETEND
# include "jmalloc.h"
#endif

/* -------------------------------------------------------------------------
 * Definitions:
 */
#ifdef vms
#define BUFSIZE 	512
#else
#define BUFSIZE 	256
#endif
#define FNAMESIZE	65

/* -------------------------------------------------------------------------
 * Prototypes:
 */
#ifdef __PROTOTYPE__

static int ga_optionhandler(char,int,char **,          /* getarg.c        */
   int (*)(char **,char **),int *);
static void ga_dofile_record( void (*)(char *),        /* getarg.c        */
   char *);
static void ga_parmhandler(int,char **,int,PARMDEF *); /* getarg.c        */

#ifdef TIPRO
static int ga_hasdirspec(char *);                      /* getarg.c        */
#endif

#ifdef vms
static int ga_hasext(char *);                          /* getarg.c        */
static int ga_hasfname(char *);                        /* getarg.c        */
static int ga_hasvn(char *);                           /* getarg.c        */
static int ga_hasdirspec(char *);                      /* getarg.c        */
int ga_findfirst( char *, char **);                    /* getarg.c        */
int ga_findnext(char **);                              /* getarg.c        */
#endif

#else

static int ga_optionhandler();                         /* getarg.c        */
static void ga_parmhandler();                          /* getarg.c        */
static void ga_dofile_record();                        /* getarg.c        */

#ifdef TIPRO
static int ga_hasdirspec();                            /* getarg.c        */
#endif

#ifdef vms
static int ga_hasext();                                /* getarg.c        */
static int ga_hasfname();                              /* getarg.c        */
static int ga_hasvn();                                 /* getarg.c        */
int ga_findfirst();                                    /* getarg.c        */
int ga_findnext();                                     /* getarg.c        */
#endif

#endif

/* -------------------------------------------------------------------------
 * System Dependencies
 */
#ifdef LATTICE
# include "reg.h"
# include "dta.h"
# include "mydos.h"
# define TIPRO
#endif

#ifdef DESMET
# include "reg.h"
# include "dta.h"
# include "mydos.h"
# define  TIPRO
#endif

#ifdef MSC	/* microsoft C */
# include <dos.h>
# include <dta.h>
#endif

#ifdef __WIN32__	/* borland c */
# include <dos.h>
int findfirst(const char *,struct ffblk *,int);
int findnext(struct ffblk *);
#endif

#ifdef vms
# define GOODEXIT 1
# define BADEXIT  0
#else
# define GOODEXIT 0
# define BADEXIT  1
#endif

/* -------------------------------------------------------------------------
 * Global Parameters:
 *   ga_filenames: how many filenames were processed
 *   ga_fprompt  : whether a filename prompt was issued
 *   ga_getargc  : count of filenames processed by getarg
 *   ga_options  : how many options were present
 *   ga_prompts  : how many prompts were given
 *  *ga_skip     : indicates whether an argv[i] was skipped (ga_skip[i-1])
 * **ga_getargv  : list of filenames passed to dofile
 */
char **ga_getargv   = NULL;	/* filename list												*/
int    ga_dofile    = 1;	/* options can override this to prevent (*dofile) processing	*/
int    ga_filenames = 0;	/* qty args which are filenames									*/
int    ga_fprompt   = 0;	/* yes/no: filename prompt issued								*/
int    ga_getargc   = 0;	/* qty filenames in ga_getargv									*/
int    ga_options   = 0;	/* qty args processed as options								*/
int    ga_prompts   = 0;	/* qty parm prompts issued										*/
int    ga_stopprompt= 0;	/* 0=normal  1=options() wants to stop the issuance of a prompt	*/
int   *ga_skip      = NULL;	/* skip arg vector												*/

/* -------------------------------------------------------------------------
 * Local Parameters:
 */
static int gtaflag=0;

/* =========================================================================
 * Source Code:
 */

/* getarg:: the getarg function starts here... */
void getarg(
  int      argc,						/* count of cmd line arguments		*/
  char   **argv,						/* list of argument strings			*/
  int      parmqty,						/* qty of parameters				*/
  PARMDEF *parms,						/* parameter descriptions/prompts	*/
  char   **usage,						/* program usage explanation		*/
  int    (*options)(char **,char **),	/* user provided options processing	*/
  void   (*fprior)(int,PARMDEF *),		/* prior to filename processing		*/
  void   (*dofile)(char *),				/* execute dofile on each filename	*/
  int      wild,						/* use wildcard expansion for fprompt*/
  char    *fprompt)						/* no files -> emit fprompt			*/
{
char       **a        = NULL;
char        *f        = NULL;
static char  buf[BUFSIZE];
static char  fname[FNAMESIZE];	/* static so it won't take up stack */
int          explain;
int          hw;
int          i;
int          usestdin;
int          qty;

#ifdef vms
char        *filespec = NULL;
char        *s        = NULL;
static char *ioread   = "?";
static char *iowrite  = "?";
#endif


#ifdef vms
/* --- VMS SELF SPAWN --
 * look for a trailing "&" argument.  If present, spawn the job into
 * the background
 */
if(!strcmp("&",*(argv + argc - 1))) { /* trailing but separate "&"	*/
	spawn(argc-1,argv);	/* remove "&" from spawned process	*/
	exit(GOODEXIT);
	}
else {				/* search for & at end of last arg	*/
	for(s= *(argv + argc - 1); *s; ++s);
	if(*--s == '&') {	/* "&" tacked onto last argument	*/
		*s= '\0';	/* remove trailing "&" from last arg	*/
		spawn(argc,argv); /* spawn the modified arg list	*/
		exit(GOODEXIT);
		}
	}
#endif	/* vms */

/* --- INITIALIZE ---
 * omit handling of first argument (the program name) and indicate to
 * ga_dofile_record that getarg is in use
 */
--argc; ++argv;
gtaflag= 1;

/* initialize counts */
ga_options= ga_prompts= ga_filenames= ga_fprompt= 0;

/* skip vector: 1=> skip entry, 0=> use entry */
if(ga_skip) free((char *) ga_skip);
if(argc > 0) {
	ga_skip= (int *) calloc((size_t) argc,sizeof(int));
	outofmem(ga_skip,"getarg: allocating %d ints for ga_skip\n",argc);
	}
else ga_skip= NULL;
for(i= 0; i < argc; ++i) ga_skip[i]= 0;

#ifdef vms
/* --- VMS I/O REDIRECTION/APPENDING ---
 * pre-process (for stupid vms, of course) the command line and re-define
 * stdin and stdout if "<" or ">" are used.  Use append mode if >>
 * Note: only *one* redirection can take place for read  and
 *       only *one* redirection can take place for write!
 */
for(a= argv, i= 0; i < argc; ++i, ++a) {
	if(**a == '>' || **a == '<') {	/* re-direction					*/
		ga_skip[i]= 1;				/* skip this argument below		*/
		s         = *a;
		if(*s == '>' && iowrite[0] == '?') {	/* write/append		*/
			iowrite= "w";						/* write mode		*/
			if(s[1] == '>') {					/* append mode		*/
				iowrite= "a";					/* append mode		*/
				++s;
				}
			if(*++s) filespec= s;
			else if(i < argc - 1) { /* filespec is next argument */
				filespec    = *++a;
				ga_skip[++i]= 1;
				}
			/* no file given */
			else error(XTDIO_ERROR,"<%s> but no filename given\n",sprt(*a));

			/* attempt to re-open stdout for write/append to filespec */

			if(freopen(filespec,iowrite,stdout) == NULL) {
				if(iowrite[0] == 'a') {
					iowrite= "w";
					if(freopen(filespec,iowrite,stdout) == NULL) error(XTDIO_ERROR,"cannot open <%s> for append or write\n", filespec);
					}
				else error(XTDIO_ERROR,"cannot open <%s> for write\n",filespec);
				}
			}

		else if(*s == '<' && ioread[0] == '?') { /* read				*/
			ioread= "r";				/* set read mode				*/
			if(*++s) filespec= s;
			else if(i < argc - 1) { 	/* filespec is next argument	*/
				filespec    = *++a;
				ga_skip[++i]= 1;
				}
			else error(XTDIO_ERROR,"<%s> but no filename given",*a);

			/* attempt to reopen stdin for input */
			if(freopen(filespec,ioread,stdin) == NULL) error(XTDIO_WARNING,"cannot open <%s> for input\n",filespec);
			}
		}
	}
#endif	/* vms */

/* --- XTDIO_USAGE ---
 * determine if "?" is the only argument for usage message.  If so,
 * the message is assumed to be a list of strings.  Note that a pair
 * of NULL-byte only strings terminates the array
 */
for(i= qty= 0; i < argc; ++i) if(!ga_skip[i]) {
	++qty;
	if(qty == 1) explain= !strcmp(argv[i],"?") || !strcmp(argv[i],"--help");
	else         break;
	}

if(qty == 1 && explain && usage) ga_usage(usage,1);

/* --- OPTIONS---
 *  handle "-..." arguments as options
 */
if(options) ga_options+= ga_optionhandler('-',argc,argv,options,ga_skip);


/* --- PARAMETERS ---
 * PARMDEF parameters: handle prompt/set/default directions from PARMDEF
 */
if(parms && parmqty > 0) ga_parmhandler(argc,argv,parmqty,parms);


/* --- FPRIOR ---
 * count number of so-far unprocessed command line arguments : place
 * into "ga_filenames".  Note that the user's fprior function has access
 * to ga_skip and so it can prevent dofile from processing any arguments the
 * programmer wishes to.  The number in ga_filenames is sometimes useful to the
 * programmer and so is determined here, however, note that it does so
 * prior to any fooling around fprior does with ga_skip.
 */
if(dofile || fprior) {
	hw= 0;
	for(i= 0; i < argc; ++i) if(!ga_skip[i] && argv[i][0] != '+') {
		hw= hw || ga_haswild(argv[i]);
		++ga_filenames;
		}
	if(hw && ga_filenames <= 1) ga_filenames= 2;
	}

/* if fprior is not NULL, then call fprior now.
 * Thus, the user is able to perform some operations which presumably depend
 * on the parameters/options as interpreted above.  Note that fprior receives
 * the parms data, and so it "knows" about the parameters as set above.
 */
if(fprior) (*fprior)(parmqty,parms);


/* --- DOFILE ---
 * filename processing
 *
 *  This code will indirectly call (*dofile)(char *filename) via
 *  ga_dofilewild or ga_dofile_record.
 *
 *  Ifno filenames have been entered on command line:
 *   (*dofile)("stdin") will be indirectly called.
 *
 * otherwise:
 *   indirectly, dofile will be called, one at a time, with each argument
 *   that is not marked as "to be skipped".
 *
 * (*dofile)() is called by
 *
 *   ga_dofilewild   : (wildcard mode true)
 *                     which processes arguments for wildcard expansion,
 *                     and passes each resulting file one at a time to
 *                     ga_dofile_record.
 *
 *   ga_dofile_record: which calls (*dofile)(filename), and it records the
 *                     filename in the fnhd <-> fntl doubly-linked data
 *                     structure.  This structure is converted to the
 *                     ga_getargc and ga_getargv variables for the programmer's
 *                     subsequent edification and perusal.
 */
if(dofile && ga_dofile) {
	/* decide whether to use standard input or not here */
	usestdin= 1;
	if(ga_skip) {
		/* if any argument is left, it will be dofile'd and hence
		 * stdin not needed
		 */
		for(i= 0; i < argc; ++i) if(!ga_skip[i] && argv[i][0] != '+') {
			usestdin= 0;
			break;
			}
		}

	/* use standard input: give prompt (if any) and ga_dofile_record process */
	if(usestdin) {
		/* indicate whether a fprompt was issued */
		ga_fprompt= fprompt && fprompt[0] && !ga_stopprompt;

		/* for those machines o/s's capable of piping, often times
		 * there's a function to determine whether or not stdin is
		 * coming from a pipe (or re-direction).  If so, then we
		 * shouldn't issue a prompt for files from the user because
		 * we're not interactive.
		 */
#ifdef unix
		if(ga_fprompt) ga_fprompt= isatty(fileno(stdin));
#endif
#ifdef AZTEC_C
		if(ga_fprompt) {
			ga_fprompt= isatty(fileno(stdin));
			}
#endif
#ifdef vms
		if(ga_fprompt && ioread[0] != '?') ga_fprompt= 0;
#endif
#ifdef __WIN32__
		if(ga_fprompt) ga_fprompt= isatty(fileno(stdin));
#endif

		if(ga_fprompt) {	/* issue the prompt here */
			fprintf(stderr,"%s%s%s: ",CYAN,fprompt,GREEN);
			fgets(buf,BUFSIZE,stdin);
			f= stpblk(buf);
			if(!*f) ga_dofile_record(dofile,"stdin");
			else do {
				sscanf(f,"%s",fname);
				if(wild && ga_haswild(fname)) ga_dofilewild(dofile,fname);
				else                          ga_dofile_record(dofile,fname);
				} while(*(f= stpnxt(f,"%s%b")));
			}
		else ga_dofile_record(dofile,"stdin");
		}

	/* process remaining arguments with ga_dofilewild (wildcard) */
	else if(wild) for(i= 0, a= argv; i < argc; ++i, ++a) {
		if(!ga_skip[i]) {
			int optcnt;
			/* apply dofile (with wildcard handling) to any argument
			 * not grabbed by ga_options
			 */
			optcnt= ga_optionhandler('+',1,a,options,ga_skip + i);
			if(optcnt) {
				i         += optcnt - 1;
				a         += optcnt - 1;
				ga_options+= optcnt;
				}
			else ga_dofilewild(dofile,*a);
			}
		}

	/* process remaining arguments with ga_dofile_record (no wildcard) */
	else for(i= 0, a= argv; i < argc; ++i,++a) if(!ga_skip[i]) {
		if(!ga_skip[i]) {
			int optcnt;
			/* apply dofile (with wildcard handling) to any argument
			 * not grabbed by ga_options
			 */
			optcnt= ga_optionhandler('+',1,a,options,ga_skip + i);
			if(optcnt) {
				i         += optcnt - 1;
				a         += optcnt - 1;
				ga_options+= optcnt;
				}
			else ga_dofile_record(dofile,*a);
			}
		}
	}	/* dofile processing */


/* --- TERMINATION ---
 *  finally, setup getargc and getargv
 */
ga_dofile_record((void (*)()) NULL,"");
gtaflag= 0;

}

/* --------------------------------------------------------------------- */

/* ga_usage: this function */
void ga_usage(char **usage,int doexit)
{
char **u    = NULL;
char *pager = NULL;
FILE *tmpfp = NULL;


/* attempt to get pager (optional) */
pager= getenv("GAPAGER");				/* allow user to specify a pager just for getarg-using routines */
if(!pager) pager= getenv("PAGER");		/* attempt to use standard pager								*/

/* XTDIO_NOTE: *two* null-length strings in a row are needed to terminate the
 * list of strings
 */
if(pager) {
	static char usagefile[]="usage.tmp";
	/* write a temporary file and let the user's favorite PAGER handle the display */
	tmpfp= fopen(usagefile,"r");
	if(tmpfp) {
		fclose(tmpfp);
		tmpfp= NULL;
		}
	else {
		tmpfp= fopen(usagefile,"w");
		if(tmpfp) {
			for(u= usage; u[0][0] || u[1][0]; ++u) rdcputs(*u,tmpfp);
			fclose(tmpfp);
			system(strprintf("%s %s",pager,usagefile));
			}
		remove(usagefile);
		}
	}

/* if unsuccessful at writing to tmpfp, or if no pager, write usage to stdout */
if(!tmpfp) {
	for(u= usage; u[0][0] || u[1][0]; ++u) rdcputs(*u,stdout);
	}

if(doexit) {
	exit(GOODEXIT);
	}

}

/* --------------------------------------------------------------------- */

/* ga_optionhandler: this function handles options for getarg */
static int ga_optionhandler(
  char   flagchar,
  int    argc,
  char **argv,
  int  (*options)(char **,char **),
  int   *skip)
{
char **a;
char   c;
char  *s;
int    next;
int    i,j;
int    optcnt;
int    skipcount;


for(a= argv, i= optcnt= 0; i < argc; ++i,++a) {

	c= (*a)[1];	/* look at character following the potential flagchar */

	/* test if -something, where something is not [0-9.] */
	if(**a == flagchar && !(isdigit(c) || c == '.')) {

		/* if flagchar is encountered by itself, then the argument is *not*
		 * processed as an option!
		 */
		if(c == '\0') continue;

		/* increment count of options */
		++optcnt;

		/* The user's options() routine may return an integer:
		 *   +: skip this many subsequent arguments (presumably, these have
		 *      been processed by the user's options() function)
		 *   0: normal every-character-passed to options processing
		 *   -: skip the rest of this argument
		 *
		 *   "options" is called with each character in the string
		 * following a "-" or a "+".  The "-" options are all done
		 * prior to any parameter or file processing; they may appear
		 * anywhere on the line.  The "+" options are done in their
		 * order of appearance on the command line.
		 *
		 * Since the address of "s" (itself a pointer to the present
		 * character), "options" must use "**s" to access the present
		 * character.  This formulation allows "options" to change *s.
		 * Thus, "-t52" could mean: option 't' selected, the following
		 * digits form a terminal number; options would advance *s to
		 * point past the digits by setting "*s+= 2;" .
		 */

		for(next= 0, s= *a+1; *s; ++s) {
			skipcount= (*options)(&s,a);
			if(skipcount < 0) break;
			next    += skipcount;
			}
		skip[i]= 1;		/* indicate: skip current arg for subsequent work */
		for(j= 1; j <= next; ++j) {	/* also skip these args */
			skip[++i]= 1;
			}
		a+= next;
		}	/* -option test				*/
	}		/* for(a= argv ... ) loop	*/

return optcnt;
}

/* --------------------------------------------------------------------- */

/* ga_parmhandler: handles getarg's parameters */
static void ga_parmhandler(
  int      argc,
  char   **argv,
  int      parmqty,
  PARMDEF *parms)
{
PARMDEF     *parm    = NULL;
char       **a;
char        *equal;
int          barflag = 0;
int          i;
int          qty;
static char  buf[BUFSIZE];
static int   skipper = 1;


/* scan list for "parm=value" entries */
for(i= 0, a= argv; i < argc; ++a, ++i) {
	if(!strcmp(*a,"+|")) break;					/* don't even look past +|						*/
	equal= strchr(*a,'=');
	if(equal) {
		*equal= '\0';							/* break arg *a into two strings				*/
		for(qty= 0, parm= parms; qty < parmqty; ++parm, ++qty) {
			if(!strcmp(parm->parmname,*a)) {	/* found a match								*/

				/* translate command line entry via sscanf into parameter						*/
				if(ga_translate(parm->p,parm->type,equal+1)) continue;
				ga_skip[i]        = 1;			/* mark this argument as processed				*/
				parm->skip_option = &skipper;	/* mark this parameter as to-be-skipped below	*/
				break;
				}
			}
		*equal= '=';							/* restore argument								*/
		}
	}

/* go over missing parameters and attempt to fill 'em in with values  from the cmd line			*/
for(i= 0, parm= parms, a= argv, qty= 0, barflag= 0; qty < parmqty; ++i, ++a) {
	if(i < argc && !barflag && !strcmp(*a,"+|")) {
		barflag    = 1;							/* don't look at args past +|					*/
		ga_skip[i] = 1;
		continue;
		}

	if(parm->skip_option && *parm->skip_option) {
		/* skip PARMDEF parameter when parm->skip_option is true
		 * Note that options fires before parameters are checked for, so the
		 * programmer can arrange for the user to skip over a parameter
		 */
		++parm;
		++qty;
		continue;
		}

	if(i < argc && ga_skip && !barflag) {
		/* skip those arguments marked by preceding options as already used,
		 * or those past +|
		 */
		if(ga_skip[i]) {
			continue;
			}

		/* translate command line entry via sscanf into parameter */
		if(ga_translate(parm->p,parm->type,*a)) continue;
		ga_skip[i]= 1;
		}

	else {
		int blen;
		/* there are no more arguments on command line.  issue prompt for them					*/
		++ga_prompts;
		fprintf(stderr,"%sEnter %s%s: ",CYAN,parm->parmname,GREEN);
		fgets(buf,BUFSIZE,stdin);
		/* remove trailing newline */
		blen= strlen(buf);
		if(blen >= 1) buf[blen-1]= '\0';
		ga_translate(parm->p,parm->type,buf);
		}
	++parm; ++qty;
	}

}

/* ----------------------------------------------------------------------- */

/* ga_dofile_record: this function records filenames passed to dofile */
static void ga_dofile_record(
  void (*dofile)(char *),
  char  *filename)
{
static struct fnstr {
	char *filename;
	struct fnstr *nxt;
	} *fnhd=NULL,*fntl=NULL,*fn,*fnnxt;


if(!gtaflag) (*dofile)(filename);	/* not called by getarg (just dofile it) */

else if(dofile) { /* record the filename */
	if(!strcmp(filename,"-")) filename= "stdin";
	tail_link(struct fnstr,fnhd,fntl,
	  "while allocating struct fnstr in ga_dofile_record");
	stralloc(fntl->filename,filename,"allocating filename in ga_dofile_record");
	(*dofile)(fntl->filename);
	}

else { /* set up getargc, getargv, and free up fn's */
	for(ga_getargc= 0, fn= fnhd; fn; fn= fn->nxt) ++ga_getargc;
	if(ga_getargc <= 0) {
		return;
		}

	ga_getargv= (char **) calloc((size_t) ga_getargc,sizeof(char *));
	outofmem((void *) ga_getargv,"setting up ga_getargv\n");
	for(ga_getargc= 0, fn= fnhd; fn; fn= fnnxt) {
		fnnxt               = fn->nxt;
		ga_getargv[ga_getargc++]= fn->filename;
		free((char *) fn);
		}
	}

}

/* ========================================================================= */
/*                                 TIPRO                                     */

#ifdef TIPRO
#include <dta.h>
/* ga_dofilewild: this uses the dofile function passed by the user
 *	along with the filespec to be processed.  It assumes
 *	that wild card characters mean that they are to be used
 *	with the filespecs a la MS-DOS.
 *	   TIPRO
 */
void ga_dofilewild(
  void (*dofile)(),
  char  *filespec)
{
DTA dta,old_dta;


if(!ga_haswild(filespec)) { /* if no wildcards in filespec, dofile it */
	ga_dofile_record(dofile,filespec);
	return;
	}

/* get old DTA and store in old_dta */
mygetdta(&old_dta);

/* find first and subsequent files satisfying filespec.  NORM_FILES is
 * defined in "mydos.h".
 */
if(find_first(filespec,&dta,NORM_FILES)) do {
	setdta(&old_dta);		/* restore old dta	*/
	ga_dofile_record(dofile,dta.fname);	/* process filename	*/
	} while(find_next(&dta));
setdta(&old_dta);		/* restore old dta	*/

}

/* ----------------------------------------------------------------------- */

/* ga_haswild: this function determines if the filespec has any wildcard
 *  characters a la .
 *	   TIPRO
 */
int ga_haswild(char *fspec)
{
char *f;
int ret=0;


for(f= fspec; *f; ++f) if(*f == '*' || *f == '?') {
	ret= 1;
	break;
	}

return ret;
}
#endif	/* #ifdef  TIPRO ... */

/* ========================================================================= */
/*                                 MSC                                     */
#ifdef MSC

/* ga_dofilewild: this uses the dofile function passed by the user
 *	along with the filespec to be processed.  It assumes
 *	that wild card characters mean that they are to be used
 *	with the filespecs a la MS-DOS.
 *	MSC
 */
void ga_dofilewild(
  void (*dofile)(),
  char  *filespec)
{
char          filename[15];
unsigned _cdecl ret;
unsigned      types=NORM_FILES;
struct find_t filefind;


if(!ga_haswild(filespec)) { /* if no wildcards in filespec, dofile it */
	ga_dofile_record(dofile,filespec);
	return;
	}

/* filespec has wildcards in it, so find first and subsequent files
 * satisfying the filespec.  NORM_FILES is defined in <dta.h>
 */
ret= _dos_findfirst(filespec,types,&filefind);
strcpy(filename,filefind.name);
while(!ret) {
	ga_dofile_record(dofile,filename);	/* process filename	*/
	ret= _dos_findnext(&filefind);
	strcpy(filename,filefind.name);
	}

}

/* ----------------------------------------------------------------------- */

/* ga_haswild: this function determines if the filespec has any wildcard
 *  characters a la .
 *	MSC
 */
int ga_haswild(char *fspec)
{
char *f;
int ret=0;


for(f= fspec; *f; ++f) if(*f == '*' || *f == '?') {
	ret= 1;
	break;
	}

return ret;
}
#endif	/* #ifdef  MSC ... */

/* ========================================================================= */
/*                              __WIN32__                                 */
#ifdef __WIN32__

/* ga_dofilewild: this uses the dofile function passed by the user
 *	along with the filespec to be processed.  It assumes
 *	that wild card characters mean that they are to be used
 *	with the filespecs a la MS-DOS.
 *	__WIN32__
 */
void ga_dofilewild(
  void (*dofile)(),
  char  *filespec)
{
char            filename[15];
char           *f;
int             attrb;
int             ret;
int             wildret;
int             idirspec;
static char     dirfilename[128];
struct ffblk    ffblk;


wildret= ga_haswild(filespec);
if(!wildret) { /* if no wildcards in filespec, dofile it */
	ga_dofile_record(dofile,filespec);
	return;
	}
--wildret;

/* set up idirspec, the index to end-of-directory spec */
if(wildret) {
	for(idirspec= wildret; idirspec > 0; --idirspec)
	  if(filespec[idirspec] == '\\' || filespec[idirspec] == ':') {
		  idirspec++;
		  break;
		  }
	}
else idirspec= 0;

/* filespec has wildcards in it, so find first and subsequent files
 * satisfying the filespec.  NORM_FILES is defined in <dta.h>
 */
attrb= FA_RDONLY|FA_DIREC|FA_ARCH;
ret  = findfirst(filespec,&ffblk,attrb);
strcpy(filename,ffblk.ff_name);
while(!ret) {
	for(f= filename; *f; ++f) if(isupper(*f)) *f= tolower(*f);
	/* build directory-path + filename string */
	if(idirspec) {
		strcpy(dirfilename,filespec);
		strcpy(dirfilename + idirspec,filename);
		}
	else strcpy(dirfilename,filename);

	/* process filename	*/
	ga_dofile_record(dofile,dirfilename);

	/* set up for next filename */
	ret= findnext(&ffblk);
	strcpy(filename,ffblk.ff_name);
	}

}

/* ----------------------------------------------------------------------- */

/* ga_haswild: this function determines if the filespec has any wildcard
 *  characters a la .
 *    Returns: 0 if no wildcards
 *             index+1 to where wildcard was found (fspec[ga_haswild()-1])
 *	__WIN32__
 */
int ga_haswild(char *fspec)
{
char *f;
int ret=0;


for(f= fspec; *f; ++f) if(*f == '*' || *f == '?') {
	ret= (f - fspec) + 1;
	break;
	}

return ret;
}
#endif	/* #ifdef  __WIN32__ ... */

/* ======================================================================= */
/*                                VMS                                      */

#ifdef vms
/* the following routines support wildcards for vms */
#include rms
#define FSPEC 128

/* ----------------------------------------------------------------------- */

/* ga_dofilewild: this function is required for wildcard'ed file specifiers
 *  VMS
 */
void ga_dofilewild(
  void (*dofile)(),
  char  *infspec)
{
char *filename;
char *f;
char  fspec[FSPEC];
int   dspec;
struct flist_str {
	char             *filename;
	struct flist_str *nxt;
	};
struct flist_str *fhd      = NULL;
struct flist_str *ftl      = NULL;
struct flist_str *flist    = NULL;
struct flist_str *nxtflist = NULL;
char   filebuf[FSPEC];


/* copy input filespec into local storage */
strcpy(fspec,infspec);

/* determine dspec: is a directory spec included in *argv? */
dspec= ga_hasdirspec(fspec);

/* if dspec, is there any filename?  if not, append * */
if(dspec && !ga_hasfname(fspec)) strcat(fspec,"*");

#ifdef APPEND_WILD
/* missing filespec extension */
if(!ga_hasext(fspec)) strcat(fspec,".*");
#endif

/* if no wildcards, then do a (*dofile)() */
if(!ga_haswild(fspec)) {
	ga_dofile_record(dofile,fspec);
	return;
	}

/* no version #, append ";*" */
if(!ga_hasvn(fspec)) strcat(fspec,";*");

/* use vms-dependent RMS to get filenames */
if(ga_findfirst(fspec,&filename)) do {

	/* --- determine if filename has extension ".dir" --- */

	/* convert filename to upper case */
	for(f= filename; *f; ++f) if(islower(*f)) *f= toupper(*f);

	/* find the end of the directory spec portion (ie. the ']') */
	for(f= filename; *f; ++f) if(*f == ']') break;

	/* find the beginning of the extension (ie. the '.') */
	for(++f; *f; ++f) if(*f == '.') break;

	/* test to see if it is a ".DIR" extension */
	if(*f == '.' && *(f+1) == 'D' && *(f+2) == 'I' && *(f+3) == 'R') continue;
	strcpy(filebuf,filename);

#ifdef __alpha
	/* if openVMS, elide the version number and only process one
	 * version of the file
	 */
	f= strchr(filebuf,';');
	if(f) {
		*f= '\0';
		/* only process one version of a file */
		if(ftl && !strcmp(ftl->filename,filename)) continue;
		}
#endif

	/* link and create new flist_str */
	flist= (struct flist_str *) malloc(sizeof(*flist));
	if(fhd) ftl->nxt= flist;
	else    fhd     = flist;
	ftl       = flist;
	flist->nxt= NULL;

	/* record filename in flist_str */
	if(!dspec) { /* no dspec in fspec, so remove dirspec from filename */
		for(f= filebuf; *f && *f != ']'; ++f);
		if(*f) ++f; /* f points just past ']' now */
		else   f= filebuf;
		}
	else f= filebuf;

	/* record filename into flist */
	flist->filename= (char *) calloc((size_t) strlen(f)+1,sizeof(char));
	strcpy(flist->filename,f);
	} while(ga_findnext(&filename));

else { /* unable to "ga_findfirst" the (possibly modified) fspec		*/
	ga_dofile_record(dofile,infspec); /* so dofile the original input fspec	*/
	return;
	}

/* finally, dofile each filename and then free up associated memory */
for(flist= fhd; flist; flist= nxtflist) {
	nxtflist= flist->nxt;
	ga_dofile_record(dofile,flist->filename);
	free(flist->filename);
	free((char *) flist);
	}
fhd= ftl= flist= NULL;

}

/* ----------------------------------------------------------------------- */

/* ga_haswild: this function determines if the input filename possesses
 *	any wildcard characters (for vms: "%*").
 *  VMS
 */
int ga_haswild(char *fspec)
{
char *f;
int   ret=0;


for(f= fspec; *f; ++f) if(*f == '*' || *f == '%') {
	ret= 1;
	break;
	}

return ret;
}

/* ----------------------------------------------------------------------- */

/* ga_hasdirspec: returns 1 if a directory specification is included, 0 else
 *  VMS
 */
static int ga_hasdirspec(char *fspec)
{
char *f;
int   ret=0;


for(f= fspec; *f; ++f) if(*f == '[' || *f == ':') {
	ret= 1;
	break;
	}

return ret;
}

/* ----------------------------------------------------------------------- */

/* ga_hasext: returns 1 if fspec has an extension
 *  VMS
 */
static int ga_hasext(char *fspec)
{
char *f;
int   ret=0;


/* skip over dirspec, if any */
for(f= fspec; *f; ++f) if(*f == ']') {
	fspec= f + 1;
	break;
	}

for(; *fspec; ++fspec) if(*fspec == '.') {
	ret= 1;
	break;
	}

return ret;
}

/* ----------------------------------------------------------------------- */

/* ga_hasfname: returns 1 if fspec has a filename following dspec
 *  VMS
 */
static int ga_hasfname(char *fspec)
{
char *f;
int   ret=0;


for(f= fspec; *f && (*f != ']' && *f != ':'); ++f);
if(f[0] == ':') {
	if(f[1] == '[') {	/* abc:[... */
		for(f= fspec; *f && *f != ']'; ++f);
		}
	else {				/* abc:... */
		if(*++f) ret= 1;
		else     ret= 0;
		return ret;
		}
	}
if(*f == ']') { /* found end of dspec */
	if(*++f) ret= 1;
	}

return ret;
}

/* ----------------------------------------------------------------------- */

/* ga_hasvn: returns 1 if fspec has a version number specifier
 *   VMS
 */
static int ga_hasvn(char *fspec)
{
int ret=0;


for(; *fspec; ++fspec) if(*fspec == ';') {
	ret= 1;
	break;
	}

return ret;
}

/* ----------------------------------------------------------------------- */

/* data structures for interfacing to RMS */
static struct FAB fab;
static struct NAM nam;

/* ga_findfirst: this function finds the first filename associated with
 *	fspec.
 *   VMS
 */
int ga_findfirst(
  char  *fspec,
  char **filename)
{
static char esa[FSPEC];
static char rsa[FSPEC];
int         parse;
int         ret;


fab          = cc$rms_fab;
nam          = cc$rms_nam;
fab.fab$l_dna= fspec;
fab.fab$b_dns= strlen(fspec);
fab.fab$l_nam= &nam;
nam.nam$l_esa= esa;
nam.nam$b_ess= FSPEC;
nam.nam$l_rsa= rsa;
nam.nam$b_rss= FSPEC;
parse        = sys$parse(&fab);

if(parse != RMS$_SUC) {
	fab.fab$l_dna= NULL;
	fab.fab$b_dns= 0;
	return 0;
	}


/* find the first filename satisfying filespec */
ret= ga_findnext(filename);

return ret;
}

/* ----------------------------------------------------------------------- */

/* ga_findnext: this function finds subsequent matches to the wildcarded
 *	filename.
 *   VMS
 */
int ga_findnext(char **filename)
{

if(sys$search(&fab) != RMS$_NORMAL) { /* return 0 */
	*filename    = NULL;
	fab.fab$l_dna= NULL;
	fab.fab$b_dns= 0;
	return 0;
	}
*filename= nam.nam$l_rsa;


(*filename)[nam.nam$b_rsl]= '\0'; /* forces end-of-string to be NULL byte */

return 1;
}

/* ----------------------------------------------------------------------- */

#include descrip

/* spawn: spawns an argc,argv-style command into the background
 *   VMS
 */
int spawn(
  int argc,
  char **argv)
{
char       *s;
static char cmd[BUFSIZE] = "x";
int         ret          = 0;
long        childstat;
long        flags        = 0L;
globalvalue SS$_NORMAL;
$DESCRIPTOR(DCMD,cmd);
$DESCRIPTOR(DINP,"SYS$COMMAND");
$DESCRIPTOR(DOUT,"SYS$OUTPUT");
$DESCRIPTOR(DNULL,"NLA0:");


/* construct the command string.  By experimentation, I have found
 * that the first argument is inconveniently pre-expanded into a
 * drive:[directory...]cmd.exe
 * style name.  The following code serves to obtain just the "cmd"
 * portion
 */

for(s= *argv; *s; ++s);					/* locate last character in first argv	*/
for(--s; s >= *argv && *s != '.'; --s);	/* locate '.' in suffix					*/
if(s > *argv) *s= '\0';					/* remove suffix						*/
for(--s; s >= *argv && *s != ']'; --s); /* locate ']' designator				*/
if(*s == ']') strcpy(cmd,s+1);
else          strcpy(cmd,s);

/* copy the rest of the arguments into cmd */
for(--argc, ++argv; argc; --argc, ++argv) {
	strcat(cmd," ");
	strcat(cmd,*argv);
	}

/* handle vms's run-time library call to lib$spawn */
DCMD.dsc$w_length = strlen(cmd);
flags             = 1; /* set bit 0 to 1, thereby enabling "NOWAIT" */

/* DNULL means that spawned processes cannot accept input from anyplace */
if((ret= lib$spawn(&DCMD,&DNULL,0,&flags,0,0,&childstat,0,0,0,0,0))
  != SS$_NORMAL) {
	return 1;
	}

if(childstat & 1L)       ret= 0;
else if(childstat == 0L) ret= 1;
else if(childstat < 0)   ret=  -childstat;
else                     ret= childstat;

return ret;
}
#endif	/* #ifdef vms ... */

/* ======================================================================= */
/*                              UNIX                                       */

#if defined(unix) || defined(__linux)
/* ga_dofilewild: this uses the dofile function passed by the user
 *	along with the filespec to be processed.  It assumes
 *	that wild card characters mean that they are to be used
 *	with the filespecs a la UNIX.
 *	  UNIX
 */
void ga_dofilewild(
  void (*dofile)(),
  char *filespec)
{
char  buf[BUFSIZE];
char  filename[BUFSIZE];
FILE *fp;


if(!ga_haswild(filespec)) { /* if no wildcards in filespec, dofile it */
	ga_dofile_record(dofile,filespec);
	return;
	}

/* open a pipe */
sprintf(buf,"ls %s",filespec);
fp= popen(buf,"r");

/* read in filenames from the pipe */
if(fp) {
	while(fgets(buf,BUFSIZE,fp)) {
		sscanf(buf,"%s",filename);
		ga_dofile_record(dofile,filename);
		}

	/* close the pipe */
	pclose(fp);
	}

}

/* ----------------------------------------------------------------------- */

/* ga_haswild: this function determines if the filespec has any wildcard
 *  characters a la UNIX.
 *	  UNIX
 */
int ga_haswild(char *fspec)
{
char *f;
int   ret=0;


for(f= fspec; *f; ++f) if(*f == '*' || *f == '?' || *f == '[') {
	ret= 1;
	break;
	}

return ret;
}
#endif /* #ifdef unix ... */

/* ======================================================================= */
/*                               AMIGA-DOS                                 */

#ifdef AZTEC_C
/* ga_dofilewild: this uses the dofile function passed by the user
 *	along with the filespec to be processed.  It assumes
 *	that wild card characters mean that they are to be used
 *	with the filespecs a la UNIX.
 *	AMIGA-DOS
 */
void ga_dofilewild(
  void (*dofile)(char *),
  char  *filespec)
{
char *filename;
FILE *fp;


if(!ga_haswild(filespec)) { /* if no wildcards in filespec, dofile it */
	ga_dofile_record(dofile,filespec);
	return;
	}

/* use scdir() to get filenames from filespec */
while((filename= scdir(filespec))) ga_dofile_record(dofile,filename);

}

/* ----------------------------------------------------------------------- */

/* ga_haswild: this function determines if the filespec has any wildcard
 *  characters a la UNIX.
 *	AMIGA-DOS
 */
int ga_haswild(char *fspec)
{
char *f;
int   ret=0;


for(f= fspec; *f; ++f) if(*f == '*' || *f == '?') {
	ret= 1;
	break;
	}

return ret;
}
#endif /* #ifdef AZTEC_C ... */

/* =========================================================================
 * Test Code:
 */

/* --------------------------------------------------------------------- */
