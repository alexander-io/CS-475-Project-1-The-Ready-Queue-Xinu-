/* queue.c - enqueue, dequeue, isempty, nonempty, et al. */

// #include <xinu.h>
#include "../include/xinu.h"
#include "../include/stdio.h"
#include <stdlib.h>

/**
 * Prints out contents of a queue
 * @param q	pointer to a queue
 */
void	printqueue(struct queue *q)
{
	// print all contents from head to tail
	// format should be [(pid=p1), (pid=p2), ...

	struct qentry *toPrint = q->head;
	printf("\n[(pid=p%d)",toPrint->process_id);
	toPrint = toPrint->next;
	while(toPrint != NULL){
		printf(", (pid=p%d)",toPrint->process_id);
		toPrint = toPrint->next;
	}
	printf("]\n");
}

/**
 * Checks whether queue is empty
 * @param q	Pointer to a queue
 * @return TRUE if true, FALSE otherwise
 */
bool8	isempty(struct queue *q)
{
	
	if (q->size == 0 || q == NULL){
		return 1;	
	} 
	return 0;	
	
	//return NULL;
}

/**
 * Checks whether queue is nonempty
 * @param q	Pointer to a queue
 * @return TRUE if true, FALSE otherwise
 */
bool8	nonempty(struct queue *q)
{
	// don't just check q's size because q could be NULL
	
	if (q->size == 0 || q == NULL){
		return 0;	
	} 
	return 1;
}


/**
 * Checks whether queue is full
 * @param q	Pointer to a queue
 * @return TRUE if true, FALSE otherwise
 */
bool8	isfull(struct queue *q)
{
	// check if there are at least NPROC processes in the queue'
	if(q->size >= NPROC){
		return 1;
	}
	return 0;
}


/**
 * Insert a process at the tail of a queue
 * @param pid	ID process to insert
 * @param q	Pointer to the queue to use
 *
 * @return pid on success, SYSERR otherwise
 */
pid32 enqueue(pid32 pid, struct queue *q)
{
        // check if queue is full and if pid is illegal, and return SYSERR if either is true
	
	//if (isfull(q) || isbadpid(pid)){
	if (isfull(q)){
		return SYSERR;
	}

        // allocate space on heap for a new QEntry
	struct qentry *new_qentry = malloc(sizeof(struct qentry));

        // initialize the new QEntry
	new_qentry->process_id = pid;

 	// insert into tail of queue
	new_qentry->prev = q->tail;
	
	q->tail = new_qentry;

        // return the pid on success
	return pid;
}


/**
 * Remove and return the first process on a list
 * @param q	Pointer to the queue to use
 * @return pid of the process removed, or EMPTY if queue is empty
 */
pid32 dequeue(struct queue *q)
{
        // return EMPTY if queue is empty
	if (isempty(q)){
		return EMPTY;	
	}

        // get the head entry of the queue
	
	struct qentry *old_head = q->head;// = malloc(sizeof(qentry));
	q->head = old_head->next;
        // unlink the head entry from the rest
	
	q->head->prev = NULL;
	pid32 return_pid = old_head->process_id;
        // free up the space on the heap
	free(old_head);

        // return the pid on success
	return return_pid;
}


/**
 * Finds a queue entry given pid
 * @param pid	a process ID
 * @param q	a pointer to a queue
 * @return pointer to the entry if found, NULL otherwise
 */
struct qentry *getbypid(pid32 pid, struct queue *q)
{
	// return NULL if queue is empty or if an illegal pid is given
	//if (isempty(q) || isbadpid(pid)){
	if (isempty(q)){
		return NULL;
	}

	struct qentry *temp = q->head;

	// find the qentry with the given pid
	while(temp != NULL){
		if (temp->process_id == pid){
			return temp;
		}	
		temp = temp->next;
	}
	// return a pointer to it
	return NULL;
}

/**
 * Remove a process from the front of a queue (pid assumed valid with no check)
 * @param q	pointer to a queue
 * @return pid on success, EMPTY if queue is empty
 */
pid32	getfirst(struct queue *q)
{
	//TODO - return EMPTY if queue is empty

	//TODO - remove process from head of queue and return its pid
	return NULL;
}

/**
 * Remove a process from the end of a queue (pid assumed valid with no check)
 * @param q	Pointer to the queue
 * @return pid on success, EMPTY otherwise
 */
pid32	getlast(struct queue *q)
{
	//TODO - return EMPTY if queue is empty

	//TODO - remove process from tail of queue and return its pid
	return NULL;
}



/**
 * Remove a process from an arbitrary point in a queue
 * @param pid	ID of process to remove
 * @param q	Pointer to the queue
 * @return pid on success, SYSERR if pid is not found
 */
pid32	remove(pid32 pid, struct queue *q)
{
	//TODO - return EMPTY if queue is empty

	//TODO - return SYSERR if pid is illegal

	//TODO - remove process identified by pid parameter from the queue and return its pid

	//TODO - if pid does not exist in the queue, return SYSERR
	return NULL;
}


int main(){
	
	// init two new qentries
	struct qentry process1 = {.process_id = 1};
	struct qentry process2 = {.process_id = 2};
	
	
	process1.next = &process2;
	process2.prev = &process1;

	struct queue my_queue = {&process1, &process2, 2};
	

	//printf("\nhead : %d\n", my_queue.head->process_id);
	// call printqueue()
	printqueue(&my_queue);

	//printf("\nhead : %d\n", my_queue.head->process_id);


	//qentry.process_id = 1;
	
	//struct queue = {.};
	
	return 0;
}

