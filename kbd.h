#ifndef _OOE_KBD_H_
#define _OOE_KBD_H_

#include "s.h"

enum editorKeys
{
    KEY_BACKSPACE = 0x7F,
    ESC_KEY = 0x1B,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

void kbdProcKey(struct SCRN*);

#endif