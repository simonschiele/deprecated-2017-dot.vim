/* prototypes generated automatically by Dr. Chip's flist program
 * Fri Jan 12 10:38:46 EST 2001
 */
#ifdef __PROTOTYPE__
 
void error( int, char *, ...);                                                                                      /* error.c         */
FILE *fopenv(char *,char *,char *);                                                                                 /* fopenv.c        */
int ga_translate( void *, int, char *);                                                                             /* ga_translate.c  */
void getarg( int,  char **,  int,  PARMDEF *,  char **,  int (*)(char **,char **),  void (*)(int,PARMDEF *),        /* getarg.c        */
    void (*)(char *),  int,  char *);
void ga_usage(char **,int);                                                                                         /* getarg.c        */
void ga_dofilewild( void (*)(), char *);                                                                            /* getarg.c        */
int ga_haswild(char *);                                                                                             /* getarg.c        */
void ga_dofilewild( void (*)(), char *);                                                                            /* getarg.c        */
int ga_haswild(char *);                                                                                             /* getarg.c        */
void ga_dofilewild( void (*)(), char *);                                                                            /* getarg.c        */
int ga_haswild(char *);                                                                                             /* getarg.c        */
void ga_dofilewild( void (*)(), char *);                                                                            /* getarg.c        */
int ga_haswild(char *);                                                                                             /* getarg.c        */
int ga_findfirst( char *, char **);                                                                                 /* getarg.c        */
int ga_findnext(char **);                                                                                           /* getarg.c        */
int spawn( int, char **);                                                                                           /* getarg.c        */
void ga_dofilewild( void (*)(), char *);                                                                            /* getarg.c        */
int ga_haswild(char *);                                                                                             /* getarg.c        */
void ga_dofilewild( void (*)(char *), char *);                                                                      /* getarg.c        */
int ga_haswild(char *);                                                                                             /* getarg.c        */
int main( int, char **);                                                                                            /* mcol.c          */
int options( char **, char **);                                                                                     /* mcol.c          */
void fprior(int,PARMDEF *);                                                                                         /* mcol.c          */
void mcol(char *);                                                                                                  /* mcol.c          */
void rendertst(char *,int);                                                                                         /* mcol.c          */
int multicol( int, char **, int, char *, FILE *);                                                                   /* multicol.c      */
void outofmem(void *,char *,...);                                                                                   /* outofmem.c      */
int pstrlen(int,char *);                                                                                            /* pstrlen.c       */
void rdcolor(void);                                                                                                 /* rdcolor.c       */
void rdcputs(char *,FILE *);                                                                                        /* rdcolor.c       */
void setup_screendata(char *);                                                                                      /* rdcolor.c       */
char *sprt(const void *);                                                                                           /* sprt.c          */
char *srmtrblk(char *);                                                                                             /* srmtrblk.c      */
char *stpblk(char *);                                                                                               /* stpblk.c        */
char *stpbrk(char *,char *);                                                                                        /* stpbrk.c        */
char *stpnxt( char *,  char *);                                                                                     /* stpnxt.c        */
char *strprintf(char *,...);                                                                                        /* strprintf.c     */
 
#else	/* __PROTOTYPE__ */
 
extern void error();                                                                                                /* error.c         */
extern FILE *fopenv();                                                                                              /* fopenv.c        */
extern int ga_translate();                                                                                          /* ga_translate.c  */
extern void getarg();                                                                                               /* getarg.c        */
extern void ga_usage();                                                                                             /* getarg.c        */
extern void ga_dofilewild();                                                                                        /* getarg.c        */
extern int ga_haswild();                                                                                            /* getarg.c        */
extern void ga_dofilewild();                                                                                        /* getarg.c        */
extern int ga_haswild();                                                                                            /* getarg.c        */
extern void ga_dofilewild();                                                                                        /* getarg.c        */
extern int ga_haswild();                                                                                            /* getarg.c        */
extern void ga_dofilewild();                                                                                        /* getarg.c        */
extern int ga_haswild();                                                                                            /* getarg.c        */
extern int ga_findfirst();                                                                                          /* getarg.c        */
extern int ga_findnext();                                                                                           /* getarg.c        */
extern int spawn();                                                                                                 /* getarg.c        */
extern void ga_dofilewild();                                                                                        /* getarg.c        */
extern int ga_haswild();                                                                                            /* getarg.c        */
extern void ga_dofilewild();                                                                                        /* getarg.c        */
extern int ga_haswild();                                                                                            /* getarg.c        */
extern int main();                                                                                                  /* mcol.c          */
extern int options();                                                                                               /* mcol.c          */
extern void fprior();                                                                                               /* mcol.c          */
extern void mcol();                                                                                                 /* mcol.c          */
extern void rendertst();                                                                                            /* mcol.c          */
extern int multicol();                                                                                              /* multicol.c      */
extern void outofmem();                                                                                             /* outofmem.c      */
extern int pstrlen();                                                                                               /* pstrlen.c       */
extern void rdcolor();                                                                                              /* rdcolor.c       */
extern void rdcputs();                                                                                              /* rdcolor.c       */
extern void setup_screendata();                                                                                     /* rdcolor.c       */
extern char *sprt();                                                                                                /* sprt.c          */
extern char *srmtrblk();                                                                                            /* srmtrblk.c      */
extern char *stpblk();                                                                                              /* stpblk.c        */
extern char *stpbrk();                                                                                              /* stpbrk.c        */
extern char *stpnxt();                                                                                              /* stpnxt.c        */
extern char *strprintf();                                                                                           /* strprintf.c     */
 
#endif	/* __PROTOTYPE__ */
