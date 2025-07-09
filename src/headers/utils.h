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
 * @return void
*/
void erase_element(cvector_vector_type(char*)* vec, char* str);

/**
 * # IMPROVE THIS FUNCTION
 * @brief Finds element in c_vector
 * @param vec vector
 * @param str string (element)
 * @return bool
*/
bool find_element(cvector_vector_type(char*)* vec, char* str);

/**
 * Gets all words starting with prefix from the words list
 * @param words words list
 * @param prefix substring
 * @return cvector_vector_type(char*)
*/
cvector_vector_type(char*) get_all_words_starting_on(cvector_vector_type(char*)* words, char* prefix);

/**
 * Gets first N characters
 * @param input string
 * @param N number of characters
 * @param buffer where result will be stored (buffer must have space for N+1 chars)
 * @return void
*/
void get_first_N_characters(const char* str, int N, char* buffer);

/**
 * Get last N characters
 * @param input string
 * @param N number of characters we are comparing
 * @param buffer where result will be stored (buffer must have space for N+1 chars)
 * @return void
*/
void get_last_N_characters(const char* str, int N, char* buffer);

/**
 * Finds minimum value between a and b
 * @param a first number
 * @param b second number
 * @return int16_t
*/
int16_t maximum(int16_t a, int16_t b);

/**
 * Finds maximum value between a and b
 * @param a first number
 * @param b second number
 * @return int16_t
*/
int16_t minimum(int16_t a, int16_t b);

/**
 * Removes whitespaces from a string
 * @param str string
 * @return char*
*/
char* trim_whitespace(char* str);
