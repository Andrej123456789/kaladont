#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <ctype.h>
#include "c_vector.h"

/**
 * # IMPROVE THIS FUNCTION
 * @brief Finds element in c_vector
 * @param vec vector
 * @param str string (element)
 * @return bool
*/
bool find_element(cvector_vector_type(char*) vec, char* str);

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
 * Remove whitespace from string
 * @param str string
 * @return char*
*/
char* trim_whitespace(char* str);
