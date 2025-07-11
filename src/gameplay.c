/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Program's logic
 */

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "headers/c_vector.h"
#include "headers/computer.h"
#include "headers/gameplay.h"
#include "headers/server.h"
#include "headers/utils.h"

void next_player(Gameplay* _gameplay)
{
    _gameplay->current_player += 1;
    if (_gameplay->current_player >= _gameplay->number_of_players)
    {
        _gameplay->current_player = 0;
    }
}

char* random_word(Gameplay* _gameplay)
{
    srand(time(0));

    size_t size = cvector_size(_gameplay->words);
    if (size == 0)
    {
        return "<error>";
    }

    size_t pos = rand() % size;
    return _gameplay->words[pos];
}

void read_points(Gameplay* _gameplay, Network* _network)
{
    printf("Number of points of each player: \n");
    if (_network->enabled) { broadcast(_gameplay, "Number of points of each player: \n"); }

    for (uint16_t i = 0; i < _gameplay->number_of_players; i++)
    {
        printf("Player %u has %lu points. \n", i, _gameplay->players[i].points);

        if (_network->enabled)
        {
            broadcast(_gameplay, "Player %u has %lu points. \n", i, _gameplay->players[i].points);
        }
    }
}

void set_point(Gameplay* _gameplay)
{
    _gameplay->players[_gameplay->current_player].points += 1;
}

void set_random_word(Gameplay* _gameplay)
{
    char* rand_word = random_word(_gameplay);

    strncpy(_gameplay->current_word, rand_word, WORD_LIMIT);
    _gameplay->current_word[WORD_LIMIT] = '\0';

    erase_element(&_gameplay->words, rand_word);
}

/* ------------------------------------ */

int gameplay(Gameplay* _gameplay, Network* _network, char* input)
{
    if (strcmp(input, "exit") == 0)
    {
        printf("Exiting...\n");
        if (_network->enabled) { broadcast(_gameplay, "Exiting...\n"); }

        return -2;
    }

    else if (strcmp(input, "next") == 0)
    {
        printf("Player %u skipping, no points!\n", _gameplay->current_player);
        if (_network->enabled)
        {
            broadcast(_gameplay, "Player %u skipping, no points!\n", _gameplay->current_player);
        }

        return 0;
    }

    char first_buffer[3];
    char last_buffer[3];

    get_first_N_characters(input, 2, first_buffer);
    get_last_N_characters(_gameplay->current_word, 2, last_buffer);

    if (strcmp(first_buffer, last_buffer) == 0 && 
        find_element(&_gameplay->words, input)  && 
        strlen(input) > 2)
    {
        erase_element(&_gameplay->words, input);

        get_last_N_characters(input, 2, last_buffer);
        if (strcmp(last_buffer, "nt") == 0)
        {
            if (strcmp(input, "kaladont") == 0 && _gameplay->kaladont_allowed == false)
            {
                printf("Game ended... \n");
                if (_network->enabled) { broadcast(_gameplay, "Game ended...\n"); }

                return -2;
            }

            printf("Player %u received a point!\n", _gameplay->current_player);
            printf("Game ended... \n");

            if (_network->enabled) { broadcast(_gameplay, "Player %u received a point!\n", _gameplay->current_player); }
            if (_network->enabled) { broadcast(_gameplay, "Game ended...\n"); }

            return -1;
        }

        strncpy(_gameplay->current_word, input, WORD_LIMIT);
        _gameplay->current_word[WORD_LIMIT] = '\0';

        printf("Player %u received a point!\n", _gameplay->current_player);
        if (_network->enabled)
        {
            broadcast(_gameplay, "Player %u received a point!\n", _gameplay->current_player);
        }

        return 1;
    }

    printf("Player %u didn't receive a point!\n", _gameplay->current_player);
    if (_network->enabled)
    {
        broadcast(_gameplay, "Player %u didn't receive a point!\n", _gameplay->current_player);
    }

    return 0;
}

void gameplay_entry(Gameplay* _gameplay,Network* _network)
{
    bool game_finished = false;

    _gameplay->current_player = 0;
    _gameplay->players = calloc(_gameplay->number_of_players, sizeof(Player));

    if (_gameplay->players == NULL)
    {
        printf("Error during memory allocation!\nExiting...\n");
        return;
    }

    char user_input[WORD_LIMIT + 1];
    set_random_word(_gameplay);

    uint16_t expected_clients = 0;
    for (uint16_t i = 0; _gameplay->players_sequence[i] != '\0'; i++)
    {
        if (_gameplay->players_sequence[i] == '2')
        {
            expected_clients++;
        }
    }

    int listener_fd = -1;
    if (_network->enabled == true)
    {
        listener_fd = net_start_server(_network->port, expected_clients);
    }

    /* Wait for all clients to join the game */
    if (_network->enabled == true)
    {
        uint16_t connected_clients = 0;
        while (connected_clients < expected_clients)
        {
            connected_clients = 0; // reset counter so it counts all connected clients correctly
            if (listener_fd >= 0) 
            {
                net_accept_clients(listener_fd, _gameplay);
                net_poll_clients(_gameplay);
            }

            for (uint16_t i = 0; i < _gameplay->number_of_players; i++) 
            {
                if (_gameplay->players[i].network_player.sockfd > 0) 
                {
                    connected_clients++;
                }
            }
        }
    }

    while (!game_finished)
    {
        if (listener_fd >= 0) 
        {
            net_accept_clients(listener_fd, _gameplay);
            net_poll_clients(_gameplay);
        }

        if (cvector_size(_gameplay->words) == 0)
        {
            printf("No words left!\nExiting...\n");
            if (_network->enabled) { broadcast(_gameplay, "No words left!\nExiting...\n"); }

            read_points(_gameplay, _network);
            game_finished = true;
        }

        printf("Previous word is: %s\n", _gameplay->current_word);
        if (_network->enabled)
        {
            broadcast(_gameplay, "Previous word is: %s\n", _gameplay->current_word);
        }

        switch (_gameplay->players_sequence[_gameplay->current_player])
        {
            case '1': // computer player
                computer_turn(_gameplay, user_input);
                break;

            case '2': // network player
                NetworkPlayer *np =
                    &_gameplay->players[_gameplay->current_player].network_player;

                const int TIME_LIMIT_SEC = 30;
                const int POLL_SLEEP_US = 10000; // 10 ms

                time_t deadline = time(NULL) + TIME_LIMIT_SEC;

                /* poll until we get a full line or the timer expires */
                while (!np->ready && !game_finished && time(NULL) < deadline)
                {
                    net_poll_clients(_gameplay);   /* non‑blocking socket pump  */
                    usleep(POLL_SLEEP_US);         /* nap to save CPU */
                }

                if (np->ready)
                {
                    strncpy(user_input, np->inbuf, WORD_LIMIT);
                    user_input[WORD_LIMIT] = '\0';
                }

                else
                {
                    strcpy(user_input, "<timeout>");
                }

                /* reset buffer */
                np->inbuf[0] = '\0';
                np->ready = false;

                break;

            default:
                char custom_format[6];
                sprintf(custom_format, "%%%ds", WORD_LIMIT);

                printf("Player %u: ", _gameplay->current_player);
                scanf(custom_format, user_input);

                break;
        }

        printf("Player %u played: %s\n", _gameplay->current_player, user_input);
        if (_network->enabled)
        {
            broadcast(_gameplay, "Player %u played: %s\n", _gameplay->current_player, user_input);
        }

        int result = gameplay(_gameplay, _network, user_input);
        switch (result)
        {
            case 1:
                set_point(_gameplay);
                break;

            case -1:
                set_point(_gameplay);
                set_point(_gameplay); // last person gets one more point

                read_points(_gameplay, _network);
                game_finished = true;

                break;

            case -2:
                read_points(_gameplay, _network);
                game_finished = true;

                break;
        }

        if (!(result == 0 && _gameplay->wait_for_correct_word == true))
        {
            next_player(_gameplay);
        }
    }
}
