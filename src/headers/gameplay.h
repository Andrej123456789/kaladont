#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <limits.h>

#include "c_string.h"
#include "c_vector.h"

/**
 * Struct containing settings
 * @param kaladont_allowed is word `kaladont` allowed
 * @param players number of players
 * @param words_path path to words file
 * @param words list of all available words
*/
typedef struct Start
{
    bool kaladont_allowed;
    uint64_t players;

    char words_path[NAME_MAX];
    char **words;
} Start;

/**
 * Struct containing gameplay informations
 * @param player id of current player
 * @param timeline used words in current game
*/
typedef struct Gameplay
{
    uint64_t player;
    cvector_vector_type(void*) timeline;
} Gameplay;

/**
 * Entry point to gameplay mechanics
 * @param _gameplay `Gameplay` struct
 * @param _start `Start` struct
*/
void gameplay(Gameplay* _gameplay, Start* _start);
