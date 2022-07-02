#include "ws.h"

#include "defs.h"
#include "w.h"

#include <stdlib.h>

int getWinIndex(struct SCRN* pScrn)
{
    int winIndex = -1;
    
    for (int i = 0; i < pScrn->wins.size; i++)
    {
        if (pScrn->cx >= pScrn->wins.wins[i].x 
         && pScrn->cy >= pScrn->wins.wins[i].y
         && pScrn->cx <= pScrn->wins.wins[i].x + pScrn->wins.wins[i].w
         && pScrn->cy <= pScrn->wins.wins[i].y + pScrn->wins.wins[i].h)
        {	winIndex = i;	break;	}
    }
    return winIndex;
}

void winSplitVertical(struct SCRN* pScrn)
{
    // Get window width and halve it.
    int winIndex = getWinIndex(pScrn);

    if (round_whole((float)pScrn->wins.wins[winIndex].w / 2) >= WIN_MIN_WIDTH)
    {
        struct WIN win;
        win.w = round_whole((float)pScrn->wins.wins[winIndex].w / 2);
        win.h = pScrn->wins.wins[winIndex].h;
        win.x = (pScrn->wins.wins[winIndex].w / 2) + pScrn->wins.wins[winIndex].x;
        win.y = pScrn->wins.wins[winIndex].y;
        win.cx = win.cy = win.splitType = 1;
        wins_append(&pScrn->wins, win);

        pScrn->wins.wins[winIndex].w /= 2;
    }
}

void winSplitHorizontal(struct SCRN* pScrn)
{
    int winIndex = getWinIndex(pScrn);

    if (round_whole((float)pScrn->wins.wins[winIndex].h / 2) >= WIN_MIN_HEIGHT)
    {
        struct WIN win;
        win.w = pScrn->wins.wins[winIndex].w;
        win.h = round_whole((float)pScrn->wins.wins[winIndex].h / 2);
        win.x = pScrn->wins.wins[winIndex].x;
        win.y = (pScrn->wins.wins[winIndex].h / 2) + pScrn->wins.wins[winIndex].y;
        win.cx = win.cy = 1;
        win.splitType = 0;
        wins_append(&pScrn->wins, win);
        
        pScrn->wins.wins[winIndex].h /= 2;
    }
}