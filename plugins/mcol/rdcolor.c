/* rdcolor.c: this program initializes color/printer variables using a
 *   rdcolor.dat file if it exists.  Otherwise, default values are used.
 *   The <rdcolor.dat> file uses the following format:
 *	color ...<CR>
 *   where the ellipsis is the escape sequence to be used for the "color".
 *   The following characters have special meaning when preceded by a
 *   backslash:
 *	     \e     =>      escape character
 *	     \f     =>      formfeed character
 *	     \h     =>      backspace character
 *	     \n     =>      newline character
 *	     \t     =>      tab character
 *	     \A - \Z=>      Associated control characters
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#include <stdio.h>
#include <ctype.h>
#include "xtdio.h"

#if defined(AMIGA) || defined(MCH_AMIGA) || defined(LATTICE)
# ifndef amiga
#  define amiga
# endif
# include <devices/conunit.h>
# include <fcntl.h>
# include <dos/dosextens.h>
# include <clib/dos_protos.h>
# include <clib/exec_protos.h>
# ifndef AZTEC_C
   static long dos_packet(struct MsgPort *,long,long);
# endif

/*
 * This is a routine for setting a given stream to raw or cooked mode on the
 * Amiga . This is useful when you are using Lattice C to produce programs
 * that want to read single characters with the "getch()" or "fgetc" call.
 *
 * Written : 18-Jun-87 By Chuck McManis.
 */
#define MP(xx)  ((struct MsgPort *)((struct FileHandle *) (BADDR(xx)))->fh_Type)

static BPTR				raw_in  = (BPTR)NULL;
static BPTR				raw_out = (BPTR)NULL;
#endif	/* amiga stuff */

#ifdef sgi
# include <sys/termio.h>
# include <time.h>
# include <signal.h>
#endif

#ifdef unix
# if defined(ESIX) || defined(M_UNIX) && !defined(SCO)
#  ifdef SIGWINCH
#   undef SIGWINCH
#  endif
#  ifdef TIOCGWINSZ
#   undef TIOCGWINSZ
#  endif
# endif

# if defined(SIGWINDOW) && !defined(SIGWINCH)    /* hpux 9.01 has it */
#  define SIGWINCH SIGWINDOW
# endif
#endif

#ifdef vms
# include    <unixio.h>
# include    <unixlib.h>
# include    <signal.h>
# include    <file.h>
# include    <ssdef.h>
# include    <descrip.h>
# include    <libclidef.h>
# include    <lnmdef.h>
# include    <psldef.h>
# include    <prvdef.h>
# include    <dvidef.h>
# include    <dcdef.h>
# include    <stsdef.h>
# include    <iodef.h>
# include    <ttdef.h>
# include    <tt2def.h>
# include    <rms.h>
# include    <string.h>
# include    <starlet.h>
# include    <lib$routines.h>
#endif

#ifdef MSDOS
# define msdos
# define __COLORS		/* prevents Borland C's <conio.h> from enum'ing colors */
# include <conio.h>
#endif

#ifdef __WIN32__
# include <windows.h>
#endif

/* -----------------------------------------------------------------------
 * Definitions:
 */
#define LINESIZE 80
#define TERMSIZE 20

/* -----------------------------------------------------------------------
 * Local Data Structures
 */
struct colorstr {  /* color data structure          */
	char **color;  /* points to a color variable    */
	char  *name;   /* gives a name to a color       */
	char  *defalt; /* default color string: nothing */
	};

/* -----------------------------------------------------------------------
 * Local Data:
 */
static struct colorstr colors[]={
	  {&BLACK,		"BLACK",		"\0"},
	  {&RED,		"RED",			"\0"},
	  {&GREEN,		"GREEN",		"\0"},
	  {&YELLOW,		"YELLOW",		"\0"},
	  {&BLUE,		"BLUE",			"\0"},
	  {&MAGENTA,	"MAGENTA",		"\0"},
	  {&CYAN,		"CYAN",			"\0"},
	  {&WHITE,		"WHITE",		"\0"},

	  {&UBLACK,		"UBLACK",		"\0"},
	  {&URED,		"URED",			"\0"},
	  {&UGREEN,		"UGREEN",		"\0"},
	  {&UYELLOW,	"UYELLOW",		"\0"},
	  {&UBLUE,		"UBLUE",		"\0"},
	  {&UMAGENTA,	"UMAGENTA",		"\0"},
	  {&UCYAN,		"UCYAN",		"\0"},
	  {&UWHITE,		"UWHITE",		"\0"},

	  {&RVBLACK,	"RVBLACK",		"\0"},
	  {&RVRED,		"RVRED",		"\0"},
	  {&RVGREEN,	"RVGREEN",		"\0"},
	  {&RVYELLOW,	"RVYELLOW",		"\0"},
	  {&RVBLUE,		"RVBLUE",		"\0"},
	  {&RVMAGENTA,	"RVMAGENTA",	"\0"},
	  {&RVCYAN,		"RVCYAN",		"\0"},
	  {&RVWHITE,	"RVWHITE",		"\0"},

	  {&ITBLACK,	"ITBLACK",		"\0"},
	  {&ITRED,		"ITRED",		"\0"},
	  {&ITGREEN,	"ITGREEN",		"\0"},
	  {&ITYELLOW,	"ITYELLOW",		"\0"},
	  {&ITBLUE,		"ITBLUE",		"\0"},
	  {&ITMAGENTA,	"ITMAGENTA",	"\0"},
	  {&ITCYAN,		"ITCYAN",		"\0"},
	  {&ITWHITE,	"ITWHITE",		"\0"},

	  {&BOLDBLACK,	"BOLDBLACK",	"\0"},
	  {&BOLDRED,	"BOLDRED",		"\0"},
	  {&BOLDGREEN,	"BOLDGREEN",	"\0"},
	  {&BOLDYELLOW,	"BOLDYELLOW",	"\0"},
	  {&BOLDBLUE,	"BOLDBLUE",		"\0"},
	  {&BOLDMAGENTA,"BOLDMAGENTA",	"\0"},
	  {&BOLDCYAN,	"BOLDCYAN",		"\0"},
	  {&BOLDWHITE,	"BOLDWHITE",	"\0"},

	  {&BOLD,		"BOLD",			"\0"},
	  {&NRML,		"NRML",			"\0"},
	  {&PYELLOW,	"PYELLOW",		"\0"},
	  {&PRED,		"PRED",			"\0"},
	  {&PCYAN,		"PCYAN",		"\0"},
	  {&PBLACK,		"PBLACK",		"\0"},
	  {&CLEAR,		"CLEAR",		"\0"}
	  };
static int ncolor      = sizeof(colors)/sizeof(struct colorstr);
char  *colorfile[]     = {"rdcolor.dat","color.dat"};
static int ncolorfile  = sizeof(colorfile)/sizeof(char *);
static int rdcolor_done= 0;	/* has rdcolor been called? */

/* -----------------------------------------------------------------------
 * Source Code:
 */

/* rdcolor: read the <rdcolor.dat> file */
void rdcolor(void)
{
FILE *fp                         = NULL;
char *cmd                        = NULL;
char *new                        = NULL;
char *lterm                      = NULL;
char  line[LINESIZE];
char  color[LINESIZE];
char  newdef[LINESIZE+LINESIZE];
char *term                       = NULL;
int   icolor;
int   foundterm;


/* indicate that rdcolor() has been called */
rdcolor_done= 1;

/* attempt to locate correct terminal definition */
#ifdef unix
term= getenv("TERM");
#endif
#ifdef LATTICE
term= "TI";
#endif
#ifdef DESMET
term= "TI";
#endif
#ifdef AZTEC_C
term= "Amiga";
#endif
#ifdef vms
term= getenv("TERM");
if(!term) term= "vms";
#endif
#ifdef MSDOS
 term="msdos";
#else
# if defined(__WIN32__)
  term="win32";
# elif defined(msdos)
  term="msdos";
# endif
#endif

/* set up screen height and width */
setup_screendata(term);

/* set up default colors */
for(icolor= 0; icolor < ncolor; ++icolor) *(colors[icolor].color)= colors[icolor].defalt;

/* attempt to open <rdcolor.dat> file */
for(icolor= 0; icolor < ncolorfile; ++icolor) {
	fp= fopenv(colorfile[icolor],"r","ChipData");
	if(fp) break;
	}

/* set up default RD_... colors */
RD_BLACK  = BLACK;
RD_RED    = RED;
RD_GREEN  = GREEN;
RD_YELLOW = YELLOW;
RD_BLUE   = BLUE;
RD_MAGENTA= MAGENTA;
RD_CYAN   = CYAN;
RD_WHITE  = WHITE;
RD_CLEAR  = CLEAR;

if(!fp) { /* use default values */
	return;
	}

if(term) {  /* search for terminal entry in <rdcolor.dat> file */
	foundterm= 0;
	while(fgets(line,LINESIZE,fp)) if(!isspace(line[0])) {
		srmtrblk(line);
		for(lterm= (char *) strtok(line,"|:"); lterm;
		    lterm= (char *) strtok((char *) NULL,"|:")) {
			lterm= stpblk(lterm);
			srmtrblk(lterm);
			if(!strcmp(lterm,term)) {
				foundterm= 1;
				break;
				}
			}	/* term|term|term|term: search */
		if(foundterm) break;
		}

	if(!foundterm) { /* couldn't find terminal entry */
		fclose(fp);
		return;
		}
	}

/* read color & use cmd sequence */
while(fgets(line,LINESIZE,fp)) {

	/* skip blank lines */
	for(cmd= line; *cmd; ++cmd) if(!isspace(*cmd)) break;
	if(!*cmd) continue;
	if(cmd == line) break; /* finished reading in terminal def'n */

	/* if first non-blank character is a "#", skip it (comment) */
	if(*cmd == '#') continue;

	/* get the color */
	sscanf(cmd,"%s",color);

	/* skip to first white space character */
	for(; *cmd && !isspace(*cmd); ++cmd);
	cmd[strlen(cmd) - 1]= '\0';	/* remove newline character */

	/* skip over tabs following colorname */
	while(*cmd == '\t') ++cmd;

	/* identify color (if known) */
	for(icolor= 0; icolor < ncolor; ++icolor) if(!strcmp(colors[icolor].name,color)) break;
	if(icolor >= ncolor) { /* unknown color */
		error(XTDIO_WARNING, "(rdcolor) ignoring unknown color <%s> in <%s>\n", color,colorfile);
		continue;
		}


	/* copy cmd (new color) over to newdef (new definition), making
	 * appropriate changes due to backslashes
	 */
	for(new= newdef; *cmd; ++cmd,++new) {
		if(*cmd == '\\') {
			switch(*++cmd) {
			case 'e' : /* escape character		*/
				*new= '\033';
				break;
			case 'f' : /* formfeed character	*/
				*new= '\f';
				break;
			case 'h' : /* backspace character	*/
				*new= (char) 8;
				break;
			case 'n' : /* newline character		*/
				*new= '\n';
				break;
			case 't' : /* tab character		*/
				*new= '\t';
				break;
			default:   /* handles A-Z and other	*/
				if('A' <= *cmd && *cmd <= 'Z') *new= *cmd - 64;
				else *new= *cmd;
				break;
				}
			}
		else *new= *cmd;
		}
	*new= '\0'; /* terminate new definition with null byte */

	/* allocate memory and then set color to colorfile-defined value */
	*colors[icolor].color= (char *) calloc((size_t) strlen(newdef)+1,sizeof(char));
	if(newdef[0]) strcpy(*colors[icolor].color,newdef);
	else          *colors[icolor].color= "\0";
	}

/* close the colorfile */
fclose(fp);

/* set up RD_... colors */
RD_BLACK  = BLACK;
RD_RED    = RED;
RD_GREEN  = GREEN;
RD_YELLOW = YELLOW;
RD_BLUE   = BLUE;
RD_MAGENTA= MAGENTA;
RD_CYAN   = CYAN;
RD_WHITE  = WHITE;
RD_CLEAR  = CLEAR;


}

/* ----------------------------------------------------------------------- */

/* rdcputs: read color's put-string function.  Normally, rdcputs acts exactly
 *  like fputs, except that "\255X#" strings are translated to appropriate
 *  colors.
 */
void rdcputs(char *s,FILE *fp)
{
int icolor;


if(*s == '\255' && *(s+1) == 'X') { /* translate */
	if(rdcolor_done) {
		/* only try interpreting this if rdcolor() has been called */
		sscanf(s+2,"%d",&icolor);
		fputs(*colors[icolor].color,fp);
		}
	}
else {
	fputs(s,fp);
	}

}

/* --------------------------------------------------------------------- */

/* setup_screendata: sets up global variables screenheight and screenwidth
 *  It generally prefers to query the o/s, but if that fails/is unavailable,
 *  it queries for environment variables SCREENHEIGHT and SCREENWIDTH,
 *  then it finally just leaves the two variables at their default values,
 *  set in <xvar.c>
 */
void setup_screendata(char *term)
{
char *scrw  = NULL;
int   old_sh;
int   old_sw;


/* set up screenheight and screenwidth */
old_sh       = screenheight;
old_sw       = screenwidth;
screenheight = screenwidth   = 0;

#ifdef __EMX__
	{
	int s[2];
	_scrsize(s);
	screenheight= s[1];
	screenwidth = s[0];
	}

#else	/* __EMX__ */

/* attempt to use ioctl */
# if defined(TIOCGWINSZ)
	{
	struct winsize ws;
	if(ioctl(0,TIOCGWINSZ,&ws) == 0) {
		screenwidth = ws.ws_col;
		screenheight= ws.ws_row;
		}
	}
# elif defined(TIOCGSIZE)
	{
	struct ttysize ts;
	if(ioctl(0,TIOCGSIZE,&ts) == 0) {
		screenwidth = ts.ts_cols;
		screenheight= ts.ts_lines;
		}
	}
# endif	/* TIOCGWINSZ - TIOCGSIZE */
#endif	/* __EMX__ */

#if defined(HAVE_TGETENT) && defined(unix)
# define TBUFSZ 1024
if(!screenheight || !screenwidth) {
	char tbuf[TBUFSZ];
	if(term[0] && tgetent(tbuf,term) > 0) {
		if(screenheight == 0) screenheight= tgetnum("li");
		if(screenwidth  == 0) screenwidth = tgetnum("co");
		}
	}
#endif

#ifdef amiga
	{
	struct ConUnit	            *conUnit        = NULL;
	char			             id_a[sizeof(struct InfoData) + 3];
	int                          dos_pkt_ret;
	struct InfoData             *id            = NULL;
	struct Window               *wb_window     = NULL;
	static struct IntuitionBase *IntuitionBase = NULL;
	static struct Library       *DosBase       = NULL;

	/* insure longword alignment */
 	id            = (struct InfoData *)(((long)id_a + 3L) & ~3L);
 	raw_out       = Output();
 	IntuitionBase = (struct IntuitionBase *) OpenLibrary((UBYTE *) "intuition.library", 0L);
	if(IntuitionBase) DosBase= OpenLibrary((UBYTE *) "dos.library", 37L);

	if(IntuitionBase && DosBase) {
		dos_pkt_ret= dos_packet(MP(raw_out), (long)ACTION_DISK_INFO, ((ULONG) id) >> 2);
		wb_window  = (struct Window *)id->id_VolumeNode;


		if(dos_pkt_ret != 0 && wb_window && (id->id_InUse != (BPTR)NULL)) {
			conUnit = (struct ConUnit *) ((struct IOStdReq *) id->id_InUse)->io_Unit;

			/* get window size */
			screenheight = conUnit->cu_YMax + 1;
			screenwidth  = conUnit->cu_XMax + 1;
			if (screenheight < 0 || screenheight > 200) { /* cannot be an amiga window */
				screenheight = 0;
				screenwidth  = 0;
				}
			}
		}

	/* close down connections to resources */
	if(DosBase)       CloseLibrary((struct Library *) DosBase);
	if(IntuitionBase) CloseLibrary((struct Library *) IntuitionBase);
	}
#endif

#ifdef vms
# define TTSIZ	1024
	{
	struct {
	    char         class;
	    char         type;
	    short        width;
	    union {
			struct {
			    char _basic[3];
			    char length;
				}    y;
			int      basic;
	    	}        x;
	    int          extended;
		} tmode;
	long  my_status;
	DESC  odsc;
	short iochan;
	char  ttbuf[TTSIZ];
	short iosb[4];		/* IO status block	*/
	char *TT;

	TT= getenv("TT");
	if(TT) {	/* found out the hard way -- getenv more or less doesn't work under vms
				 * when run/detach is used.
				 */
		strcpy(ttbuf,getenv("TT"));
		odsc.dsc$b_dtype   = DSC$K_DTYPE_T;
		odsc.dsc$b_class   = DSC$K_CLASS_S;
		odsc.dsc$a_pointer = ttbuf;
		odsc.dsc$w_length  = ttbuf[0]? strlen(ttbuf) : 0;

		sys$assign(&odsc,&iochan,0,0);

		my_status= sys$qiow(0,iochan,IO$_SENSEMODE,iosb,0,0,&tmode,sizeof(tmode),0,0,0,0);
		if(my_status == SS$_NORMAL && (iosb[0] & 0xFFFF) == SS$_NORMAL) {
			screenwidth  = tmode.width;
			screenheight = tmode.x.y.length;
			}
		}
	}
#endif

#if defined(msdos) && !defined(__WIN32__)
	{
	struct text_info ti;

	gettextinfo(&ti);
	screenheight= ti.screenheight;
	screenwidth = ti.screenwidth;
	}
#endif

#ifdef __WIN32__
	{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		screenheight = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;
		screenwidth  = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
		}
	}
#endif

/* if all else fails, check the environment for SCREENWIDTH and SCREENHEIGHT */
if(screenwidth == 0) {
	scrw= getenv("SCREENWIDTH");
	if(!scrw) scrw= getenv("COLUMNS");
	if(scrw) {
		sscanf(scrw,"%d",&screenwidth);	/* screenwidth is in <xvar.c> */
		}
	if(screenwidth == 0) {
		screenwidth= old_sw;
		}
	}

if(screenheight == 0) {
	scrw= getenv("SCREENHEIGHT");
	if(!scrw) scrw= getenv("LINES");
	if(scrw) {
		sscanf(scrw,"%d",&screenheight);	/* screenheight is in <xvar.c> */
		}
	if(screenheight == 0) {
		screenheight= old_sh;
		}
	}


}

/* -----------------------------------------------------------------------
 * Debug Source Code:
 */


/* ----------------------------------------------------------------------- */
