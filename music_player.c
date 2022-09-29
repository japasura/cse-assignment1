#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

song_t *swapAndIterate ( list_t *list, song_t *song, song_t *toSwap );

playlist_t *create_playlist ( ) // return a newly created doubly linked list
{
    // DO NOT MODIFY!!!
    playlist_t *playlist = ( playlist_t * ) malloc( sizeof( playlist_t ));
    playlist->list = create_list();
    playlist->num_songs = 0;
    playlist->last_song = NULL;
    return playlist;
}

void delete_playlist ( playlist_t *playlist ) // delete the playlist
{
    // DO NOT MODIFY!!!
    delete_list( playlist->list );
    free( playlist );
}

music_queue_t *create_music_queue ( ) // return a newly created queue
{
    // DO NOT MODIFY!!!
    return create_queue();
}

void clear_music_queue ( music_queue_t *q ) // clear the queue q
{
    // DO NOT MODIFY!!!
    delete_queue( q );
}

/*
 * add a song id to the playlist
 */
void add_song ( playlist_t *playlist, int song_id, int where ) {
    switch ( where ) {
        case -1: {
            insert_front( playlist->list, song_id );
            break;
        }
        case -2: {
            insert_back( playlist->list, song_id );
            break;
        }
        default: {
            insert_after( playlist->list, song_id, where );
            break;
        }
    }
    playlist->num_songs++;
}

/* remove song id from the playlist */
void delete_song ( playlist_t *playlist, int song_id ) {
    delete_node( playlist->list, song_id );
    playlist->num_songs--;
}

/*
 * return a pointer to the node where the song id is present in the playlist
 */
song_t *search_song ( playlist_t *playlist, int song_id ) {
    return search( playlist->list, song_id );
}

/* play the song with given song_id from the list(no need to bother about the queue.
 *      Call to this function should always play the given song and further calls to play_next
 *      and play_previous)
 */
void search_and_play ( playlist_t *playlist, int song_id ) {
    song_t *song = search_song( playlist, song_id );
    if ( song ) {
        play_song( song->data );
        playlist->last_song = song;
    }
}

void play_from_playlist ( playlist_t *playlist ) {
    if ( playlist->last_song && playlist->last_song->next ) {
        play_song( playlist->last_song->data );
        playlist->last_song = playlist->last_song->next;
    } else if ( playlist->list->size ) {
        play_song( playlist->list->head->data );
        playlist->last_song = playlist->list->head;
    }
}

/*  play the next song in the linked list if the queue is empty.
 *  If the queue if not empty, play from the queue
 */
void play_next ( playlist_t *playlist, music_queue_t *q ) {
    if ( empty( q )) {
        play_from_playlist( playlist );
    } else {
        play_from_queue( q );
    }
}

/*
 * play the previous song from the linked list
 */
void play_previous ( playlist_t *playlist ) {
    if ( playlist->last_song && playlist->last_song->prev ) {
        play_song( playlist->last_song->prev->data );
        playlist->last_song = playlist->last_song->prev;
    } else if ( !is_empty( playlist->list )) {
        playlist->last_song = playlist->list->tail;
        play_song( playlist->last_song->data );
    }
}

/* play a song from the queue */
void play_from_queue ( music_queue_t *q ) {
    int songid = dequeue( q );
    play_song( songid );
}

/* insert a song id to the queue */
void insert_to_queue ( music_queue_t *q, int song_id ) {
    enqueue( q, song_id );
}

/* reverse the order of the songs in the given playlist. (Swap the nodes, not data) */
void reverse ( playlist_t *playlist ) {
    song_t *cur1, *tmp;
    list_t *list = playlist->list;
    cur1 = list->head;

    while ( cur1 ) {
        tmp = cur1->next;
        cur1->next = cur1->prev;
        cur1->prev = tmp;
        cur1 = cur1->prev;
    }
    cur1 = list->head;
    list->head = list->tail;
    list->tail = cur1;
}

song_t *getElAtIndex ( list_t *list, int index ) {
    song_t *cur = list->head;
    while ( index-- && cur ) {
        cur = cur->next;
    }
    return cur;
}

/*
 * swap the node at position i with node at position i+k
 * upto the point where i+k is less than the size of the linked list
 */
void k_swap ( playlist_t *playlist, int k ) {
    list_t *list = playlist->list;
    song_t *song = list->head;
    song_t *toSwap;
    song_t *tmp;
    for ( int i = 0; i <= (list->size); i++ ) {
        toSwap = getElAtIndex( list, i + k );
        tmp = song->next;
        if ( toSwap ) {
            swapAndIterate( list, song, toSwap );
        } else {
            break;
        }
        song = tmp;
    }
}

song_t *swapAndIterate ( list_t *list, song_t *song, song_t *toSwap ) {
    song_t *toSwp_nxt = toSwap->next;
    song_t *tmp;
    if ( toSwap->next ) {
        toSwap->next->prev = song;
    } else {
        list->tail = song;
    }

    if ( toSwap->prev ) {
        toSwap->prev->next = song;
    }

    if ( song->prev ) {
        song->prev->next = toSwap;
    } else {
        list->head = toSwap;
    }

    song->next->prev = toSwap;

    tmp = song->next;
    song->next = toSwap->next;
    toSwap->next = tmp;

    tmp = song->prev;
    song->prev = toSwap->prev;
    toSwap->prev = tmp;
    return toSwp_nxt;
}

/* perform k_swap and reverse */
void shuffle ( playlist_t *playlist, int k ) {
    k_swap( playlist, k );
    reverse( playlist );
}

/* if the given linked list has a cycle,
 *  return the start of the cycle, else return null.
 *  Check cycles only in forward direction i.e with the next pointer.
 *  No need to check for cycles in the backward pointer.
 */
song_t *debug ( playlist_t *playlist ) {
    list_t *list = playlist->list;
    node_t *slow = list->head, *fast = list->head;

    while ( slow && fast && fast->next ) {
        slow = slow->next;
        fast = fast->next->next;
        if ( slow == fast ) {
            return slow;
        }
    }
    return NULL;

}

void display_playlist ( playlist_t *p ) // Displays the playlist
{
    // DO NOT MODIFY!!!
    display_list( p->list );
}

void play_song ( int song_id ) {
    // DO NOT MODIFY!!!
    printf( "Playing: %d\n", song_id );
}

