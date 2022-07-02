#include "kbd.h"
#include "ws.h"

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define CTRL_KEY(k)	((k) & 0x1F)

static int kbdReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) return -1;
  }
  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
    if (seq[0] == '[') {
      if (seq[1] >= '0' && seq[1] <= '9') {
        if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
        if (seq[2] == '~') {
          switch (seq[1]) {
            case '1': return HOME_KEY;
            case '3': return DEL_KEY;
            case '4': return END_KEY;
            case '5': return PAGE_UP;
            case '6': return PAGE_DOWN;
            case '7': return HOME_KEY;
            case '8': return END_KEY;
          }
        }
      } else {
        switch (seq[1]) {
          case 'A': return ARROW_UP;
          case 'B': return ARROW_DOWN;
          case 'C': return ARROW_RIGHT;
          case 'D': return ARROW_LEFT;
          case 'H': return HOME_KEY;
          case 'F': return END_KEY;
        }
      }
    } else if (seq[0] == 'O') {
      switch (seq[1]) {
        case 'H': return HOME_KEY;
        case 'F': return END_KEY;
      }
    }
    return '\x1b';
  } else {
    return c;
  }
}

void scrnMoveCursor(struct SCRN* pScrn, int key)
{
  switch (key)
  {
  case ARROW_UP:
    if (pScrn->pWin->cy != 1)
      pScrn->pWin->cy--;
    break;
  case ARROW_DOWN:
    if (pScrn->pWin->cy < pScrn->pWin->h - 1)
      pScrn->pWin->cy++;
    break;
  case ARROW_LEFT:
    if (pScrn->pWin->splitType && pScrn->pWin->cx != 1)
    {
      pScrn->pWin->cx--;
      break;
    }
    
    if (!pScrn->pWin->splitType && pScrn->pWin->cx != 0)
    {
      pScrn->pWin->cx--;
      break;
    }
    break;
  case ARROW_RIGHT:
    if (pScrn->pWin->cx < pScrn->pWin->w - 1)
      pScrn->pWin->cx++;
    break;
  }
  pScrn->cx = pScrn->pWin->x + pScrn->pWin->cx;
  pScrn->cy = pScrn->pWin->y + pScrn->pWin->cy;
}

void kbdProcKey(struct SCRN* pScrn)
{
  char buf[30];	int size = 0;
  int winIndex;

  int key = kbdReadKey();
  //char buf[300];	int size;
  //int y = 0;	int x = 0;

  switch (key)
  {
  case CTRL_KEY('Q'):
    exit(0);
    break;
  // Get winIndex
  case CTRL_KEY('H'):
    winSplitVertical(pScrn);
    break;
  case CTRL_KEY('O'):
    winSplitHorizontal(pScrn);
    break;
  case CTRL_KEY('G'):
    winIndex = getWinIndex(pScrn);
    size = snprintf(buf, sizeof(buf), "\x1b[3;3H%d", winIndex);
    write(STDOUT_FILENO, buf, size);
    break;
  // Split window horizontally
  // Split window vertically
  case ARROW_UP:
  case ARROW_DOWN:
  case ARROW_LEFT:
  case ARROW_RIGHT:
    scrnMoveCursor(pScrn, key);
    break;
  }
}