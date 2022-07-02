#include "vbuf.h"

#include <stdlib.h>
#include <memory.h>

#define VBUF_CAP	50

struct VBUF vbuf_init()
{
    struct VBUF vbuf = {NULL, 0, VBUF_CAP};
    vbuf.data = malloc(VBUF_CAP);
    return vbuf;
}

void vbuf_realloc(struct VBUF* pVbuf, const size_t newCap)
{
    char* data = malloc(newCap);
    if (newCap < pVbuf->size)	pVbuf->size = newCap;

    memcpy(data, pVbuf->data, pVbuf->size);
    free(pVbuf->data);

    pVbuf->data = data;
    pVbuf->cap = newCap;
}

void vbuf_append(struct VBUF* pVbuf, const char* data, const size_t data_size)
{
    if (pVbuf->size + data_size >= pVbuf->cap)
        vbuf_realloc(pVbuf, pVbuf->size + data_size + VBUF_CAP);

    memcpy(&pVbuf->data[pVbuf->size], data, data_size);
    pVbuf->size += data_size;
}

void vbuf_free(struct VBUF* pVbuf)
{
    free(pVbuf->data);
    pVbuf->size = pVbuf->cap = 0;
}