/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Implementation of computer player
 */

#pragma once

struct Gameplay;

#define UNUSED(x) (void)(x)
#define WORD_LIMIT 62

/* ------------------------------------ */

/**
 * ### BROKEN! NOT IMPLEMENTED BECAUSE KALADONT IS NOT
 * TWO-PLAYER ZERO-SUM GAME
 * @brief Evaluates a word
 * @param word word to be evaluated
 * @return int16_t
*/
int16_t evaluate_word(char* word);

/**
 * ### BROKEN! YOU CANNOT USE NEGAMAX ON N-PLAYER NON-ZERO GAME
 * @brief Searches for the best word, copies the result into `best_word` variable
 * @param _gameplay `Gameplay` struct
 * @param best_word variable where result is stored
 * @param depth current depth
 * @return int16_t
*/
int16_t search(struct Gameplay* _gameplay, char* best_word, uint16_t depth);

/**
 * ### BROKEN! YOU CANNOT USE NEGAMAX ON N-PLAYER NON-ZERO GAME
 * @brief Searches for the best word, copies the result into `best_word` variable,
 * and prints the steps.
 * @param _gameplay `Gameplay` struct
 * @param best_word variable where result is stored
 * @param depth current depth
 * @param level current level
 * @return int16_t
*/
int16_t search_debug(struct Gameplay* _gameplay, char* best_word, uint16_t depth, uint16_t level);

/**
 * Returns a word which computer played
 * @param _gameplay `Gameplay` struct
 * @param word variable where computer's word will be stored
 * @return void
*/
void computer_turn(struct Gameplay* _gameplay, char* word);
