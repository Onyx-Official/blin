#ifndef _OOE_ERR_H_
#define _OOE_ERR_H_

#include <stdio.h>
#include <stdlib.h>

void error(const char* msg)
{
    perror(msg);
    exit(0);
}

#endif