#ifndef VARRAY_H_
#define VARRAY_H_

#include <stddef.h>

typedef struct {
	size_t len;
	size_t cap;
	size_t el_size;
	void *data;
} varray_t;

varray_t *va_new(const size_t cap, const size_t el_size);
void va_push(varray_t *va, const void *elem);
void *va_pop(varray_t *va);
int va_grow(varray_t *va, const size_t cap);
void va_free(varray_t **va);

#endif // VARRAY_H_
