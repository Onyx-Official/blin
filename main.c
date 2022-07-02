#include "vbuf.h"
#include "w.h"

#include <stdio.h>
#include <stdlib.h>

#include "s.h"
#include "tty.h"
#include "kbd.h"
#include "defs.h"

#include <unistd.h>

struct SCRN scrn;

void terminalAtExit()
{
    scrn_free(&scrn);
}

int main()
{
    scrn = scrn_init();
    if (ttyGetWindowSize(&scrn.height, &scrn.width) == -1) {
        perror("Cannot get terminal window size.");
        exit(0);
    }

    //ttyEnableRawMode();

    struct WIN win = {scrn.width, scrn.height, 0, 0, 0, 1, 0};
    wins_append(&scrn.wins, win);
    scrn.pWin = &scrn.wins.wins[0];

    scrn.cx = scrn.pWin->cx + scrn.pWin->cx;
    scrn.cy = scrn.pWin->cy + scrn.pWin->cy;
    while (1)
    {
        scrn_update(&scrn);
        kbdProcKey(&scrn);
    }
    return 0;
}