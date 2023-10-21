#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "server.h"

#include "c_string.h"
#include "c_vector.h"

/**
 * Struct containing settings
 * @param kaladont_allowed is word `kaladont` allowed
 * @param players number of players
 * @param words_path path to words file
*/
typedef struct Start
{
    bool kaladont_allowed;
    uint64_t players;

    cvector_vector_type(char*) words_path;
} Start;

/**
 * Struct containing gameplay informations
 * @param current_word current word
 * @param player id of current player
 * @param timeline used words in current game
 * @param words list of all available words
*/
typedef struct Gameplay
{
    char* current_word;
    uint64_t player;
    cvector_vector_type(char*) timeline;
    cvector_vector_type(char*) words;
} Gameplay;

/**
 * Struct containing player's informationas
 * @param points number of points
*/
typedef struct Player
{
    uint64_t points;
} Player;

/**
 * Struct containing network informations
 * @param enabled is multiplayer enabled
 * @param port port number
*/
typedef struct Network
{
    bool enabled;
    uint16_t port;
} Network;

/* ------------------------------------ */

/**
 * # IMPROVE THIS FUNCTION
 * @brief Finds element in c_vector
 * @param vec vector
 * @param str string (element)
 * @return bool
*/
bool find_element(cvector_vector_type(char*) vec, char* str);

/**
 * Get last N characters
 * @param input string
 * @param N number of characters we are comparing
 * @return char*
*/
char* get_last_N_characters(const char* input, int N);

/**
 * Get first N characters
 * @param input string
 * @param N number of characters we are comparing
 * @return char*
*/
char* get_first_N_characters(const char* input, int N);

/* ------------------------------------ */

/**
 * Set current player to next player
 * @param _gameplay `Gameplay` struct
 * @param _start `Start` struct
*/
void next_player(Gameplay* _gameplay, Start* _start);

/**
 * Get random word from `words` list
 * @param _gameplay `Gameplay` struct
 * @return char*
*/
char* random_word(Gameplay* _gameplay);

/**
 * Get random word from `random_word`, push back it to `timeline` and copy it to `current_word`
 * @param _gameplay `Gameplay` struct
*/
void set_random_word(Gameplay* _gameplay);

/**
 * Entry point for multiplayer gameplay
 * @param _gameplay `Gameplay` struct
 * @param _network `Network` struct
 * @param _start `Start` struct
*/
void network_gameplay(Gameplay* _gameplay, Network* _network, Start* _start);

/**
 * Entry point for local gameplay
 * @param _gameplay `Gameplay` struct
 * @param _start `Start` struct
*/
void local_gameplay(Gameplay* _gameplay, Start* _start);
