#include "defs.h"

int round_whole(const float f)
{
    if (f - (float)((int)f) >= 0.5)	return (int)f + 1;
    else				return (int)f;
}