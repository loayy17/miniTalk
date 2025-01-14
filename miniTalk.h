#ifndef MINI_TALK_H
#define MINI_TALK_H

#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "./Libft/libft.h"

typedef struct s_mini
{
    char character;
    int counter;
    int indicator;
    int length;
    char *buffer;
    int oncetime;
    int index;
} t_mini;

t_mini g_mini;

#endif