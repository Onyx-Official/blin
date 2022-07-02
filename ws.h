#ifndef _OOE_WS_H_
#define _OOE_WS_H_

#include "s.h"

#define WIN_MIN_HEIGHT	5
#define WIN_MIN_WIDTH	15

int getWinIndex(struct SCRN*);

void winSplitVertical(struct SCRN*);

void winSplitHorizontal(struct SCRN*);

#endif