/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Program's logic
 */

#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "headers/c_vector.h"
#include "headers/computer.h"
#include "headers/gameplay.h"
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
    /* Seed the random number generator with the current time */
    srand(time(0));

    /* Get random vector position */
    size_t pos = (rand() % (cvector_size(_gameplay->words) - 0 + 1)) + 0;

    /* Return string at selected position */
    return _gameplay->words[pos];
}

void read_points(Player* players, uint16_t num_players)
{
    printf("Number of points of each player: \n");
    for (size_t i = 0; i < num_players; i++)
    {
        printf("Player %lu has %lu points. \n", i, players[i].points);
    }
}

void set_point(Gameplay* _gameplay)
{
    _gameplay->players[_gameplay->current_player].points += 1;
}

void set_random_word(Gameplay* _gameplay)
{
    char* rand_word = random_word(_gameplay);
    strcpy(_gameplay->current_word, rand_word);
}

/* ------------------------------------ */

int gameplay(Gameplay* _gameplay, char* input)
{
    if (strcmp(input, "exit") == 0)
    {
        printf("Exiting...\n");
        return -2;
    }

    else if (strcmp(input, "next") == 0)
    {
        printf("You don't have a point!\n");
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
                return -2;
            }

            printf("You have one point!\n");
            printf("Game ended... \n");

            return -1;
        }

        strcpy(_gameplay->current_word, input);
        return 1;
    }

    printf("You don't have a point!\n");
    return 0;
}

void gameplay_entry(Gameplay* _gameplay,Network* _network)
{
    bool game_finished = false;

    _gameplay->current_player = 0;
    _gameplay->players = calloc(_gameplay->number_of_players, sizeof(Player));

    char user_input[WORD_LIMIT + 1];
    set_random_word(_gameplay);

    if (_network->enabled == true)
    {
        /* start a server */
    }

    while (!game_finished)
    {
        if (_gameplay->players_sequence[_gameplay->current_player] == '1') // computer player
        {
            computer_turn(_gameplay, user_input);
            printf("Player %d played: %s\n", _gameplay->current_player, user_input);
        }

        else if (_gameplay->players_sequence[_gameplay->current_player] == '2') // network player
        {
            /* receive a message from the server */
        }

        else
        {
            char custom_format[6];
            sprintf(custom_format, "%%%ds", WORD_LIMIT);

            printf("Previous word is: %s\n", _gameplay->current_word);

            printf("Player %u: ", _gameplay->current_player);
            scanf(custom_format, user_input);
        }

        int result = gameplay(_gameplay, user_input);
        switch (result)
        {
            case 1:
                set_point(_gameplay);
                break;

            case -1:
                set_point(_gameplay);
                set_point(_gameplay); // last person gets one more point

                read_points(_gameplay->players, _gameplay->number_of_players);
                game_finished = true;

                break;

            case -2:
                read_points(_gameplay->players, _gameplay->number_of_players);
                game_finished = true;

                break;
        }

        if (!(result == 0 && _gameplay->wait_for_correct_word == true))
        {
            next_player(_gameplay);
        }
    }
}
