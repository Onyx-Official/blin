#ifndef _OOE_VBUF_H_
#define _OOE_VBUF_H_

#include <stddef.h>

struct VBUF
{
    char* data;
    size_t size;
    size_t cap;
};

struct VBUF vbuf_init();

void vbuf_append(struct VBUF*, const char*, const size_t);

void vbuf_free(struct VBUF*);

#endif