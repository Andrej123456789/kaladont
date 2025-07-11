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
    char buffer[3];
    get_last_N_characters(word, 2, buffer);

    if (strcmp(buffer, "nt") == 0)
    {
        return -1000;
    }

    int16_t combinations[11] = {-6, 3, -4, 1, 10, 1, 2, 3, 4, 5};

    int16_t result = combinations[rand() % 
        (11 - 0 + 1) + 0];

    return result;
}

int16_t search(Gameplay* _gameplay, char* best_word, uint16_t depth)
{
    if (depth == 0)
    {
        return evaluate_word(_gameplay->current_word);
    }

    char buffer[3];
    get_last_N_characters(_gameplay->current_word, 2, buffer);
    
    cvector_vector_type(char*) possible_words = NULL;
    possible_words = get_all_words_starting_on(&_gameplay->words, buffer);
    
    size_t words_size = cvector_size(possible_words);
    if (words_size == 0)
    {
        cvector_free(possible_words);
        return -1000;
    }
    
    int16_t bestEval = -1000; // basically, we give the worst value so we can "filter" out the best value for ourself
    for (size_t i = 0; i < words_size; i++)
    {
        strncpy(_gameplay->current_word, possible_words[i], WORD_LIMIT);
        _gameplay->current_word[WORD_LIMIT] = '\0';

        int16_t eval = -search(_gameplay, best_word, depth - 1);
        bestEval = maximum(eval, bestEval);

        // we can select a word only for the next move, not later ones
        if (bestEval == eval && depth == _gameplay->depth)
        {
            strncpy(best_word, possible_words[i], WORD_LIMIT);
            best_word[WORD_LIMIT] = '\0';
        }
    }

    cvector_free(possible_words);
    return bestEval;
}

int16_t search_debug(Gameplay* _gameplay, char* best_word, uint16_t depth, uint16_t level)
{
    // Print current node
    for (int i = 0; i < level; i++) printf("|  ");
    printf("↳ %s (depth: %u)\n", _gameplay->current_word, depth);

    if (depth == 0)
    {
        int16_t score = evaluate_word(_gameplay->current_word);

        for (int i = 0; i < level + 1; i++) printf("|  ");
        printf("Eval: %d\n", score);

        return score;
    }

    char buffer[3];
    get_last_N_characters(_gameplay->current_word, 2, buffer);

    cvector_vector_type(char*) possible_words = NULL;
    possible_words = get_all_words_starting_on(&_gameplay->words, buffer);

    size_t words_size = cvector_size(possible_words);
    if (words_size == 0)
    {
        for (int i = 0; i < level + 1; i++) printf("|  ");
        printf("Dead end\n");

        cvector_free(possible_words);
        return -1000;
    }

    int16_t bestEval = -1000; // basically, we give the worst value so we can "filter" out the best value for ourself
    for (size_t i = 0; i < words_size; i++)
    {
        strncpy(_gameplay->current_word, possible_words[i], WORD_LIMIT);
        _gameplay->current_word[WORD_LIMIT] = '\0';

        int16_t eval = -search_debug(_gameplay, best_word, depth - 1, level + 1);

        // Print child word and eval inline
        for (int j = 0; j < level + 1; j++) printf("|  ");
        printf("└─ %s → %d\n", possible_words[i], eval);

        bestEval = maximum(eval, bestEval);

        // we can select a word only for the next move, not later ones
        if (bestEval == eval && depth == _gameplay->depth)
        {
            strncpy(best_word, possible_words[i], WORD_LIMIT);
            best_word[WORD_LIMIT] = '\0';
        }
    }

    cvector_free(possible_words);

    // Print best eval for this node
    for (int i = 0; i < level; i++) printf("|  ");
    printf("Best eval for \"%s\": %d\n", _gameplay->current_word, bestEval);

    return bestEval;
}

void computer_turn(Gameplay* _gameplay, char* word)
{
    char best_word[WORD_LIMIT + 1];     // +1 for '\0'
    char original[WORD_LIMIT + 1];      // +1 for '\0'

    strncpy(original, _gameplay->current_word, WORD_LIMIT);
    original[WORD_LIMIT] = '\0';

    search(_gameplay, best_word, _gameplay->depth);

    strncpy(_gameplay->current_word, original, WORD_LIMIT);
    _gameplay->current_word[WORD_LIMIT] = '\0';

    strncpy(word, best_word, WORD_LIMIT);
    word[WORD_LIMIT] = '\0';
}
