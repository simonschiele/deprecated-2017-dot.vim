/* rdcolor.h: this file specifies that all colors are actually pointers to
 *  color strings.  It is expected that the function "rdcolor()" will
 *  be used to initialize the colors.  "rdcolor()" examines a colorfile
 *  called "color.dat" for color strings: color ...<CR> where the ellipsis
 *  is the desired escape string.  The default value of such color strings
 *  is set for a color ASCII monitor (8 colors) and the IDS Prism printer.
 *
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#ifndef RDCOLOR_H
#define RDCOLOR_H

#ifdef oldvms
extern char *BLACK;
extern char *RED;
extern char *GREEN;
extern char *YELLOW;
extern char *BLUE;
extern char *MAGENTA;
extern char *CYAN;
extern char *WHITE;
#else
# if    !defined(__GL_GL_H__) && !defined(VOGLE_H)   && \
        !defined(VOGL)        && !defined(__CONIO_H)
extern char *BLACK;
extern char *RED;
extern char *GREEN;
extern char *YELLOW;
extern char *BLUE;
extern char *MAGENTA;
extern char *CYAN;
extern char *WHITE;
# endif
#endif

extern char *RD_BLACK;		/* same as BLACK		*/
extern char *RD_RED;		/* same as RED			*/
extern char *RD_GREEN;		/* same as GREEN		*/
extern char *RD_YELLOW;		/* same as YELLOW		*/
extern char *RD_BLUE;		/* same as BLUE			*/
extern char *RD_MAGENTA;	/* same as MAGENTA		*/
extern char *RD_CYAN;		/* same as CYAN			*/
extern char *RD_WHITE;		/* same as WHITE		*/
extern char *RD_CLEAR;		/* same as CLEAR		*/

extern char *UBLACK;		/* underline + color	*/
extern char *URED;
extern char *UGREEN;
extern char *UYELLOW;
extern char *UBLUE;
extern char *UMAGENTA;
extern char *UCYAN;
extern char *UWHITE;

extern char *RVBLACK;		/* reverse video + color*/
extern char *RVRED;
extern char *RVGREEN;
extern char *RVYELLOW;
extern char *RVBLUE;
extern char *RVMAGENTA;
extern char *RVCYAN;
extern char *RVWHITE;

extern char *ITBLACK;		/* italic + color		*/
extern char *ITRED;
extern char *ITGREEN;
extern char *ITYELLOW;
extern char *ITBLUE;
extern char *ITMAGENTA;
extern char *ITCYAN;
extern char *ITWHITE;

extern char *BOLDBLACK;		/* bold + color			*/
extern char *BOLDRED;
extern char *BOLDGREEN;
extern char *BOLDYELLOW;
extern char *BOLDBLUE;
extern char *BOLDMAGENTA;
extern char *BOLDCYAN;
extern char *BOLDWHITE;

#ifdef oldvms
extern char *CLEAR;
#else
# if !defined(__GL_GL_H__) && !defined(VOGLE_H)
#  ifndef CLEAR
extern char *CLEAR;
#  endif
# endif
#endif

extern char *BOLD;
extern char *NRML;
extern char *PYELLOW;
extern char *PRED;
extern char *PCYAN;
extern char *PBLACK;

/* for rdcputs's benefit... */
#define XBLACK			"\255X0"
#define XRED			"\255X1"
#define XGREEN			"\255X2"
#define XYELLOW			"\255X3"
#define XBLUE			"\255X4"
#define XMAGENTA		"\255X5"
#define XCYAN			"\255X6"
#define XWHITE			"\255X7"
#define XUBLACK			"\255X8"
#define XURED			"\255X9"
#define XUGREEN			"\255X10"
#define XUYELLOW		"\255X11"
#define XUBLUE			"\255X12"
#define XUMAGENTA		"\255X13"
#define XUCYAN			"\255X14"
#define XUWHITE			"\255X15"
#define XRVBLACK		"\255X16"
#define XRVRED			"\255X17"
#define XRVGREEN		"\255X18"
#define XRVYELLOW		"\255X19"
#define XRVBLUE			"\255X20"
#define XRVMAGENTA		"\255X21"
#define XRVCYAN			"\255X22"
#define XRVWHITE		"\255X23"
#define XITBLACK		"\255X24"
#define XITRED			"\255X25"
#define XITGREEN		"\255X26"
#define XITYELLOW		"\255X27"
#define XITBLUE			"\255X28"
#define XITMAGENTA		"\255X29"
#define XITCYAN			"\255X30"
#define XITWHITE		"\255X31"
#define XBOLDBLACK		"\255X32"
#define XBOLDRED		"\255X33"
#define XBOLDGREEN		"\255X34"
#define XBOLDYELLOW		"\255X35"
#define XBOLDBLUE		"\255X36"
#define XBOLDMAGENTA	"\255X37"
#define XBOLDCYAN		"\255X38"
#define XBOLDWHITE		"\255X39"
#define XBOLD			"\255X40"
#define XNRML			"\255X41"
#define XPYELLOW		"\255X42"
#define XPRED			"\255X43"
#define XPCYAN			"\255X44"
#define XPBLACK			"\255X45"
#define XCLEAR			"\255X46"
#endif
