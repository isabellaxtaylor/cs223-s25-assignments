/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 04/23/2025
 * Description: First-fit free-list memory allocator
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
    int size;      
    int used;      
    struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    struct chunk **prevp = &flist;
    struct chunk  *curr = flist;
    while (curr) {
        if (curr->size >= (int)size) {
            *prevp = curr->next;
            curr->used = size;
            curr->next = NULL;
            return (void*)(curr + 1);
        }
        prevp = &curr->next;
        curr  = curr->next;
    }

    size_t total = sizeof(struct chunk) + size;
    struct chunk *hdr = sbrk(total);
    if (!hdr) {
        return NULL;
    }
    hdr->size = size;
    hdr->used = size;
    hdr->next = NULL;
    return (void*)(hdr + 1);
}

void free(void *memory) {
    if (memory == NULL) {
        return;
    }
    struct chunk *hdr = (struct chunk*)memory - 1;
    hdr->used = 0;
    hdr->next = flist;
    flist  = hdr;
}
