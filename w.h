#ifndef _OOE_W_H_
#define _OOE_W_H_

struct WIN
{
    int w;
    int h;
    int x;
    int y;
    int cx;
    int cy;

    short splitType;
};

struct WINS
{
    struct WIN* wins;
    int size;
    int cap;
};

struct WINS wins_init();

void wins_append(struct WINS*, const struct WIN);

void wins_free(struct WINS*);

#endif