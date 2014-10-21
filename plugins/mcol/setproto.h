/* <setproto.h>: determine if prototype using or not
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#ifndef SETPROTO_H
# define SETPROTO_H

/* --------------------------------------------------------------------- */

# ifndef __PROTOTYPE__

#  ifdef vms
#   ifndef oldvms
#    define __PROTOTYPE__
#   endif

#  else

#   if defined(sgi)       || defined(apollo)    || defined(__STDC__)  || \
       defined(MCH_AMIGA) || defined(_AIX)      || defined(__MSDOS__) || \
	   defined(ultrix)    || defined(__DECC)    || defined(__alpha)   || \
	   defined(__osf__)   || defined(__WIN32__) || defined(__linux)
#    define __PROTOTYPE__
#   endif
#  endif
# endif

/* --------------------------------------------------------------------- */

#endif	/* SETPROTO_H */
