/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Implementation of computer player
 */

#pragma once

struct gameplay_T;

#define UNUSED(x) (void)(x)
#define WORD_LIMIT 62

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
 * @param best_word current best word
 * @param depth current depth
 * @return int16_t
*/
int16_t search(struct gameplay_T* _gameplay, char* best_word, uint16_t depth);

/**
 * Returns a word which computer played
 * @param _gameplay `Gameplay` struct
 * @param word variable where computer's word will be stored
 * @return void
*/
void computer_turn(struct gameplay_T* _gameplay, char* word);
