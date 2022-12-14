#include "queue.h"
#include "dll.h"
#include <stdio.h>
#include <stdlib.h>


/* return a newly created empty queue */
queue_t *create_queue ( ) {
    // DO NOT MODIFY!!!
    queue_t *Q = ( queue_t * ) malloc( sizeof( queue_t ));
    Q->list = create_list();
    Q->front = Q->list->head;
    Q->rear = Q->list->tail;
    Q->size = Q->list->size;
    return Q;
}

/*  insert data at the end of a queue */
void enqueue ( queue_t *q, int data ) {
    insert_back( q->list, data );
    q->rear = q->list->tail;
    q->size++;
}

/* return the data at the front of a queue and remove it. Return -1 if queue is empty */
int dequeue ( queue_t *q ) {
    int rv = q->front->data;
    delete_front( q->list );
    return rv;
}

/* return the data at the front of a queue. Return -1 if queue is empty */
int front ( queue_t *q ) {
    return q->front->data;
}

int empty ( queue_t *q ) // return if the queue is empty
{
    // DO NOT MODIFY!!!
    return is_empty( q->list );
}

int queue_size ( queue_t *q ) // returns the number of elements in the queue
{
    // DO NOT MODIFY!!!
    return q->size;
}

void delete_queue ( queue_t *q ) // empty the contents of the queue
{
    // DO NOT MODIFY!!!
    delete_list( q->list );
    free( q );
}
