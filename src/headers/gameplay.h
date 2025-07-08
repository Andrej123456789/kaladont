/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Program's logic
 */

#pragma once

#include "c_vector.h"

#define WORD_LIMIT 62

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

/**
 * Struct containing player's informations
 * @param points number of points
*/
typedef struct Player
{
    char* name;
    uint64_t points;
} Player;

/**
 * Struct containing gameplay informations
 * @param current_word current word
 * @param player id of current player
 * @param network_points vector containing points in multiplayer mode
 * @param timeline used words in current game
 * @param words list of all available words
*/
typedef struct gameplay_T
{
    Player* players;
    uint16_t number_of_players;
    char* players_sequence;

    bool kaladont_allowed;
    bool wait_for_correct_word;

    char current_word[WORD_LIMIT + 1]; // +1 for '\0'
    uint16_t current_player;

    cvector_vector_type(char*) words_path;
    cvector_vector_type(char*) words;

    uint16_t depth;
} Gameplay;

/* ------------------------------------ */

/**
 * Moves an increment for current player
 * @param _gameplay `Gameplay` struct
 * @return void
*/
void next_player(Gameplay* _gameplay);

/**
 * Gets a random word from `words` list
 * @param _gameplay `Gameplay` struct
 * @return char*
*/
char* random_word(Gameplay* _gameplay);

/**
 * Reads points from players
 * @param players array of players
 * @param num_players number of players in the game
 * @return void
*/
void read_points(Player* players, uint16_t num_players);

/**
 * Sets a point to a player
 * @param _gameplay `Gameplay` struct
 * @return void
*/
void set_point(Gameplay* _gameplay);

/**
 * Gets a random word from `random_word`, push back it to `timeline` and copies it to `current_word`
 * @param _gameplay `Gameplay` struct
 * @return void
*/
void set_random_word(Gameplay* _gameplay);

/* ------------------------------------ */

/**
 * Unified gameplay mechanics
 * @param _gameplay `Gameplay` struct
 * @param input user input
 * @return int [0 - no point, 1 - give a point to the player, 
 * -1 - game finished with a point, -2 - game finished without a point]
*/
int gameplay(Gameplay* _gameplay, char* input);

/**
 * Entry point for game logic
 * @param _gameplay `Gameplay` struct
*/
void gameplay_entry(Gameplay* _gameplay);
