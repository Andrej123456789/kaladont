/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Helper functions
 */

#pragma once

#include "c_vector.h"

/**
 * # IMPROVE THIS FUNCTION
 * @brief Erases element in c_vector
 * @param vec vector
 * @param str string (element)
 * @return cvector_vector_type
*/
void erase_element(cvector_vector_type(char*)* vec, char* str);

/**
 * # IMPROVE THIS FUNCTION
 * @brief Finds element in c_vector
 * @param vec vector
 * @param str string (element)
 * @return bool
*/
bool find_element(cvector_vector_type(char*) vec, char* str);

/**
 * Get all words from words list starting on specified substring
 * @param words words list
 * @param prefix substring
*/
cvector_vector_type(char*) get_all_words_starting_on(cvector_vector_type(char*) words, char* prefix);

/**
 * Get first N characters
 * @param input string
 * @param N number of characters we are comparing
 * @return char*
*/
char* get_first_N_characters(const char* input, int N);

/**
 * Get last N characters
 * @param input string
 * @param N number of characters we are comparing
 * @return char*
*/
char* get_last_N_characters(const char* input, int N);

/**
 * Find minimum number between a and b
 * @param a first number
 * @param b second number
 * @return int16_t
*/
int16_t maximum(int16_t a, int16_t b);

/**
 * Find maximum number between a and b
 * @param a first number
 * @param b second number
 * @return int16_t
*/
int16_t minimum(int16_t a, int16_t b);

/**
 * Remove whitespace from string
 * @param str string
 * @return char*
*/
char* trim_whitespace(char* str);
