#include "s.h"
#include "w.h"
#include "vbuf.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

struct SCRN scrn_init()
{
    struct SCRN scrn;
    scrn.wins = wins_init();
    scrn.winIndex = 0;
    scrn.pWin = &scrn.wins.wins[0];
    scrn.width = scrn.height = scrn.cx = scrn.cy = 0;

    return scrn;
}

void scrn_free(struct SCRN* pScrn)
{
    wins_free(&pScrn->wins);
}

static void scrnUpdate_DrawWin(struct WIN win, struct VBUF* pVbuf)
{
    // Set terminal cursor to window position
    char buffer[300];	int size = 0;
    memset(buffer, 0, sizeof(buffer));
    
    size = snprintf(buffer, sizeof(buffer), "\x1b[%d;%dH", win.y + 1, win.x + 1);
    vbuf_append(pVbuf, buffer, size);

    // Draw window status bar
    vbuf_append(pVbuf, "\x1b[7m", 4);
    char buf[15];
    size = snprintf(buf, sizeof(buf), "X: %d, Y: %d", win.cx, win.cy);
    vbuf_append(pVbuf, buf, size);
    for (int i = 0; i < win.w - size; i++)
        vbuf_append(pVbuf, " ", 1);
    //vbuf_append(pVbuf, "\x1b[m", 3);

    if (win.splitType)
    {
        for (int y = 1; y < win.h; y++)
        {
            size = snprintf(buffer, sizeof(buffer), "\x1b[%d;%dH ", win.y + 1 + y, win.x + 1);
            vbuf_append(pVbuf, buffer, size);
        }
    }
    vbuf_append(pVbuf, "\x1b[m", 3);
}

void scrn_update(struct SCRN* pScrn)
{
    struct VBUF vbuf = vbuf_init();
    
    // hide terminal cursor
    vbuf_append(&vbuf, "\x1b[?25l", 6);

    // reset terminal cursor
    vbuf_append(&vbuf, "\x1b[H", 3);

    // Draw
    for (int i = 0; i < pScrn->wins.size; i++)
        scrnUpdate_DrawWin(pScrn->wins.wins[i], &vbuf);

    // Position screen cursor
    char buf[300];
    int size = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", pScrn->pWin->y + pScrn->pWin->cy + 1,
                                                         pScrn->pWin->x + pScrn->pWin->cx + 1);
    vbuf_append(&vbuf, buf, size);

    // Show terminal cursor
    vbuf_append(&vbuf, "\x1b[?25h", 6);

    // Write buffer to the terminal
    write(STDOUT_FILENO, vbuf.data, vbuf.size);
    vbuf_free(&vbuf);
}