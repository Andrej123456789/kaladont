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
