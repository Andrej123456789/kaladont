#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <limits.h>

#include "c_string.h"
#include "c_vector.h"

typedef struct Start
{
    bool kaladont_allowed;
    uint64_t players;

    char words_path[NAME_MAX];
    char **words;
} Start;

typedef struct Gameplay
{
    uint64_t player;
    cvector_vector_type(void*) timeline;
} Gameplay;
