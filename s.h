#ifndef _OOE_S_H_
#define _OOE_S_H_

#include "w.h"

struct SCRN
{
    struct WINS wins;
    struct WIN* pWin;

    int winIndex;

    int width;
    int height;

    int cx;
    int cy;
};

struct SCRN scrn_init();

void scrn_free(struct SCRN*);

void scrn_update(struct SCRN*);

#endif