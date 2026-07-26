/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Helper functions
 */

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/utils.h"

void erase_element(cvector_vector_type(char*)* vec, char* str)
{
    for (size_t i = 0; i < cvector_size(*vec); i++)
    {
        if (strcmp(str, (*vec)[i]) == 0)
        {
            free((*vec)[i]);
            cvector_erase(*vec, i);

            break;
        }
    }
}

bool find_element(cvector_vector_type(char*)* vec, char* str)
{
    for (size_t i = 0; i < cvector_size(*vec); i++)
    {
        if (strcmp(str, (*vec)[i]) == 0)
        {
            return true;
        }
    }
    
    return false;
}

cvector_vector_type(char*) get_all_words_starting_on(cvector_vector_type(char*)* words, char* prefix)
{
    cvector_vector_type(char*) my_words = NULL;

    for (size_t i = 0; i < cvector_size(*words); i++)
    {
        char buffer[3];
        get_first_N_characters((*words)[i], 2, buffer);
 
        if (strcmp(buffer, prefix) == 0)
        {
            cvector_push_back(my_words, (*words)[i]);
        }
    }

    return my_words;
}

void get_first_N_characters(const char* str, int N, char* buffer) 
{
    int len = strlen(str);
    if (N > len) N = len;
    strncpy(buffer, str, N);
    buffer[N] = '\0';
}

void get_last_N_characters(const char* str, int N, char* buffer) 
{
    int len = strlen(str);
    if (N > len) N = len;
    strncpy(buffer, str + len - N, N);
    buffer[N] = '\0';
}

int16_t maximum(int16_t a, int16_t b) 
{
    return (a > b) ? a : b;
}

int16_t minimum(int16_t a, int16_t b) 
{
    return (a < b) ? a : b;
}

char* trim_whitespace(char* str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if( frontp != str && endp == frontp )
            *str = '\0';
    else if( str + len - 1 != endp )
            *(endp + 1) = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
        while( *frontp ) { *endp++ = *frontp++; }
        *endp = '\0';
    }

    return str;
}
