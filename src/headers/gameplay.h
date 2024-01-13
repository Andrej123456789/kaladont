#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "server.h"
#include "utils.h"

#include "computer.h"
#include "c_vector.h"

struct networkPlayer_T;

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
    char* current_word;
    uint64_t player;
    cvector_vector_type(struct networkPlayer_T*) network_points;
    cvector_vector_type(char*) timeline;
    cvector_vector_type(char*) words;
} Gameplay;

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
 * Struct containing network player's informations
 * @param name player's name
 * @param points number of points
*/
typedef struct networkPlayer_T
{
    char* name;
    uint64_t points;
} NetworkPlayer;


/**
 * Struct containing player's informationas
 * @param points number of points
*/
typedef struct Player
{
    uint64_t points;
} Player;

/**
 * Struct containing settings
 * @param kaladont_allowed is word `kaladont` allowed
 * @param players number of players
 * @param depth depth of search in computer player
 * @param sequence sequence containing human and computer players 
 * @param words_path path to words file
*/
typedef struct start_T
{
    bool kaladont_allowed;
    uint64_t players;
    uint16_t depth;

    cvector_vector_type(char) sequence;
    cvector_vector_type(char*) words_path;
} Start;

/* ------------------------------------ */

/**
 * Sets a current player to next player
 * @param _gameplay `Gameplay` struct
 * @param _start `Start` struct
*/
void next_player(Gameplay* _gameplay, Start* _start);

/**
 * Gets a random word from `words` list
 * @param _gameplay `Gameplay` struct
 * @return char*
*/
char* random_word(Gameplay* _gameplay);

/**
 * Reads points from local players
 * @param players players list
 * @param num_players number of players in game
*/
void read_points(Player players[], uint64_t num_players);

/**
 * Sets points to a local player
 * @param _gameplay `Gameplay` struct
 * @param players players list
*/
void set_point(Gameplay* _gameplay, Player players[]);

/**
 * Gets a random word from `random_word`, push back it to `timeline` and copies it to `current_word`
 * @param _gameplay `Gameplay` struct
*/
void set_random_word(Gameplay* _gameplay);

/* ------------------------------------ */

/**
 * Unified gameplay mechanics
 * @param _gameplay `Gameplay` struct
 * @param np network players
 * @param input user input
 * @param network is multiplayer mode enabled
*/
int gameplay(Gameplay* _gameplay, ClientList* np, char* input, bool network);

/**
 * Entry point for multiplayer gameplay
 * @param _gameplay `Gameplay` struct
 * @param _network `Network` struct
*/
void network_gameplay(Gameplay* _gameplay, Network* _network);

/**
 * Entry point for local gameplay
 * @param _gameplay `Gameplay` struct
 * @param _start `Start` struct
*/
void local_gameplay(Gameplay* _gameplay, Start* _start);
