#include "headers/utils.h"

bool find_element(cvector_vector_type(char*) vec, char* str)
{
    for (size_t i = 0; i < cvector_size(vec); i++)
    {
        if (strcmp(str, vec[i]) == 0)
        {
            return true;
        }
    }
    
    return false;
}

char* get_first_N_characters(const char* input, int N)
{
    char result[255];

    if (N <= 0) 
    {
        result[0] = '\0';
        return NULL;
    }

    strncpy(result, input, N);
    result[N] = '\0';

    return strdup(result);
}

char* get_last_N_characters(const char* input, int N)
{
    char result[255];

    if (N <= 0) 
    {
        result[0] = '\0';
        return NULL;
    }

    int length = strlen(input);
    if (length < N) 
    {
        N = length;
    }

    strncpy(result, input + (length - N), N);
    result[N] = '\0';

    return strdup(result);
}

char* trim_whitespace(char* str)
{
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // All spaces?
    return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character

    if (strlen(end) < 1)
    {
        return str;
    }

    end[1] = '\0';
    return str;
}
