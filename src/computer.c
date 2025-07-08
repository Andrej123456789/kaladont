/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Implementation of computer player
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "headers/computer.h"
#include "headers/gameplay.h"
#include "headers/utils.h"

int16_t evaluate_word(char* word)
{
    UNUSED(word);

    int16_t combinations[11] = {-6, 3, -4, 1, 10, 1, 2, 3, 4, 5};

    int16_t result = combinations[rand() % 
        (11 - 0 + 1) + 0];

    return result;
}

int16_t search(Gameplay* _gameplay, char* best_word, uint16_t depth)
{
    int16_t bestEval = 1000;    // -1000 if first node white; +1000 if first node black
                                // basically, we give worst value so we can "filter" real value

    if (depth == 0)
    {
        return evaluate_word(_gameplay->current_word);
    }

    cvector_vector_type(char*) possible_words = NULL;
    possible_words = get_all_words_starting_on(_gameplay->words, get_last_N_characters(_gameplay->current_word, 2));

    size_t words_size = cvector_size(possible_words);
    if (words_size == 0)
    {
        cvector_free(possible_words);
        return -1000;
    }

    for (size_t i = 0; i < words_size; i++)
    {
        strcpy(_gameplay->current_word, possible_words[i]);

        int16_t eval = -search(_gameplay, best_word, depth - 1);
        bestEval = minimum(eval, bestEval);

        if (bestEval == eval)
        {
            strcpy(best_word, possible_words[i]);
        }
    }

    cvector_free(possible_words);
    return bestEval;
}

void computer_turn(struct gameplay_T* _gameplay, char* word)
{
    char best_word[WORD_LIMIT + 1];     // +1 for '\0'
    char original[WORD_LIMIT + 1];      // +1 for '\0'

    strcpy(original, _gameplay->current_word);
    search(_gameplay, best_word, _gameplay->depth);

    strcpy(_gameplay->current_word, original);
    strcpy(word, best_word);
}
