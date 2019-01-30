#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "cache.h"

/**
 * Allocate a cache entry
 */
struct cache_entry *alloc_entry(char *path, char *content_type, void *content, int content_length)
{
  struct cache_entry *new_entry = malloc(sizeof(struct cache_entry));
  
  new_entry->path = path;
  new_entry->content_type = content_type;
  new_entry->content_length = content_length;
  new_entry->content = content;

  return new_entry;
}

/**
 * Deallocate a cache entry
 */
void free_entry(struct cache_entry *entry)
{
  free(entry->path);
  free(entry->content_type);
  free(entry->content);
  free(entry);
}

/**
 * Insert a cache entry at the head of the doubly linked list
 */
void dllist_insert_head(struct cache *cache, struct cache_entry *ce)
{
    // Insert at the head of the list
    if (cache->head == NULL) {
        cache->head = cache->tail = ce;
        ce->prev = ce->next = NULL;
    } else {
        cache->head->prev = ce;
        ce->next = cache->head;
        ce->prev = NULL;
        cache->head = ce;
    }
}

/**
 * Move a cache entry to the head of the doubly linked list
 */
void dllist_move_to_head(struct cache *cache, struct cache_entry *ce)
{
    if (ce != cache->head) {
        if (ce == cache->tail) {
            // We're the tail
            cache->tail = ce->prev;
            cache->tail->next = NULL;

        } else {
            // We're neither the head nor the tail
            ce->prev->next = ce->next;
            ce->next->prev = ce->prev;
        }

        ce->next = cache->head;
        cache->head->prev = ce;
        ce->prev = NULL;
        cache->head = ce;
    }
}


/**
 * Removes the tail from the doubly linked list and returns it
 * 
 * NOTE: does not deallocate the tail
 */
struct cache_entry *dllist_remove_tail(struct cache *cache)
{
    struct cache_entry *oldtail = cache->tail;

    cache->tail = oldtail->prev;
    cache->tail->next = NULL;

    cache->cur_size--;

    return oldtail;
}

/**
 * Create a new cache
 * 
 * max_size: maximum number of entries in the cache
 * hashsize: hashtable size (0 for default)
 */
struct cache *cache_create(int max_size, int hashsize)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    (void)max_size;
    (void)hashsize;
    return 0;
}

void cache_free(struct cache *cache)
{
    struct cache_entry *cur_entry = cache->head;

    hashtable_destroy(cache->index);

    while (cur_entry != NULL) {
        struct cache_entry *next_entry = cur_entry->next;

        free_entry(cur_entry);

        cur_entry = next_entry;
    }

    free(cache);
}

/**
 * Store an entry in the cache
 *
 * This will also remove the least-recently-used items as necessary.
 * 
 * NOTE: doesn't check for duplicate cache entries
 */
void cache_put(struct cache *cache, char *path, char *content_type, void *content, int content_length)
{
    struct cache_entry *new_entry = alloc_entry(path, content_type, content, content_length);

    dllist_insert_head(cache, new_entry);
    hashtable_put(cache->index, new_entry->path, new_entry);
    cache->cur_size++;

    while (cache->cur_size > cache->max_size) {
      struct cache_entry *removed_tail = dllist_remove_tail(cache);
      hashtable_delete(cache->index, removed_tail->path);
      free_entry(removed_tail);
    }
    
    ///////////////////
    // 1) Allocate a new cache entry with the passed parameters.✅
    // cache.c --> alloc_entry(char *path, char *content_type, void *content, int content_length) 
    
    // 2) Insert the entry at the head of the doubly-linked list.✅
    // cache.c --> void dllist_insert_head(struct cache *cache, struct cache_entry *ce)
    
    // 3) Store the entry in the hashtable as well, indexed by the entry's path.✅
    // hashtable.c --> void *hashtable_put(struct hashtable *ht, char *key, void *data)
    // insert path as the key, and the node as the data

    // 4) Increment the current size of the cache.✅

    // 5) If the cache size is greater than the max size:✅
      // 5a)Remove the cache entry at the tail of the linked list.✅
      // cache.c --> struct cache_entry *dllist_remove_tail(struct cache *cache)
      // does not deallocate the tail
      
      // 5b)Remove that same entry from the hashtable, using the entry's path and the hashtable_delete function.✅
      // hashtable.c --> void *hashtable_delete(struct hashtable *ht, char *key)

      // 5c)Free the cache entry.✅
      // cache.c --> void free_entry(struct cache_entry *entry)

      // 5d)Ensure the size counter for the number of entries in the cache is correct.✅
      // built in decrement to cur_size in dllist_remove_tail()
    ///////////////////
}

/**
 * Retrieve an entry from the cache
 */
struct cache_entry *cache_get(struct cache *cache, char *path)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    (void)cache;
    (void)path;
    return 0;
}
