/* sprt.c:
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 */
#include <stdio.h>
#include "xtdio.h"

/* -------------------------------------------------------------------------
 * Local Definitions:
 */
#ifdef DEBUG_TEST_SMALL
#define BUFSIZE  10
#define SFTY      2
#else
#define BUFSIZE 256
#define SFTY     20
#endif

/* ---------------------------------------------------------------------
 * Typedefs:
 */
typedef struct DYNBUF_str DYNBUF;

/* ---------------------------------------------------------------------
 * Structures:
 */
struct DYNBUF_str {
	char *buf;
	int   buflen;
	};

/* --------------------------------------------------------------------- */

/* sprt: this routine makes string characters all visible
 *       It has five internal buffers, so a printf statement can
 *       use it up to 5 times before unfortunate effects occur.
 *       Furthermore, the five buffers are dynamically sized so that
 *       only your hardware limits the string size that can be made
 *       visible.
 */
char *sprt(const void *vs)
{
char          *b;
char          *bsfty;
char          *s    = (char *) vs;
int            ic;
static DYNBUF  buf1 = {NULL,0};
static DYNBUF  buf2 = {NULL,0};
static DYNBUF  buf3 = {NULL,0};
static DYNBUF  buf4 = {NULL,0};
static DYNBUF  buf5 = {NULL,0};
static DYNBUF *buf  = &buf5;


/* allows up to four sprt()s in one function call */
if     (buf == &buf1) buf= &buf2;
else if(buf == &buf2) buf= &buf3;
else if(buf == &buf3) buf= &buf4;
else if(buf == &buf4) buf= &buf5;
else                  buf= &buf1;


if(!buf1.buf) {	/* initialization */
	buf1.buf= (char *) calloc((size_t) BUFSIZE,sizeof(char)); buf1.buflen= BUFSIZE;
	buf2.buf= (char *) calloc((size_t) BUFSIZE,sizeof(char)); buf2.buflen= BUFSIZE;
	buf3.buf= (char *) calloc((size_t) BUFSIZE,sizeof(char)); buf3.buflen= BUFSIZE;
	buf4.buf= (char *) calloc((size_t) BUFSIZE,sizeof(char)); buf4.buflen= BUFSIZE;
	buf5.buf= (char *) calloc((size_t) BUFSIZE,sizeof(char)); buf5.buflen= BUFSIZE;
	}

buf->buf[0] = '\0';
bsfty       = buf->buf + buf->buflen - SFTY;
if(((int) s) == 1 || ((int) s) == -1) {	/* common bad-pointer values */
	strcpy(buf->buf,"bad-ptr");
	}
else if(s) {
	for(b= buf->buf; *s && b < bsfty; ++s, b+= strlen(b)) {
		ic= (int) ((unsigned char) *s);
		if(ic < 31)        sprintf(b,"^%c",(char) (ic + 64));
		else if(ic >= 128) sprintf(b,"~%3d",ic);
		else {
			*b    = *s;
			*(b+1)= '\0';
			}
		b+= strlen(b);

		/* getting near end-of-buffer, re-allocate to a bigger buffer */
		if(b >= bsfty) {
			int blen;
			blen        = b - buf->buf;
			buf->buflen+= BUFSIZE;
			buf->buf= (char *) realloc(buf->buf,buf->buflen);
			bsfty        = buf->buf + buf->buflen - BUFSIZE;
			b            = buf->buf + blen;
			}
		}
	}
else strcpy(buf->buf,"null");

return buf->buf;
}

/* ===================================================================== */

/* --------------------------------------------------------------------- */

