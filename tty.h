#ifndef _OOE_TTY_H_
#define _OOE_TTY_H_

#include <termios.h>

int ttyDisableRawMode();

int ttyEnableRawMode();

int ttyGetCursorPosition(int*, int*);

int ttyGetWindowSize(int*, int*);

#endif