#include "varray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

varray_t *va_new(const size_t cap, const size_t el_size)
{
    if (cap < 1) {
        return NULL;
    }

    varray_t *va = malloc(sizeof(*va));
    if (!va) {
        return NULL;
    }

    va->data = malloc(cap * el_size);
    if (!va->data) {
        free(va);
        return NULL;
    }

    va->cap = cap;
    va->len = 0;
    va->el_size = el_size;

    return va;
}

void va_push(varray_t *va, const void *el)
{
    if (va->len == va->cap) {
        int res = va_grow(va, va->cap * 2);
        if (res < 0) {
            fprintf(stderr, "unable to grow array\n");
            return;
        }
    }

    size_t offset = va->len * va->el_size;
    memcpy((char *)va->data + offset, el, va->el_size);
    va->len++;
}

void *va_pop(varray_t *va)
{
    if (va->len == 0) {
        // vator is empty
        return NULL;
    }

    va->len--;

    // TODO: shrink array if less than half empty

    size_t offset = va->len * va->el_size;

    return (char *)va->data + offset;
}

int va_grow(varray_t *va, const size_t cap)
{
    // TODO: use realloc?
    void *new_data = realloc(va->data, cap * va->el_size);
    if (!new_data) {
        return -1;
    }

    va->data = new_data;
    va->cap = cap;

    return 0;
}

void va_free(varray_t **va)
{
    if ((*va)->data) {
        free((*va)->data);
    }
    if (*va) {
        free(*va);
        *va = NULL;
    }
}
