/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Server code
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

struct Gameplay;
struct Player;

/**
 * Starts a server
 * @param port port number
 * @param max_players maximum number of players server can receive
 * @return int
 */
int net_start_server(uint16_t port, uint16_t max_players);

/**
 * Accepts a client's connection to the server
 * @param listener_fd file descriptor
 * @param g `Gameplay` struct
 * @return void
 */
void net_accept_clients(int listener_fd, struct Gameplay* g);

/**
 * Polls input from clients
 * @param g `Gameplay` struct
 * @return void
 */
void net_poll_clients(struct Gameplay* g);

/**
 * Sends a message to one player
 * @param p player
 * @param fmt message
 * @return void
 */
void send_to_player(struct Player* p, const char* fmt, ...);

/**
 * Sends a message to all players
 * @param g `Gameplay` struct
 * @param fmt message
 * @param void
 */
void broadcast(struct Gameplay* g, const char* fmt, ...);
