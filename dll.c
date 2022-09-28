#include "dll.h"
#include <stdio.h>
#include <stdlib.h>

list_t *create_list ( ) /* return a newly created empty doubly linked list */ {
    // DO NOT MODIFY!!!
    list_t *l = ( list_t * ) malloc( sizeof( list_t ));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

node_t *create_item ( int val ) {
    node_t *rv = ( node_t * ) malloc( sizeof( list_t ));
    rv->data = val;
}

/* inserts data to the beginning of the linked list */
void insert_front ( list_t *list, int data ) {
    if (list->size){
        list->head->prev = create_item( data );
        list->head->prev->next = list->head;
        list->head = list->head->prev;
    } else {
        list->head = create_item(data);
        list->tail = list->head;
        list->tail->next = NULL;
        list->tail->prev = NULL;
    }
    list->size++;
}

void insert_back ( list_t *list, int data ) /* inserts data to the end of the linked list */ {
    if (list->size){
        list->tail->next = create_item( data );
        list->tail->next->prev = list->tail;
        list->tail = list->tail->next;
        list->tail->next = NULL;
        list->size++;
    } else {
        list->head = create_item(data);
        list->tail = list->head;
        list->tail->next = NULL;
        list->tail->prev = NULL;
        list->size = 1;
    }
}

/*
 * // inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
 */
void insert_after ( list_t *list, int data, int prev ) {
    node_t *cur = list->head;
    while ( cur && cur->data != prev ) {
        cur = cur->next;
    }
    if ( cur ) { // to guard against prev not existing
        node_t *tmp = cur->next;
        cur->next = create_item( data );
        cur->next->next = tmp;
        tmp && (tmp->prev = cur);
        cur->next->prev = cur;
        list->size++;
    }
}

/*
 * delete the start node from the linked list.
 */
void delete_front ( list_t *list ) {
    node_t *tmp = list->head->next;
    tmp->prev = NULL;
    free( list->head );
    list->head = tmp;
    list->size--;
}

/*
 * delete the end node from the linked list.
 */
void delete_back ( list_t *list ) {
    node_t *tmp = list->tail->prev;
    free( list->tail );
    list->tail = tmp;
    tmp->next = NULL;
    list->size--;
}

/*
 * TODO: delete the node with “data” from the linked list.
 */
void delete_node ( list_t *list, int data ) {
    node_t *cur = search( list, data );
    if (cur == list->head){
        list->head = cur->next;
    }
    if (cur == list->tail){
        list->tail = cur->prev;
    }
    if ( cur ) { // guard against data not existing
        cur->prev && (cur->prev->next = cur->next);
        cur->next && (cur->next->prev = cur->prev);
        free( cur );
        list->size--;
    }

}

/*
 * returns the pointer to the node with “data” field. Return NULL if not found.
*/
node_t *search ( list_t *list, int data ) {
    node_t *cur = list->head;
    while ( cur && cur->data != data ) {
        cur = cur->next;
    }
    return cur;
}

int is_empty ( list_t *list ) // return true or 1 if the list is empty; else returns false or 0
{
    // DO NOT MODIFY!!!
    return list->size == 0;
}

int size ( list_t *list ) // returns the number of nodes in the linked list.
{
    // DO NOT MODIFY!!!
    return list->size;
}

void delete_nodes ( node_t *head ) // helper
{
    // DO NOT MODIFY!!!
    if ( head == NULL)
        return;
    delete_nodes( head->next );
    free( head );
}

void delete_list ( list_t *list ) // free all the contents of the linked list
{
    // DO NOT MODIFY!!!
    delete_nodes( list->head );
    free( list );
}

/*
 * print the linked list by separating each item
 * by a space and a new line at the end of the linked list.
 */
void display_list ( list_t *list ) {
    // DO NOT MODIFY!!!
    node_t *it = list->head;
    while ( it != NULL) {
        printf( "%d ", it->data );
        it = it->next;
    }
    printf( "\n" );
}

