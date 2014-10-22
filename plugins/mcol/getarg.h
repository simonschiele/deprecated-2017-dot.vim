/* getarg.h: definitions and codes for Dr. Chip's getarg() facility for
 *  interpreting command line arguments
 *
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 *
 *  Routines Include: <getarg>
 *
 *    void getarg(
 *      int      argc,                      // qty arguments on cmd line
 *      char   **argv,                      // list of cmdline arguments
 *      int      parmqty,                   // qty of parameters
 *      PARMDEF *parmdef,
 *      char   **usage,
 *      int    (*options)(char **,char **),
 *      void   (*fprior)(int,PARMDEF *),
 *      void   (*dofile)(char *),
 *      int      wild,
 *      char    *fprompt)
 *
 * msdos:
 *    void ga_dofilewild( void (*dofile)(char *filename), char *filespec)
 *
 * vms:
 *    void ga_dofilewild( void (*dofile)(char *filename), char *infspec)
 *    int ga_haswild(char *fspec)
 *    int spawn( int argc, char **argv)
 *
 * unix:
 *    void ga_dofilewild( void (*dofile)(char *filename), char *filespec)
 *    int ga_haswild(char *fspec)
 *
 * amiga:
 *    void ga_dofilewild( void (*dofile)(char *filename), char *filespec)
 *    int ga_haswild(char *fspec)
 *
 *  Author: Dr. Charles E. Campbell, Jr.
 */
#ifndef GETARG_H
#define GETARG_H

/* --------------------------------------------------------------------------
 * Getarg Definitions: (these are PARMDEF types)
 *
 *                             Description			Cast		Format Code
 */
#define GA_BOOLEAN		0		/* for an int			(int)				%d		*/
#define GA_CHAR			1		/* for a  char			(char)				%c		*/
#define GA_DOUBLE		2		/* for a  double		(double)			%lf		*/
#define GA_FLOAT		3		/* for a  float			(float)				%f		*/
#define GA_HEX			4		/* for an int			(int)				%x		*/
#define GA_INT			5		/* for an int			(int)				%d		*/
#define GA_LINE			6		/* for an entire line	(char *)			fgets	*/
#define GA_LOGICAL		7		/* for an int			(int)				%d		*/
#define GA_LONG			8		/* for a  long			(long)				%ld		*/
#define GA_LONGHEX		9		/* for long hex			(long int)			%lx		*/
#define GA_LONGOCTAL	10		/* for long octal		(long int)			%lo		*/
#define GA_OCTAL		11		/* for an int 			(int)				%o		*/
#define GA_SHORTHEX		12		/* for short hex		(short int)			%hx		*/
#define GA_SHORTOCTAL	13		/* for short octal		(short int)			%ho		*/
#define GA_STRING		14		/* for a  string		(char *)			%s		*/
#define GA_STRUCT		15		/* for user specified data structure				*/
#define GA_UCHAR		16		/* for unsigned char	(unsigned char)		%x		*/
#define GA_UINT			17		/* for unsigned int		(unsigned)			%u		*/
#define GA_ULONG		18		/* for unsigned long	(unsigned long)		%lu		*/
#define GA_USHORT		19		/* for unsigned short	(unsigned short)	%hu		*/

/* The getarg() function is defined:
 *
 *		int getarg(
 *		  int      argc,       // from main(int argc,char **argv)
 *		  char   **argv,       // from main(int argc,char **argv)
 *		  int      parmqty,    // number of parameters
 *		  PARMDEF *parmdef,    // list of parameters
 *		  char   **usage,      // list of strings giving usage
 *		  int    (*options)(), // options processing function
 *		  void   (*fprior)(),  // executed once prior to dofile
 *		  void   (*dofile)(),  // executed for each non-opt,parm argument
 *		  int      wild,       // 0: no wildcard   1: wildcard expansion used
 *		  char    *fprompt);   // if no args left for dofile, and fprompt not
 *		                       // null (or ""), then use it to prompt user for
 *		                       // for filename(s)
 *
 * PARMDEF parms,int parmqty:
 *         is the (typedef) command line description structure.
 *    *p          : a "generic" pointer of type (void *) to the parameter
 *     type       : an integer (use the defines above) indicating type of
 *                  parameter
 *    *skip_option: skip parameter prompting if true or null
 *    *prompt     : a string to show the user prior to accepting data from the
 *	                keyboard.
 *
 *         Note: if the prompt is a NULL string then the parameter
 *         will be unchanged; the default value will be used instead.
 *         Prompts will be used only for those variables to which 
 *         a command line argument could not be bound.
 *
 *         Furthermore, if "skip_option" is not null, then it is taken to be
 *         an option.  If that option (*opt) is "true", then the parameter
 *         will not be prompted for.  This allows an option to specify whether
 *         or not a parameter is required (such as saying that a special
 *         option routine will be called in "fprior" to process a file
 *         instead of just a command line option).
 *
 *	fprior: called prior to dofile.  parms are passed, so fprior has
 *	access to whatever was set into the parameters/options.
 *	  fprior(
 *	    int parmqty,
 *	    PARMDEF *parms)
 *
 *	dofile: this function is called separately with each remaining
 *	argument (that wasn't an option or parameter).
 *	  dofile(char *filename)
 *
 *	options: this is called for arguments beginning with "-", except
 *	for those of the form ("-." or "-#", where # is 0-9).  It is called
 *	for each character in such an argument, other than the first "-"
 *	itself, unless "-" is the only character in an argument.  "**s" is
 *	the character in the present argument "*a" being processed.  "options"
 *	should return an integer specifying how many subsequent arguments it
 *	processed (usually 0).
 *	  int options(char **s,char **a)
 */

/* ---------------------------------------------------------------------
 * Typedefs:
 */
typedef struct GA_Codes_str		GA_Codes;
typedef struct GA_ParmDef_str	PARMDEF;

/* ---------------------------------------------------------------------
 * Data Structures:
 */
struct GA_ParmDef_str {
	void *p;			/* a "generic" pointer to the parameter			*/
	int   type;			/* an integer indicating type of parameter		*/
	int  *skip_option;
	char *parmname;		/* name of paramter for prompt string			*/
	};

struct GA_Codes_str {
	char *fmt;
	char  decimal;
	char  hex;
	char  oct;
	char  floating;
	};


/* ---------------------------------------------------------------------
 * External Data: (getarg sets these up)
 */
extern char **ga_getargv;	/* filename list								*/
extern int    ga_dofile;	/* allows options to override dofile processing	*/
extern int    ga_filenames;	/* qty args which are filenames					*/
extern int    ga_fprompt;	/* yes/no: filename prompt issued				*/
extern int    ga_getargc;	/* qty filenames in ga_getargv					*/
extern int    ga_options;	/* qty args processed as options				*/
extern int    ga_prompts;	/* qty parm prompts issued						*/
extern int    ga_stopprompt;/* 0=normal  1=options wants *not* to prompt	*/
extern int   *ga_skip;		/* skip arg vector								*/

/* ---------------------------------------------------------------------
 * Prototypes:
 */
#ifdef __PROTOTYPE__

void getarg( int, char **, int, PARMDEF *, char **,    /* getarg.c        */
   int (*)(char **,char **), void (*)(int,PARMDEF *), void (*)(char *), int,
   char *);

#ifdef MSDOS
void ga_dofilewild( void (*)(), char *);               /* getarg.c        */
#endif

#ifdef vms
void ga_dofilewild( void (*)(), char *);               /* getarg.c        */
int ga_haswild(char *);                                /* getarg.c        */
int spawn( int, char **);                              /* getarg.c        */
#endif

#ifdef unix
void ga_dofilewild( void (*)(), char *);               /* getarg.c        */
int ga_haswild(char *);                                /* getarg.c        */
#endif

#ifdef MCH_AMIGA
void ga_dofilewild( void (*)(char *), char *);         /* getarg.c        */
int ga_haswild(char *);                                /* getarg.c        */
#endif

#else	/* #ifdef __PROTOTYPE__ ... #else ... #endif	*/

extern void getarg();                                  /* getarg.c        */

#ifdef MSDOS
extern void ga_dofilewild();                           /* getarg.c        */
#endif

#ifdef vms
extern void ga_dofilewild();                           /* getarg.c        */
extern int ga_haswild();                               /* getarg.c        */
extern int spawn();                                    /* getarg.c        */
#endif

#ifdef unix
extern void ga_dofilewild();                           /* getarg.c        */
extern int ga_haswild();                               /* getarg.c        */
#endif

#ifdef MCH_AMIGA
extern void ga_dofilewild();                           /* getarg.c        */
extern int ga_haswild();                               /* getarg.c        */
#endif

#endif	/* #ifdef __PROTOTYPES__ ... #else ... #endif	*/

#endif  /* #ifndef GETARG_H ... #endif					*/
