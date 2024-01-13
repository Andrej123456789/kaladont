#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "gameplay.h"
#include "utils.h"

struct gameplay_T;
struct start_T;

#define UNUSED(x) (void)(x)

#define WORD_LIMIT 32

typedef struct Evaluation
{
    char* bestWord;
} Evaluation;

/* ------------------------------------ */

/**
 * Evaluates a word
 * @param word word to be evaluated
 * @return int16_t
*/
int16_t evaluate_word(char* word);

/**
 * Searches for the best word, copies word into `evaluation` variable
 * @param _gameplay `Gameplay` struct
 * @param evaluation `Evaluation` struct
 * @param depth current depth
 * @return int16_t
*/
int16_t search(struct gameplay_T _gameplay, Evaluation* evaluation, uint16_t depth);

/**
 * Returns a word which computer played
 * @param _gameplay `Gameplay` struct
 * @param _start `Start` struct
 * @return char*
*/
char* computer_turn(struct gameplay_T* _gameplay, struct start_T* _start);
