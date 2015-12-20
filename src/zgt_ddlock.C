/*------------------------------------------------------------------------------
//                         RESTRICTED RIGHTS LEGEND
//
// Use,  duplication, or  disclosure  by  the  Government is subject 
// to restrictions as set forth in subdivision (c)(1)(ii) of the Rights
// in Technical Data and Computer Software clause at 52.227-7013. 
//
// Copyright 1989, 1990, 1991 Texas Instruments Incorporated.  All rights reserved.
//------------------------------------------------------------------------------
*/

#define NULL	0
#define TRUE	1
#define FALSE	0
#include "zgt_def.h"
#include "zgt_tm.h"
#include "zgt_extern.h"

extern zgt_tm *ZGT_Sh;

/*wait_for constructor
 * Initializes the waiting transaction in wtable
 * and setting the appropriate pointers.
 */
wait_for::wait_for()
{
  zgt_tx *tp;
  node* np;
  wtable = NULL;
  fprintf(stdout, "::entering wait_for method:::\n");
  fflush(stdout);
  for (tp = (zgt_tx *) ZGT_Sh->lastr; tp!= NULL; tp= tp->nextr){
    if(tp->status != TR_WAIT) continue;
    np = new node;
    np->tid = tp->tid;
    np->sgno = tp->sgno;
    np->obno = tp->obno;
    np->lockmode = tp->lockmode;
    np->semno = tp->semno;
    np->next =  (wtable != NULL) ? wtable : NULL;
    np->parent = NULL;
    np->next_s = NULL;
    np->level = 0;
    wtable = np;
  }
  fprintf(stdout, "::leaving wait_for method:::\n");
  fflush(stdout);
}


/*
 * deadlock(), this method is used to check the waiting transaction for deadlock
 * go through the wtable and create a graph
 * use the traverse method to find the victim
 * if the transaction tid matches to that of the victim then
 * set the status of transaction to TR_ABORT
 * use the tp->free_locks() to release the lock owned by that transaction
 */
int wait_for::deadlock(){
  node* np;
  zgt_tx    *tp;

  fprintf(stdout, "::entering deadlock method:::\n");
  fflush(stdout);
  for (np=wtable; np!=NULL; np= np->next) {
    if (np->level == 0) {
      head = new node;
      head->tid = np->tid;
      head->sgno = np->sgno;
      head->obno = np->obno;
      head->lockmode = np->lockmode;
      head->semno = np->semno;
      head->next = NULL;
      head->parent = NULL;
      head->next_s = NULL;
      head->level = 1;
     //printf("\nhead****%d %d %d %c %d %d\n",head->tid,head->sgno,head->obno,head->lockmode,head->semno, head->level);
      found = FALSE;
      traverse(head);
      if ((found==TRUE)&&(victim != NULL)) {
	for (tp = (zgt_tx *) ZGT_Sh->lastr; tp!= NULL; tp= tp->nextr){
	  if (tp->tid == victim->tid) break;
	}
	tp->status = TR_ABORT;

	//tp->end_tx(); //sharma, oct 14 for testing

    tp->free_locks();

	// the v operation may not free the intended process
	  // one needs to be more careful here

	if (victim->lockmode =='X'){
	//free the semaphore
	}
	// should free all locks assoc. with tid here
	  continue;
      }
    }
  }
  fprintf(stdout, "::leaving deadlock method:::\n");
  fflush(stdout);
  return(0);
}

/*
 * this method is used by deadlock() find the owners
 * of the lock which are being waiting if it is visited
 * location is not null then it means a cycle is found
 * so choose a victim set the found to TRUE and return.
 * also create a node q set its appropriate pointers
 * assign the tid, sgno,lockmode, obno, head and last
 * to q then mark the wtable by going through wtable
 * and find the tid in hashtable(hlink) equal to
 * q's tid and set the level of q to 1 set the hlink
 * pointer by traveling it to proper obno and sgno
 * as in p.
 * use the last pointer and q's level to travel through
 * transaction list zgt_tx if the tp_status is equal to
 * TR_WAIT assign the transaction data structure to node
 * q's data structure and recursively call traverse
 * using q to find a cycle. delete the node last
 * and assign the q's next_s to last and q=last.
 */
int wait_for::traverse(node* p)
{
  node *q, *last=NULL;
  zgt_tx    *tp;
  zgt_hlink *sp;
  
};

/*
 * this method is used by traverse() to keep track of the
 * visited transaction while traversing through the wait_for
 * graph using the tid of transaction in hash table(hlink pointer)
 * similar to a DFS
 */
int wait_for::visited(long t)
{
	node* n;
	for (n=head; n != NULL; n=n->next) if (t==n->tid) return(TRUE);
	
	return(FALSE);
};

/*
 * this method is used by the traverse() method in
 * to get the node in wtable using the tid of transaction
 * in hash table(hlink pointer).
 */
node * wait_for::location(long t)
{
        node* n;
        for (n=head; n != NULL; n=n->next)
		if ((t==n->tid)&&(n->level>=0)) return(n);
        return(NULL); 
}

/*
 * this method is used by traverse method to choose a
 * victim after a deadlock is encountered while traversing
 * the wait_for graph
 */
node* wait_for::choose_victim(node* p, node* q)
{
	node* n;
	int total;
	zgt_tx    *tp;
	//for (n=p; n != q->parent; n=n->parent) {
	//	printf("%d  ",n->tid);
	//}
	//printf("\n");
	for (n=p; n != q->parent; n=n->parent) {
		if (n->lockmode == 'X') return(n);
		else{
		  for (total=0,tp = (zgt_tx *) ZGT_Sh->lastr; tp!=NULL; tp= tp->nextr){
		    if (tp->semno == n->semno) total++;
		  }
			
		  if (total==1) return(n);
		}
		// for the moment, we need to show that there is at least one
		// candidate process that is associated with a semaphore waited by
		// exactly one process.  The code has to be modified if we can't 
		// show this.
	}
	return(NULL);
}
