#include "tty.h"
#include "err.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

struct termios term_ios;

int ttyDisableRawMode()
{
    return tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_ios);
}

static void editor_at_exit()
{
    if (ttyDisableRawMode() == -1)	error("terminal_disable_raw_mode()");
}

int ttyEnableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &term_ios) == -1) return -1;;
    atexit(editor_at_exit);
    struct termios raw = term_ios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) return -1;
    return 0;
}

int ttyGetCursorPosition(int* row, int* col)
{
    char buf[32];
    unsigned int i = 0;

    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)	return -1;

    while (i < sizeof(buf) - 1)
    {
        if (read(STDIN_FILENO, &buf[i], 1) != 1)	break;
        if (buf[i] == 'R')				break;
        i++;
    }
    buf[i] = '\0';

    if (buf[0] != '\x1b' || buf[1] != '[')		return -1;
    if (sscanf(&buf[2], "%d;%d", row, col) != 2)	return -1;
    return 0;
}

int ttyGetWindowSize(int* row, int* col)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)	return -1;
        return ttyGetCursorPosition(row, col);
    } else {
        *col = ws.ws_col;
        *row = ws.ws_row;
        return 0;
    }
}