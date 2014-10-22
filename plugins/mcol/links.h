/* Links.h: this file defines some useful macros for generating
 *  linked lists.  Linked lists are assumed to have one or sometimes
 *  both the members "nxt" and "prv".  The user must initialize the
 *  head/tail pointers (of type (struct structure *) ) to NULL.
 *
 *  In addition, just because they're so useful, stralloc() assigns new memory
 *  of the appropriate length for the string pointed to by "s" and copies
 *  the string to that new memory, and alloc(structure) allocates and casts
 *  memory for a structure.
 *
 * Copyright  August 25, 1999: Charles E. Campbell, Jr. -- see <Copyright> file
 *
 *  ====================================================================
 *
 *                                                            New Structure   Required
 *  Macro                                                          At         Members    Uses
 *  -----                                                     -------------   --------   ----
 *
 * LINKAGE, ALLOCATION, DE-ALLOCATION:------------------------------------------------
 *    circular_link(structure,tail,nxt,prv,fail_msg)          tail            nxt prv   malloc
 *    double_link(structure,head,tail,fail_msg)               tail            nxt prv   malloc
 *    head_link(structure,head,fail_msg)                      head            nxt       malloc
 *    insert_link(structure,head,tail,before,fail_msg)        before->nxt               malloc
 *    tail_link(structure,head,tail,fail_msg)                 tail            nxt       malloc
 *
 *    delete_circular_link(str,tail,nxt,prv)                                  nxt prv   free
 *    delete_double_link(structure,str,head,tail)                             nxt prv   free
 *    delete_head_link(structure,head)                                        nxt       free
 *
 * LINK HANDLING ONLY:----------------------------------------------------------------
 *    move_double_link(structure,str,oldhd,oldtl,newhd,newtl) newtl
 *    only_circular_link(structure,newstr,tail,nxt,prv)       tail            nxt prv
 *    only_double_link(structure,newstr,head,tail)            tail            nxt prv
 *    only_head_link(structure,newstr,head)                   head            nxt
 *    only_tail_link(structure,newstr,head,tail)              tail            nxt
 *
 *    only_delete_circular_link(str,tail,nxt,prv)                             nxt prv   free
 *    only_delete_double_link(structure,str,head,tail)                        nxt prv   free
 *    only_delete_head(structure,head)                                        nxt       free
 *
 * C++ ONLY, USES NEW/DELETE:---------------------------------------------------------
 *    CircularLink(structure,tail,nxt,prv,fail_msg)          tail            nxt prv    new
 *    DoubleLink(structure,head,tail,fail_msg)               tail            nxt prv    new
 *    HeadLink(structure,head,fail_msg)                      head            nxt        new
 *    InsertLink(structure,head,tail,before,fail_msg)        before->nxt                new
 *    TailLink(structure,head,tail,fail_msg)                 tail            nxt        new
 *
 *    DeleteCircularLink(s,tail,nxt,prv)                                     nxt prv    delete
 *    DeleteDoubleLink(structure,s,head,tail)                                nxt prv    delete
 *    DeleteHead(structure,head)                                             nxt        delete
 *
 * ADDITIONAL USEFUL MACROS:----------------------------------------------------------
 *    stralloc(ptr,str,fail_msg)                              allocates a string        malloc
 *    alloc(structure)                                        allocates a structure     malloc
 */

#ifndef LINKS_H
#define LINKS_H

#if defined(MCH_AMIGA) || defined(msdos) || defined(__BORLANDC__)
typedef char *caddr_t;
#else
# ifdef vms
#  include <socket.h>
# else
#  include <sys/types.h>
# endif
#endif

/* --------------------------------------------------------------------- */

/* double_link: handles the generation of doubly linked lists.  Note that
 *   each structure is assumed to have members "nxt" and "prv".
 *   The new member becomes "tail" - ie. oldest is first in the linked list,
 *   the newest is last.
 */
#define double_link(structure,head,tail,fail_msg) {               \
	structure *newstr;                                            \
	newstr= (structure *) malloc(sizeof(structure));              \
	outofmem((void *) newstr,"%s\n",fail_msg);                    \
	if(tail) (tail)->nxt= newstr;                                 \
	else     head       = newstr;                                 \
	newstr->prv= tail;                                            \
	newstr->nxt= (structure *) NULL;                              \
	tail       = newstr;                                          \
	}
#define delete_double_link(structure,str,head,tail) {             \
	structure *old= str;                                          \
	if(old->prv) old->prv->nxt= old->nxt;                         \
	else         head         = old->nxt;                         \
	if(old->nxt) old->nxt->prv= old->prv;                         \
	else         tail         = old->prv;                         \
	free((char *) old);                                           \
	}
# define only_double_link(structure,newstr,head,tail) {           \
	if(tail) (tail)->nxt= newstr;                                 \
	else     head       = newstr;                                 \
	newstr->prv= tail;                                            \
	newstr->nxt= (structure *) NULL;                              \
	tail       = newstr;                                          \
	}
# define only_delete_double_link(structure,str,head,tail) {       \
	structure *old= str;                                          \
	if(old->prv) old->prv->nxt= old->nxt;                         \
	else         head         = old->nxt;                         \
	if(old->nxt) old->nxt->prv= old->prv;                         \
	else         tail         = old->prv;                         \
	}
#ifdef __cplusplus
# define DoubleLink(structure,head,tail,fail_msg) {               \
	structure *newstr;                                            \
	newstr= new structure;                                        \
	outofmem((void *) newstr,"%s\n",fail_msg);                    \
	if(tail) (tail)->nxt= newstr;                                 \
	else     head       = newstr;                                 \
	newstr->prv= tail;                                            \
	newstr->nxt= (structure *) NULL;                              \
	tail       = newstr;                                          \
	}
# define DeleteDoubleLink(structure,str,head,tail) {              \
	structure *old= str;                                          \
	if(old->prv) old->prv->nxt= old->nxt;                         \
	else         head         = old->nxt;                         \
	if(old->nxt) old->nxt->prv= old->prv;                         \
	else         tail         = old->prv;                         \
	delete old;                                                   \
	}
#endif

/* insert_link: handles the generation and linking (doubly linked list)
 * of a structure, *after* an arbitrary "before structure".  It will also
 * link  *before* the head of the list if the "before" is null.
 */
#define insert_link(structure,head,tail,before,fail_msg) {        \
	structure *newstr;                                            \
	newstr= (structure *) malloc(sizeof(structure));              \
	outofmem(newstr,"%s\n",fail_msg);                             \
	newstr->prv= before;                                          \
	if(!(before)) {	/* insert in front of list */                 \
		newstr->nxt   = (head);                                   \
		newstr->prv   = NULL;                                     \
		if(head) (head)->prv= newstr;                             \
		else     (tail)     = newstr;                             \
		(head)= newstr;                                           \
		}                                                         \
	else {                                                        \
		newstr->nxt= (before)->nxt;                               \
		newstr->prv= before;                                      \
		if((before)->nxt) (before)->nxt->prv= newstr;             \
		else              (tail)            = newstr;             \
		(before)->nxt= newstr;                                    \
		}                                                         \
	}
# define only_insert_link(structure,newstr,head,tail,before) {    \
	newstr->prv= before;                                          \
	if(!(before)) {	/* insert in front of list */                 \
		newstr->nxt   = (head);                                   \
		newstr->prv   = NULL;                                     \
		if(head) (head)->prv= newstr;                             \
		else     (tail)     = newstr;                             \
		(head)= newstr;                                           \
		}                                                         \
	else {                                                        \
		newstr->nxt= (before)->nxt;                               \
		newstr->prv= before;                                      \
		if((before)->nxt) (before)->nxt->prv= newstr;             \
		else              (tail)            = newstr;             \
		(before)->nxt= newstr;                                    \
		}                                                         \
	}
#ifdef __cplusplus
# define InsertLink(structure,head,tail,before,fail_msg) {        \
	structure *newstr;                                            \
	newstr= new structure;                                        \
	outofmem(newstr,"%s\n",fail_msg);                             \
	newstr->prv= before;                                          \
	if(!(before)) {	/* insert in front of list */                 \
		newstr->nxt   = (head);                                   \
		newstr->prv   = NULL;                                     \
		if(head) (head)->prv= newstr;                             \
		else     (tail)     = newstr;                             \
		(head)= newstr;                                           \
		}                                                         \
	else {                                                        \
		newstr->nxt= (before)->nxt;                               \
		newstr->prv= before;                                      \
		if((before)->nxt) (before)->nxt->prv= newstr;             \
		else              (tail)            = newstr;             \
		(before)->nxt= newstr;                                    \
		}                                                         \
	}
#endif

/* moves a double link member from any arbitrary place in the
 *  old doubly linked list to the end of a new one
 */
#define move_double_link(structure,str,oldhd,oldtl,newhd,newtl) { \
	structure *ss= str;                                           \
	if(ss->prv) ss->prv->nxt= ss->nxt;                            \
	else        oldhd       = ss->nxt;                            \
	if(ss->nxt) ss->nxt->prv= ss->prv;                            \
	else        oldtl       = ss->prv;                            \
	if(newtl)   (newtl)->nxt= ss;                                 \
	else        newhd       = ss;                                 \
	ss->prv= newtl;                                               \
	ss->nxt= (structure *) NULL;                                  \
	newtl  = ss;                                                  \
	}

/* --------------------------------------------------------------------- */

/* circular_link: handles the generation of circular linked lists.  Note that
 *   each structure is assumed to have members "nxt" and "prv".
 *   There is only one entry point to the circular linked list: the tail.
 *   New members appear at tail.  tail->prv is the head of the list.
 */
#define circular_link(structure,tail,nxt,prv,fail_msg) {          \
	structure *newstr;                                            \
	newstr= (structure *) malloc(sizeof(structure));              \
	outofmem(newstr,"%s\n",fail_msg);                             \
	newstr->prv= tail? tail      : newstr;                        \
	newstr->nxt= tail? tail->nxt : newstr;                        \
	if(tail) {                                                    \
		if(tail->nxt) tail->nxt->prv= newstr;                     \
		tail->nxt= newstr;                                        \
		}                                                         \
	tail= newstr;                                                 \
	}
#define delete_circular_link(s,tail,nxt,prv) {                    \
	if(s == s->prv) tail= NULL;                                   \
	else {                                                        \
		if(s == tail) {                                           \
			tail= s->prv;                                         \
			if(tail == s) tail= NULL;                             \
			}                                                     \
		s->prv->nxt= s->nxt;                                      \
		s->nxt->prv= s->prv;                                      \
		}                                                         \
	free((char *) s);                                             \
	}
#define only_circular_link(structure,newstr,tail,nxt,prv) {       \
	newstr->prv= tail? tail      : newstr;                        \
	newstr->nxt= tail? tail->nxt : newstr;                        \
	if(tail) {                                                    \
		if(tail->nxt) tail->nxt->prv= newstr;                     \
		tail->nxt= newstr;                                        \
		}                                                         \
	tail= newstr;                                                 \
	}
#define only_delete_circular_link(str,tail,nxt,prv) {             \
	if(str == str->prv) tail= NULL;                               \
	else {                                                        \
		if(str == tail) {                                         \
			tail= str->prv;                                       \
			if(tail == str) tail= NULL;                           \
			}                                                     \
		str->prv->nxt= str->nxt;                                  \
		str->nxt->prv= str->prv;                                  \
		}                                                         \
	}
#ifdef __cplusplus
# define CircularLink(structure,tail,nxt,prv,fail_msg) {          \
	structure *newstr;                                            \
	newstr= new structure;                                        \
	outofmem(newstr,"%s\n",fail_msg);                             \
	newstr->prv= tail? tail      : newstr;                        \
	newstr->nxt= tail? tail->nxt : newstr;                        \
	if(tail) {                                                    \
		if(tail->nxt) tail->nxt->prv= newstr;                     \
		tail->nxt= newstr;                                        \
		}                                                         \
	tail= newstr;                                                 \
	}
# define DeleteCircularLink(s,tail,nxt,prv) {                     \
	if(s == s->prv) tail= NULL;                                   \
	else {                                                        \
		if(s == tail) {                                           \
			tail= s->prv;                                         \
			if(tail == s) tail= NULL;                             \
			}                                                     \
		s->prv->nxt= s->nxt;                                      \
		s->nxt->prv= s->prv;                                      \
		}                                                         \
	delete s;                                                     \
	}
#endif

/* --------------------------------------------------------------------- */

/* head_link: handles the generation of head-linked lists.  Note that 
 *   each structure is assumed to have the member "nxt".
 *   The new member becomes "head" - ie. oldest is last in the linked list,
 *   the newest is first.
 */
#define head_link(structure,head,fail_msg) {                      \
	structure *newstr;                                            \
	newstr= (structure *) malloc(sizeof(structure));              \
	outofmem(newstr,"%s\n",fail_msg);                             \
	newstr->nxt= head;                                            \
	head    = newstr;                                             \
	}
#define delete_head_link(structure,head) {                        \
	if(head) {                                                    \
		structure *newhead= head->nxt;                            \
		head->nxt= NULL;                                          \
		free((char *) head);                                      \
		head= newhead;                                            \
		}                                                         \
	}
# define only_head_link(structure,newstr,head) {                  \
	newstr->nxt= head;                                            \
	head    = newstr;                                             \
	}
#define only_delete_head(structure,head) {                        \
	if(head) {                                                    \
		structure *newhead= head->nxt;                            \
		head->nxt= NULL;                                          \
		head     = newhead;                                       \
		}                                                         \
	}
#ifdef __cplusplus
# define HeadLink(structure,head,fail_msg) {                      \
	structure *newstr;                                            \
	newstr= new structure;                                        \
	outofmem(newstr,"%s\n",fail_msg);                             \
	newstr->nxt= head;                                            \
	head    = newstr;                                             \
	}
# define DeleteHeadLink(structure,head) {                         \
	if(head) {                                                    \
		structure *newhead= head->nxt;                            \
		head->nxt= NULL;                                          \
		delete head;                                              \
		head= newhead;                                            \
		}                                                         \
	}
#endif

/* --------------------------------------------------------------------- */

/* tail_link: handles the generation of tail-linked lists.  Note that
 *   each structure is assumed to have the member "nxt".
 *   The new member becomes "tail" - ie. oldest is first in the linked list,
 *   the newest is last.
 */
#define tail_link(structure,head,tail,fail_msg) {                 \
	structure *newstr;                                            \
	newstr= (structure *) malloc(sizeof(structure));              \
	outofmem(newstr,"%s\n",fail_msg);                             \
	if(tail) (tail)->nxt= newstr;                                 \
	else     head       = newstr;                                 \
	newstr->nxt= NULL;                                            \
	tail    = newstr;                                             \
	}
# define only_tail_link(structure,newstr,head,tail) {             \
	if(tail) (tail)->nxt= newstr;                                 \
	else     head       = newstr;                                 \
	newstr->nxt= NULL;                                            \
	tail    = newstr;                                             \
	}
#ifdef __cplusplus
# define TailLink(structure,head,tail,fail_msg) {                 \
	structure *newstr;                                            \
	newstr= new structure;                                        \
	outofmem(newstr,"%s\n",fail_msg);                             \
	if(tail) (tail)->nxt= newstr;                                 \
	else     head       = newstr;                                 \
	newstr->nxt= NULL;                                            \
	tail    = newstr;                                             \
	}
#endif

/* stralloc: allocates new memory for and copies a string into the new mem */
#define stralloc(ptr,string,fail_msg) {                             \
	ptr= (char *) calloc((size_t) strlen(string) + 1,sizeof(char)); \
	outofmem(ptr,"%s: <%s>\n",fail_msg,string);                     \
	strcpy(ptr,string);                                             \
	}

/* ustralloc: allocates new memory for and copies an
 *     unsigned char *string
 * into the new mem
 */
#define ustralloc(ptr,string,fail_msg) {                                 \
	ptr= (unsigned char *) calloc((size_t) strlen((char *) string) + 1,  \
	     sizeof(unsigned char));                                         \
	outofmem(ptr,"%s: <%s>\n",fail_msg,string);                          \
	strcpy((char *) ptr,(char *) string);                                \
	}

/* alloc: allocates a structure */
#define alloc(structure) (structure *) malloc(sizeof(structure))


/* ====================================================================== */


/* Swami Mahalingam's Link'ed list support macros */

/* ----------------------------------------------------------------------
 * Typedefs:
 */
typedef caddr_t         Item;
typedef struct LINKstr *Link;
typedef struct LISTstr *List;


/* ----------------------------------------------------------------------
 * Data Structures:
 */
struct LINKstr {
  Link nxt, prv;					/* pointers to previous and next links	*/
  Item item;						/* item to be stored in list			*/
  int  count;						/* position of link in list				*/
  int  attr1;						/* optional attributes of link			*/
  int  attr2;
  int  attr3;
  int  attr4;
  };

struct LISTstr {
  Link head;						/* head (first) pointer of List			*/
  Link tail;						/* tail (last) pointer of List			*/
  Link window;						/* current Link							*/
  int  count;						/* qty of Items in list					*/
  };


/* ----------------------------------------------------------------------
 * Define'd Macros:
 */

#define ApdItem(list,instance,type) {                                  \
  double_link (LINK, list->head, list->tail, "attempted to ");         \
  list->tail->item  = (Item) instance;                                 \
  list->tail->attr1 = 0;                                               \
  list->tail->attr2 = 0;                                               \
  list->tail->attr3 = 0;                                               \
  list->tail->attr4 = 0;                                               \
  list->tail->count = (list->tail->prv == NULL) ? 1 :                  \
    list->tail->prv->count + 1;                                        \
  list->count++;                                                       \
  }

#define InsItemAtPosn(list, item, type, posn) {                        \
  InsertItemAtPosn (list, (Item) item, posn);                          \
  }

#define DelItem(list, item) {                                          \
  DeleteItem (list, (Item) item);                                      \
  }

#define FlushList(list) do{                                            \
      delete_double_link (LINK, list->tail, list->head, list->tail);   \
      list->count--;                                                   \
    } while (list->tail)

#define for_list_links(list, link)                                      \
  for(link=list->head; link; link=link->nxt)

#define for_list_items(list, instance, type)                           \
  for(list->window=list->head;                                         \
      list->window && (instance = ((type) list->window->item));        \
      list->window=list->window->nxt)

/* alloc: allocates a structure */
#define alloc(structure) (structure *) malloc(sizeof(structure))

#endif /* LINKS_H */
