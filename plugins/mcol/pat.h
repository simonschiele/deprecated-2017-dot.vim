/* pat.h:
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 * PAT : the pattern is to be converted into a list of PATterns.
 * LPAT: logical PATterns (PATtern boolean algebra support)
 */
#ifndef PAT_H
#define PAT_H

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Typedefs:
 */
typedef struct PAT_str   PAT;
typedef struct LPAT_str LPAT;

/* -------------------------------------------------------------------------
 * Data Structures:
 */

struct PAT_str {
	char   c;			/* c: a single character pattern					*/
	char  *range;		/* range: list of 128 chars specifying range match	*/
	char **sfo;			/* sfo: subfield start ptr to stcmpma_mtch[].start entry	*/
	char **sfc;			/* sfc: subfield close ptr to stcmpma_mtch[].last entry	*/
	char   mcnt;

#ifdef oldvms
	int (*f)();
	int (*ff)();
#else
# if defined(__PROTOTYPE__) && !defined(ultrix)
	int (*f)(char *,PAT **,int *);	/* f: function used to determine match	*/
	int (*ff)(char *,PAT **,int *);	/* ff: used by bscan and fscan			*/
# else
	int (*f)();
	int (*ff)();
# endif
#endif

	int eb;				/* eb: ending/beginning test needed in addition to	*
						 *     a range test.  Four bits are used:			*
						 *     |~$|$|~^|^| (bits |4|3|2|1| )				*
						 *													*/
	int context;		/* context: used during range matching.  Context	*
						   matching required								*/
#ifdef DEBUG
	int isfo,isfc;		/* used by debugging to number subfields			*/
#endif
	PAT *nxt;			/* nxt: pointer to next PATtern						*/
	};

/* ------------------------------------------------------------------------- */

struct LPAT_str {
	int   id;			/* identifier for debugging							*/
	int   preclvl;		/* precedence level of token						*/
	char  op;			/* logical operator (& | ! p)						*/
	PAT  *pat;			/* beginning of a PATtern linked list (for stcmpm2)	*/
	LPAT *nxt;			/* LPAT tail-linked list support					*/
	LPAT *stknxt;		/* LPAT stack support								*/
	};

/* ------------------------------------------------------------------------- */

#ifdef __cplusplus
	}
#endif

#endif	/* PAT_H */
