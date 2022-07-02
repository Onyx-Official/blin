#include "w.h"

#include <stdlib.h>
#include <memory.h>

#define WINS_CAP	5

struct WINS wins_init()
{
    struct WINS wins = {NULL, 0, WINS_CAP};
    wins.wins = malloc(sizeof(struct WIN) * WINS_CAP);
    wins.size = 0;
    wins.cap = WINS_CAP;
    return wins;
}

void winsRealloc(struct WINS* pWins, int newCap)
{
    if (newCap <= 0)	return;
    if (newCap < pWins->size)
        pWins->size = newCap;

    struct WIN* wins = malloc(sizeof(struct WIN) * newCap);


    for (int i = 0; i < newCap; i++)
        wins[i] = pWins->wins[i];

    free(pWins->wins);
    pWins->wins = wins;

    pWins->cap = newCap;
}

void wins_append(struct WINS* pWins, const struct WIN win)
{
    if (pWins->size >= pWins->cap)
        winsRealloc(pWins, pWins->cap + WINS_CAP);

    pWins->wins[pWins->size] = win;
    pWins->size++;
}

void wins_free(struct WINS* pWins)
{
    free(pWins->wins);
    pWins->size = 0;
    pWins->cap = 0;
}