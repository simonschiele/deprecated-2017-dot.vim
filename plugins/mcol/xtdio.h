/* xtdio.h: an external header file for the pattern matching routines
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#ifndef XTDIO_H
#define XTDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------------
 * Includes:
 */

#if defined(AIX)
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# ifndef unix
#  define unix
# endif

#elif defined(apollo)
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>

#elif defined(__BORLANDC__)
# define  msdos
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <time.h>

#elif defined(__DECC) || defined(__alpha) || defined(__osf__)
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>

#elif defined(__linux)
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <time.h>
# if defined(__STRICT_ANSI__) && !defined(__USE_POSIX)
	 extern FILE *fdopen __P ((int, __const char *));
	 extern int fileno __P ((FILE*));
	 extern FILE* popen __P ((__const char*, __const char*));
	 extern int pclose __P ((FILE*));
# endif

#elif defined(MCH_AMIGA)
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>

#elif defined(__MSDOS__)
# define msdos
# ifndef MSDOS
#  define MSDOS
# endif
# ifndef msdos
#  define msdos
# endif
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <time.h>

#elif defined(sgi)
# ifdef __MALLOC_DBG_H__
#  include "mallocdbg2.h"
# else
#  include <strings.h>
#  include <stdlib.h>
# endif
# include <stdarg.h>

#elif defined(sun)
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>

#elif defined(ultrix)
/* # define OldUltrix */
# ifdef OldUltrix
#  include <string.h>
#  include <stdlib.h>
#  include <varargs.h>
# else
#  include <strings.h>
#  include <stdlib.h>
#  include <stdarg.h>
# endif

#elif defined(vms)

# ifndef __STDIO_LOADED
#  ifndef oldvms
#   define oldvms 1
#  endif
# endif

# ifdef oldvms
#  include "xstdlib.h"
#  include "xvarargs.h"
#  define  defined(x) 0
#  define  strtok stptok

# else	/* new vms */
#  include <string.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  define fgets(s,n,fp)			vmsfgets(s,n,fp)
#  define read(fp,buf,bufsiz)	vmsread(fp,buf,bufsiz)
#  ifndef __DESCRIP_LOADED
#   include <descrip.h>
    typedef struct dsc$descriptor DESC;
#  endif
# endif
# define system(cmd) vms_system(cmd)

#endif

#ifndef __STDIO_H__
# include <stdio.h>
#endif

#include "rdcolor.h"
#include "links.h"
#include "pat.h"
#include "getarg.h"
#include "setproto.h"		/* sets __PROTOTYPE__ */

/* --------------------------------------------------------------------- */

/* standard Dr. Chip includes */
#ifndef EXIT
# define EXIT(rc) exit(rc)
#endif

#ifdef ultrix
# define const
#endif

/* -------------------------------------------------------------------------
 * Definitions:
 */
#define isoct(c) ('0' <= (c) && (c) <= '7')
#define ishex(c) \
 (isdigit(c) || ('a' <= (c) && (c) <= 'f') || ('A' <= (c) && (c) <= 'F'))

/* error support */
#define XTDIO_SEVERE		0
#ifndef XTDIO_ERROR
# define XTDIO_ERROR		1
#endif
#ifndef XTDIO_WARNING
# define XTDIO_WARNING	2
#endif
#define XTDIO_NOTE		3
#define XTDIO_USAGE		4
#define XTDIO_ERRORMORE	5

#ifndef USE_ESCAPES
# define USE_ESCAPES		1
#endif

#define MTCHMAX 10 /* stcmpma support */

/* -------------------------------------------------------------------------
 * Typedefs:
 */
typedef struct PS_LEAF_str		PS_LEAF;
typedef struct PS_SORT_str		PS_SORT;
typedef struct PS_str			PS;
typedef struct PS_str			ParSrch;

/* -------------------------------------------------------------------------
 * Data Structures:
 */

/* supports ps_make, ps_insert, ps_search, ps_delete, etc */
struct PS_LEAF_str {	/* PS_LEAF:											*/
	char     c;			/* character needed to transition to this leaf		*/
	void    *output;	/* this ptr is output as match if end-of-word		*/
	int      id;		/* for debugging -- helps to track leaves			*/
	PS_LEAF *left;		/* supports left-side fanout from leaf->prv			*/
	PS_LEAF *right;		/* supports right-side fanout from leaf->prv		*/
	PS_LEAF *nxt;		/* points to next ps_tree node fanout root			*/
	PS_LEAF *prv;		/* points to root of fanout's predecessor			*/
	};

struct PS_str {			/* PS:	ParSrch:									*/
	PS_LEAF *tree;		/* first character is hashed						*/
	PS_SORT *shd;		/* head of linked list of PS_SORT entries			*/
	PS_SORT *stl;		/* tail of linked list of PS_SORT entries			*/
	PS_SORT *current;	/* support for ps_srtnxt ps_srtprv					*/
	int      treesize;	/* starts at 128; may be boosted to 256 if needed	*/
	int      nwords;	/* qty of words stored in tree						*/
	int      id;		/* serves as identifier for this ParSrch			*/
#ifdef __PROTOTYPE__
	int    (*accept)(int);	/* this function restricts what characters		*/
#else	/* __PROTOTYPE__ */	/* are to be considered acceptable for ParSrch	*/
	int    (*accept)();		/* engine search.  Default: is isalnum()||'_'	*/
#endif	/* __PROTOTYPE__ */	/* note: isany() is pre-supplied				*/
	};

struct PS_SORT_str {	/* PS_SORT:											*/
	PS_LEAF *leaf;		/* associated PS_LEAF								*/
	PS_SORT *nxt;		/* doubly linked list support						*/
	PS_SORT *prv;		/* doubly linked list support						*/
	};

/* supports stcmpma */
struct mtchlst {		/* external sub-field match list					*/
	char *start;		/* the i'th sub-field start pointer					*/
	char *last;			/* the i'th sub-field last pointer					*/
	};

/* stcmpma support: */
extern struct mtchlst stcmpma_mtch[MTCHMAX];
extern int            stcmpma_mcnt;
extern char           stcmpma_underscore;

/* ---------------------------------------------------------------------
 * Machine Dependent Defines:
 */
#ifdef MCH_AMIGA
# define system(cmd)			SyStem(cmd)
# define bzero(obj,nbytes)		memset(obj,0,nbytes)
# define bcopy(tgt,src,nbytes)	memcpy(tgt,src,nbytes)
#endif

#ifdef sun
# define const
#endif

/* -------------------------------------------------------------------------
 * Global Variables:
 */

/* fopenv/fopenx support */
extern char *fopenvfile;
extern char *fopenxfile;

/* ncgets support */
extern char *ncgetsprompt;						/* allows prompt for no-comment-gets				*/

/* matdisp support */
extern char *matdispfmt;						/* default matdisp format (>= 5)					*/
extern char *imatdispfmt;						/* default matout format (>= 5)						*/
extern int   screenheight;						/* rows    in display								*/
extern int   screenwidth;						/* columns in a line available to matdisp			*/
extern int   use_escapes;						/* (don't) use ANSI escape sequences				*/

/* multicol support */
extern char  multicol_moreflag;					/* have multicol pause every screenheight-1 lines	*/
extern char *multicol_leader;					/* print out before every line						*/
extern char *multicol_oneleader;				/* print out before 1st line, blanks after			*/
extern char *multicol_section;					/* allow a section of text to be unaltered			*/
extern int   multicol_len;						/* maximum width of multicolumn output				*/
extern int   multicol_sectioncol;				/* begin output of section at/after this column		*/
extern int   multicol_transpose;                /* column/row oriented table                        */

extern unsigned long  autobuf_fgets_linenum;	/* autobuf_fgets line number						*/
extern char          *strnxtfmt_code;			/* strnxtfmt format-code pointer					*/

#ifdef __PROTOTYPE__
extern char *(*multicol_render)(char *,int);	/* multicol's rendering function					*/
#else
extern char *(*multicol_render)();
#endif

/* stcmpma support: */
extern struct mtchlst stcmpma_mtch[MTCHMAX];
extern int            stcmpma_mcnt;
extern char           stcmpma_underscore;

/* outofmem and error support */
#ifdef __PROTOTYPE__
extern void (*error_exit)(int);
#else
# define const
extern void (*error_exit)();
#endif

extern FILE *errfp;

/* getarg support */
#ifndef NO_GETARG_H
extern GA_Codes ga_codes[];
#endif

#ifdef __cplusplus
	}
#endif

/* ---------------------------------------------------------------------
 * Prototypes
 */
#include "proto.h"

#ifdef __PROTOTYPE__

char *arraysprt(char **,int ,char *);                  /* arraysprt.c     */
char *autobuf_fgets(FILE *,size_t *);                  /* autobuf_fgets.c */
char *binprt( int,  unsigned long);                    /* binprt.c        */
char *binprtall(unsigned long);                        /* binprt.c        */
unsigned fputb(unsigned,int);                          /* bits.c          */
unsigned fgetb(unsigned *,unsigned);                   /* bits.c          */
long ToJul( int,  int,  int);                          /* calcnvrt.c      */
void FromJul( long, int *, int *, int *);              /* calcnvrt.c      */
int IsLeapYear(int);                                   /* calcnvrt.c      */
int DayOfWeek(long);                                   /* calcnvrt.c      */
long DayWhen(long,int);                                /* calcnvrt.c      */
int isfullmoon(long);                                  /* calcnvrt.c      */
int isnewmoon(long);                                   /* calcnvrt.c      */
void chrname(char *,int,int);                          /* chrname.c       */
char *cprt(const char);                                /* cprt.c          */
FILE *ctropen(char *);                                 /* ctropen.c       */
void date(char *);                                     /* date.c          */
int daywk( int,  int,  int);                           /* daywk.c         */
void prt_traceback(void);                              /* dbg.c           */
void edbg(char *,...);                                 /* dbg.c           */
void rdbg(char *,...);                                 /* dbg.c           */
int dprintf(int,char *,...);                           /* dbg.c           */
int dbgswitch(int);                                    /* dbg.c           */
void initdbg(int *,char **);                           /* dbg.c           */
void initdbg2(char *);                                 /* dbg.c           */
void initdbg3(char *);                                 /* dbg.c           */
void prt_dbgstr(char *,...);                           /* dbg.c           */
void dsetjmp(void *);                                  /* dbg.c           */
void dlongjmp(void *,char *,...);                      /* dbg.c           */
int dbgtst(int);                                       /* dbg.c           */
void prt_debugstate(char *,...);                       /* dbg.c           */
FILE *dbgfpget(void);                                  /* dbg.c           */
void dbgmatdisp(double *,int,int,char *,...);          /* dbgmatdisp.c    */
void dispp2s(FILE *,char *,char *,char *);             /* dispp2s.c       */
void dmatdisp(double *,int,int,char *,...);            /* dmatdisp.c      */
void setup_dodir( void (*)(char *),  char **,  int);   /* dodir.c         */
void dodir(char *);                                    /* dodir.c         */
void eastr( int,  int *,  int *);                      /* eastr.c         */
void Paskha(int,int *,int *,int *,int *);              /* eastr.c         */
void fmatdisp( float *,  int,  int,  char *,...);      /* fmatdisp.c      */
void error( int, char *, ...);                         /* error.c         */
char *escape_interpret(char *,char *);                 /* escintrp.c      */
void fdmatdisp(FILE *,double *,int,int,char *,...);    /* fdmatdisp.c     */
void fdpmatdisp(FILE *,double **,int,int,char *,...);  /* fdpmatdisp.c    */
void setFileOptions( char *, void *, int);             /* fileOptions.c   */
int getFileOptions( char *, char *, char *);           /* fileOptions.c   */
void getVarOptions(char *);                            /* fileOptions.c   */
int filepathsrch( char *,  char *,  char *);           /* filepathsrch.c  */
int fkeys(void);                                       /* fkeys.c         */
unsigned long ieee2vms(unsigned long);                 /* floatcnvrt.c    */
unsigned long vms2ieee(unsigned long);                 /* floatcnvrt.c    */
FILE *fopenv(char *,char *,char *);                    /* fopenv.c        */
FILE *fopenx( char *,  char *,  char *,  char *);      /* fopenx.c        */
void ga_envhandler(char *,int (*)(char **,char **));   /* gaenv.c         */
int ga_translate( void *, int, char *);                /* ga_translate.c  */
void GetDate(int *,int *,int *,int *,int *,int *);     /* getdate.c       */
float *getfmat( FILE *,  float *,  int,  int,  char *, /* getfmat.c       */
    int);
int getline( char *,  int,  FILE *,  char *,  ...);    /* getline.c       */
double *getmat( FILE *,  double *,  int,  int,  char *,/* getmat.c        */
    int);
long GetFileDate(char *, int *,int *,int *, int *,int *,/* gtfdate.c      */
  int *);
char *hexprt(const void *,int);                        /* hexprt.c        */
void hsi2rgb( double, double, double, short *, short *,/* hsi2rgb.c       */
   short *);
void imatdisp(int *,int,int,char *,...);               /* imatdisp.c      */
void ipmatdisp(int **,int,int,char *);                 /* ipmatdisp.c     */
#ifdef sgi
int isdir(char *);                                     /* isdir.c         */
#endif
int islastchar(FILE *);                                /* islastch.c      */
void loadmulticol(char *);                             /* loadmulticol.c  */
void sortmulticol(void);                               /* loadmulticol.c  */
int unloadmulticol( int,  char *,  FILE *);            /* loadmulticol.c  */
int mkbkupfile(char *,char *);                         /* mkbkupfile.c    */
int multicol(int,char **,int,char *,FILE *);           /* multicol.c      */
int ncfscanf(FILE *,char *,...);                       /* ncfscanf.c      */
char *ncgets(char *,int,FILE *);                       /* ncgets.c        */
void outofmem(void *,char *,...);                      /* outofmem.c      */
int ps_accept(int);                                    /* parsrch.c       */
int isany(int);                                        /* parsrch.c       */
PS *ps_make(void);                                     /* parsrch.c       */
PS *ps_duplicate(PS *);                                /* parsrch.c       */
void *ps_insert( PS *, char *, void *);                /* parsrch.c       */
void ps_free( PS *,  void (*)(void *));                /* parsrch.c       */
int ps_delete( PS *, char *, void (*)(void *));        /* parsrch.c       */
char *ps_search( PS *, char *, void **);               /* parsrch.c       */
char *ps_beginwith( PS *, char *, void **);            /* parsrch.c       */
PS_LEAF *ps_goto( PS_LEAF *, char);                    /* parsrch.c       */
void ps_prtleaf( FILE *, PS_LEAF *);                   /* parsrch.c       */
void ps_prttree(FILE *,PS *);                          /* parsrch.c       */
void ps_optimize(PS *);                                /* parsrch.c       */
void pfmatdisp(float **,int,int,char *,...);           /* pfmatdisp.c     */
void pmatdisp(double **,int,int,char *,...);           /* pmatdisp.c      */
void set_preprochar(char);                             /* prepro.c        */
int preprocess(char *,int (*)(char *));                /* prepro.c        */
void prmatdisp(double **,int,int,char *,int);          /* prmatdisp.c     */
int initpsfkeys(void);                                 /* psfkeys.c       */
int pstrlen(int,char *);                               /* pstrlen.c       */
void ps_srtinit(ParSrch *);                            /* ps_iterate.c    */
void *ps_srtnxt(ParSrch *);                            /* ps_iterate.c    */
void *ps_srtprv(ParSrch *);                            /* ps_iterate.c    */
void ps_srtclear(PS *);                                /* ps_iterate.c    */
char *ps_partialfirst( PS *, char *, void **);         /* ps_partial.c    */
char *ps_partialnxt(void **);                          /* ps_partial.c    */
void ps_clearpartial(void);                            /* ps_partial.c    */
int putroman(int);                                     /* putroman.c      */
int qsortstrcmp( const void *, const void *);          /* qsortstrcmp.c   */
char rawgetc(void);                                    /* rawgets.c       */
char *rawgets(char *);                                 /* rawgets.c       */
void rawungetc(char);                                  /* rawgets.c       */
int rawinput(void);                                    /* rawinput.c      */
void ttyRestore(void);                                 /* rawinput.c      */
void rdcolor(void);                                    /* rdcolor.c       */
void rdcputs(char *,FILE *);                           /* rdcolor.c       */
void setup_screendata(char *);                         /* rdcolor.c       */
void rgb2hsi( short, short, short, double *, double *, /* rgb2hsi.c       */
   double *);
char *snprt(char *,int);                               /* snprt.c         */
char *sprt(const void *);                              /* sprt.c          */
char *srmtrblk(char *);                                /* srmtrblk.c      */
int stcnarg(const char *);                             /* stcnarg.c       */
int stcpm( char *, char *, char **);                   /* stcpm.c         */
int stcpma( char *, char *);                           /* stcpm.c         */
int stmpma(char *,char *);                             /* stmpma.c        */
int stmpm(char *,char *,char **);                      /* stmpma.c        */
char *stpblk(char *);                                  /* stpblk.c        */
char *stprblk(char *, char *);                         /* stprblk.c       */
char *stpbrk(char *,char *);                           /* stpbrk.c        */
char *stpchg(char *,char *,char *,int);                /* stpchg.c        */
char *stpchr(char *,char);                             /* stpchr.c        */
char *stpchres(char *,char);                           /* stpchres.c      */
char *stprchr(char *,char *,char);                     /* stprchr.c       */
char *stpend(char *);                                  /* stpend.c        */
char *stpfmt( char *, char **);                        /* stpfmt.c        */
char *stpnxt(char *,char *);                           /* stpnxt.c        */
char *stprarg( char *, int);                           /* stprarg.c       */
char *stptok(char *,char *,int,char *);                /* stptok.c        */
int strctype( char **,  char *,  char *,  char *);     /* strctype.c      */
char *stpskip(char *);                                 /* strctype.c      */
int whereis_uvar( char *,  char **,  char **);         /* strctype.c      */
int strfmtlen(char *);                                 /* strfmtlen.c     */
long strmdy(int *,int *,int *,char *);                 /* strmdy.c        */
char *strnxtfmt(char *);                               /* strnxtfmt.c     */
char *strprintf(char *,...);                           /* strprintf.c     */
void strtoday(char *);                                 /* strtoday.c      */
char *strtolower(char *);                              /* strtolower.c    */
char *strtoupper(char *);                              /* strtoupper.c    */
int termtest(int);                                     /* termtest.c      */
char *texprotect(char *);                              /* texprotect.c    */

#else      /* ---------------------------------------------------------------- */

extern char *arraysprt();                              /* arraysprt.c     */
extern char *autobuf_fgets();                          /* autobuf_fgets.c */
extern char *binprt();                                 /* binprt.c        */
extern char *binprtall();                              /* binprt.c        */
extern unsigned fputb();                               /* bits.c          */
extern unsigned fgetb();                               /* bits.c          */
extern long ToJul();                                   /* calcnvrt.c      */
extern void FromJul();                                 /* calcnvrt.c      */
extern int IsLeapYear();                               /* calcnvrt.c      */
extern int DayOfWeek();                                /* calcnvrt.c      */
extern long DayWhen();                                 /* calcnvrt.c      */
extern int isfullmoon();                               /* calcnvrt.c      */
extern int isnewmoon();                                /* calcnvrt.c      */
extern void chrname();                                 /* chrname.c       */
extern void cmatdisp();                                /* cmatdisp.c      */
extern char *cprt();                                   /* cprt.c          */
extern void csubmatdisp();                             /* csubmatdisp.c   */
extern void csubpmatdisp();                            /* csubpmatdisp.c  */
extern FILE *ctropen();                                /* ctropen.c       */
extern void date();                                    /* date.c          */
extern int daywk();                                    /* daywk.c         */
extern void prt_traceback();                           /* dbg.c           */
extern void edbg();                                    /* dbg.c           */
extern void rdbg();                                    /* dbg.c           */
extern int dprintf();                                  /* dbg.c           */
extern int dbgswitch();                                /* dbg.c           */
extern void initdbg();                                 /* dbg.c           */
extern void initdbg2();                                /* dbg.c           */
extern void initdbg3();                                /* dbg.c           */
extern void prt_dbgstr();                              /* dbg.c           */
extern void dsetjmp();                                 /* dbg.c           */
extern void dlongjmp();                                /* dbg.c           */
extern int dbgtst();                                   /* dbg.c           */
extern void prt_debugstate();                          /* dbg.c           */
extern FILE *dbgfpget();                               /* dbg.c           */
extern void dbgcmatdisp();                             /* dbgcmatdisp.c   */
extern void dbgmatdisp();                              /* dbgmatdisp.c    */
extern void dispp2s();                                 /* dispp2s.c       */
extern void dmatdisp();                                /* dmatdisp.c      */
extern void setup_dodir();                             /* dodir.c         */
extern void dodir();                                   /* dodir.c         */
extern void eastr();                                   /* eastr.c         */
extern void Paskha();                                  /* eastr.c         */
extern void fmatdisp();                                /* fmatdisp.c      */
extern void error();                                   /* error.c         */
extern char *escape_interpret();                       /* escintrp.c      */
extern void fdcmatdisp();                              /* fdcmatdisp.c    */
extern void fdmatdisp();                               /* fdmatdisp.c     */
extern void fdpmatdisp();                              /* fdpmatdisp.c    */
extern unsigned long ieee2vms();                       /* floatcnvrt.c    */
extern unsigned long vms2ieee();                       /* floatcnvrt.c    */
extern void setFileOptions();                          /* fileOptions.c   */
extern int getFileOptions();                           /* fileOptions.c   */
extern void getVarOptions();                           /* fileOptions.c   */
extern int filepathsrch();                             /* filepathsrch.c  */
extern int fkeys();                                    /* fkeys.c         */
extern FILE *fopenv();                                 /* fopenv.c        */
extern FILE *fopenx();                                 /* fopenx.c        */
extern void ga_envhandler();                           /* gaenv.c         */
extern int ga_translate();                             /* ga_translate.c  */
extern void freepg();                                  /* freepg.c        */
extern void getdate();                                 /* getdate.c       */
extern void getdate();                                 /* getdate.c       */
extern void getdate();                                 /* getdate.c       */
extern void getdate();                                 /* getdate.c       */
extern float *getfmat();                               /* getfmat.c       */
extern int getline();                                  /* getline.c       */
extern double *getmat();                               /* getmat.c        */
extern long GetFileDate();                             /* gtfdate.c       */
extern char *hexprt();                                 /* hexprt.c        */
extern void hsi2rgb();                                 /* hsi2rgb.c       */
extern void imatdisp();                                /* imatdisp.c      */
extern void ipmatdisp();                               /* ipmatdisp.c     */
extern int islastchar();                               /* islastch.c      */
extern int mkbkupfile();                               /* mkbkupfile.c    */
extern void loadmulticol();                            /* loadmulticol.c  */
extern void sortmulticol();                            /* loadmulticol.c  */
extern int unloadmulticol();                           /* loadmulticol.c  */
#ifdef sgi
extern void memchk();                                  /* memchk.c        */
#endif
extern int multicol();                                 /* multicol.c      */
extern int ncfscanf();                                 /* ncfscanf.c      */
extern char *ncgets();                                 /* ncgets.c        */
extern void outofmem();                                /* outofmem.c      */
extern int ps_accept();                                /* parsrch.c       */
extern int isany();                                    /* parsrch.c       */
extern PS *ps_make();                                  /* parsrch.c       */
extern PS *ps_duplicate();                             /* parsrch.c       */
extern void *ps_insert();                              /* parsrch.c       */
extern void ps_free();                                 /* parsrch.c       */
extern int ps_delete();                                /* parsrch.c       */
extern char *ps_search();                              /* parsrch.c       */
extern char *ps_beginwith();                           /* parsrch.c       */
extern PS_LEAF *ps_goto();                             /* parsrch.c       */
extern void ps_prtleaf();                              /* parsrch.c       */
extern void ps_prttree();                              /* parsrch.c       */
extern void ps_optimize();                             /* parsrch.c       */
extern void pfmatdisp();                               /* pfmatdisp.c     */
extern void pmatdisp();                                /* pmatdisp.c      */
extern void set_preprochar();                          /* prepro.c        */
extern int preprocess();                               /* prepro.c        */
extern void prmatdisp();                               /* prmatdisp.c     */
extern int initpsfkeys();                              /* psfkeys.c       */
extern int pstrlen();                                  /* pstrlen.c       */
extern char *ps_partialfirst();                        /* ps_partial.c    */
extern char *ps_partialnxt();                          /* ps_partial.c    */
extern void ps_clearpartial();                         /* ps_partial.c    */
extern void ps_srtinit();                              /* ps_iterate.c    */
extern void *ps_srtnxt();                              /* ps_iterate.c    */
extern void *ps_srtprv();                              /* ps_iterate.c    */
extern void ps_srtclear();                             /* ps_iterate.c    */
extern int putroman();                                 /* putroman.c      */
extern int qsortstrcmp();                              /* qsortstrcmp.c   */
extern char rawgetc();                                 /* rawgets.c       */
extern char *rawgets();                                /* rawgets.c       */
extern void rawungetc();                               /* rawgets.c       */
extern int rawinput();                                 /* rawinput.c      */
extern void ttyRestore();                              /* rawinput.c      */
extern void rdcolor();                                 /* rdcolor.c       */
extern void rdcputs();                                 /* rdcolor.c       */
extern void setup_screendata();                        /* rdcolor.c       */
extern void rgb2hsi();                                 /* rgb2hsi.c       */
extern char *snprt();                                  /* snprt.c         */
extern char *sprt();                                   /* sprt.c          */
extern char *srmtrblk();                               /* srmtrblk.c      */
extern int stcnarg();                                  /* stcnarg.c       */
extern int stcpm();                                    /* stcpm.c         */
extern int stcpma();                                   /* stcpm.c         */
extern int stmpma();                                   /* stmpma.c        */
extern int stmpm();                                    /* stmpma.c        */
extern char *stpblk();                                 /* stpblk.c        */
extern char *stprblk();                                /* stprblk.c       */
extern char *stpbrk();                                 /* stpbrk.c        */
extern char *stpchg();                                 /* stpchg.c        */
extern char *stpchres();                               /* stpchres.c      */
extern char *stpchr();                                 /* stpchr.c        */
extern char *stprchr();                                /* stprchr.c       */
extern char *stpend();                                 /* stpend.c        */
extern char *stpfmt();                                 /* stpfmt.c        */
extern char *stpnxt();                                 /* stpnxt.c        */
extern char *stprarg();                                /* stprarg.c       */
extern char *stptok();                                 /* stptok.c        */
extern int strctype();                                 /* strctype.c      */
extern char *stpskip();                                /* strctype.c      */
extern int whereis_uvar();                             /* strctype.c      */
extern int strfmtlen();                                /* strfmtlen.c     */
extern long strmdy();                                  /* strmdy.c        */
extern char *strnxtfmt();                              /* strnxtfmt.c     */
extern char *strprintf();                              /* strprintf.c     */
extern void strtoday();                                /* strtoday.c      */
extern char *strtolower();                             /* strtolower.c    */
extern char *strtoupper();                             /* strtoupper.c    */
extern int termtest();                                 /* termtest.c      */
extern char *texprotect();                             /* texprotect.c    */

#endif
#endif
