/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Program's logic
 */

#pragma once

#include <stdbool.h>

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
 * Struct containing player's network data
 * @param sockfd socket number, <= 0 is free slot
 * @param inbuf player's input, +1 is for '\0'
 * @param ready did player send an input
 */
typedef struct NetworkPlayer {
    int   sockfd;
    char  inbuf[WORD_LIMIT + 1];
    bool  ready;
} NetworkPlayer;

/**
 * Struct containing player's informations
 * @param points number of points
 * @param network_player network data
*/
typedef struct Player
{
    uint64_t points;
    NetworkPlayer network_player;
} Player;

/**
 * Struct containing gameplay informations
 * @param players array of struct `Player`
 * @param number_of_players number of players in the game
 * @param players_sequence type of players (0 - local, 1 - computer, 2 - network)
 * 
 * @param kaladont_allowed is it allowed to say word `kaladont`
 * @param wait_for_correct_word should we wait for player to say valid word
 * 
 * @param current_word current word
 * @param current_player number of current player, position in array `players`
 * 
 * @param words_path paths to the files containing files
 * @param words cached words in memory
 * 
 * @param depth depth of minmax search
*/
typedef struct Gameplay
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
 * @param _gameplay `Gameplay` struct
 * @param _network `Network` struct
 * @return void
*/
void read_points(Gameplay* _gameplay, Network* _network);

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
 * @param _network `Network` struct
 * @param input user input
 * @return int [0 - no point, 1 - give a point to the player, 
 * -1 - game finished with a point, -2 - game finished without a point]
*/
int gameplay(Gameplay* _gameplay, Network* _network, char* input);

/**
 * Entry point for game logic
 * @param _gameplay `Gameplay` struct
 * @param _network `Network` struct
 * @return void
*/
void gameplay_entry(Gameplay* _gameplay, Network* _network);
