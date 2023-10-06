#ifndef DENX_CSTRING
#define DENX_CSTRING

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CSTRING_NPOS ((size_t)-1)

/**********************************************/
/*
/* CString Function Members Definition
/*
/**********************************************/

// Create an empty CString object and returns a pointer to its data.
void* CStringCreate();

// Destroys the CString and returns a 0(no error) or 1(error).
size_t CStringDestroy(void*);

// Calculates the length of the CString and returns it.
size_t CStringLength(void*);

// Calculates the size of the CString and returns it. Note: unlike `CStringLength`, this will calculate the actual size of the string in memory.
size_t CStringSize(void*);

// Calculates the capacity of the CString object and returns it.
size_t CStringCapacity(void*);

// Returns a pointer to a character of the string or `NULL` if the index isn't valid.
char* CStringAt(void*, size_t);

// Clears the CString. This won't affect its capacity and size.
void CStringClear(void*);

// Returns a pointer to the first character of the CString.
void* CStringBegin(void*);

// Returns a pointer to the last character of the CString.
void* CStringEnd(void*);

// Returns a pointer to the last character of the CString(reversed beginning).
void* CStringRBegin(void*);

// Returns a pointer to the first character of the CString(reversed ending).
void* CStringREnd(void*);

// Copies the content of the string passed as argument to the CString. Returns the number of bytes copied.
size_t CStringEqual(void*, const char*);

// Returns the actual string of the CString object.
const char* CStringData(void*);

// Check if the CString is empty. Returns 0(not empty) or 1(empty). If CString is `NULL`, 1 is returned.
size_t CStringEmpty(void*);

// Returns a pointer to the first character of the CString or NULL.
char* CStringFront(void*);

// Returns a pointer to the last character of the CString or NULL.
char* CStringBack(void*);

// Returns the maximum number of characters a CString can hold. For the time being, this function will return 0. At the moment I don't know where could I find the maximum number of characters of a string in C.
const size_t CStringMaxSize();

// Reserves the amount of bytes specified. Returns the new capacity of the CString.
// - If the amount of bytes to be reserved are less then `CStringCapacity`, this is a shrink request.
// - If the amount of bytes to be reserved are less then `CStringSize`, this is a `shrink-to-fit` request.
size_t CStringReserve(void*, size_t);

// Shrinks the CString to fit. This will make the capacity of the CString match the size of the CString. Returns the number of bytes shrinked.
// If the size of the CString already matches the capacity of the CString, nothing is done(0 is returned).
size_t CStringShrinkToFit(void*);

// Inserts a character at the given location in the CString. Returns 0(character inserted) or 1(error).
// Any index greater than the length/size/capacity of the CString is interpreted as: insert the character at the end.
size_t CStringInsert(void*, char, size_t);

// Erases a character at the given location. Returns 0(character deleted) or 1(error, invalid position).
size_t CStringErase(void*, size_t);

// Insert a single character at the end of the CString. Returns 0(no errors) or 1(error).
size_t CStringPushBack(void*, char);

// Pops back the last character. Effectively erases the last character of the CString. Returns 0(no errors) or 1(error).
size_t CStringPopBack(void*);

// Insert a single character at the end of the CString. Returns 0(no errors) or 1(error).
size_t CStringAppend(void*, char);

// Compares the two CStrings. Returns 0, N<0 or N>0.
// - N<0 if the first character that does not match has a lower value in the first CString than in the second CString.
// - 0 if the contents of both CStrings are equal.
// - N>0 if the first character that does not match has a greater value in the first CString than in the second CString.
// - If either the first CString or the second CString is a NULL pointer, -1 is returned.
int CStringCompare(void*, void*);

// Compares the first character of the CString with the given character. Returns 1(starts with) or 0(not starting with).
size_t CStringStartsWith(void*, char);

// Compares the last character of the CString with the given character. Returns 1(ends with) or 0(not ending with).
size_t CStringEndsWith(void*, char);

// Replaces the portion of the string that the begins at the given position and spans for the given string's lenght.
// Returns the number of bytes written on the CString.
size_t CStringReplace(void*, const char*, size_t, size_t);

// Returns a CString object with its value initialized to a copy of a substring
// of the given CString object.
// Returns a CString object(valid positions) or NULL(invalid positions or NULL CString object).
void* CStringSubStr(void*, size_t, size_t);

// Copies the content of the second CString object to the first CString object.
// Returns the number of bytes copied.
// Note: The content of the first CString object is deleted.
size_t CStringCopy(void*, void*);

// Resizes the CString to a length of N characters.
// If N is smaller than the current CString length, the current value is shortened to its first N character , removing the characters beyond the Nth.
// If n is greater than the current CString length, the current content is extended by inserting at the end as many characters as needed to reach a size of N. New elements are all initialized with the value of the given character.
// Returns 0(no errors) or 1(error)
size_t CStringResize(void*, size_t, char);

// Swaps the content of two CStrings.
// Returns 0(no errors) or 1(error).
size_t CStringSwap(void*, void*);

// Finds the first sub-strings equal to the given character sequence.
// Returns the position of the first match or `CSTRING_NPOS` if no match.
size_t CStringFind(void*, const char*);

// Find the first sub-string equal to the given character sequence starting from the end of the
// CString.
// REturns the position of the first match or `CSTRING_NPOS` if no match.
size_t CStringRFind(void*, const char*);

// Finds the first sub-strings equal to the given character sequence
// Returns the position of the first match or `CSTRING_NPOS` if no match.
size_t CStringFindFirstOf(void*, const char*);

// Find the first sub-strings equal to the given character sequence starting from the end of the
// CString.
// Returns the position of the first match or `CSTRING_NPOS` if no match.
size_t CStringFindLastOf(void*, const char*);

// Find the first character not equal to the given character sequence.
// Returns the position of the first non-matching character or `CSTRING_NPOS` if all matched.
size_t CStringFindFirstNotOf(void*, const char*);

// Finds the first character not equal to the given character sequence starting from the end of the
// CString.
// Returns the position of the first non-matching character or `CSTRING_NPOS` if all matched.
size_t CStringFindLastNotOf(void*, const char*);

/**********************************************/
/*
/* CString Structures and Utility Macros
/*
/**********************************************/

typedef struct __denx__cstring_object
{
    char* string;

    size_t length;

    size_t size;

    size_t capacity;

    void* begin;

    void* end;

}denx_cstring;

#define CSTRING_REF(ptr) ((denx_cstring*)(ptr))
#define CSTRING_LEN(ptr) strlen(CSTRING_REF(ptr)->string)

/* __unix__ is usually defined by compilers targeting Unix systems */
#if defined(__unix__) || defined(__linux__)
    #define CSTRING_STRCAT(_Destination, _SizeInBytes, _Source) \
                            strcat(_Destination, _Source)
    #define CSTRING_STRCPY(_Destination, _SizeInBytes, _Source) \
                            strcpy(_Destination, _Source)
    #define CSTRING_MEMCPY(_Destination, _DestinationSize, _Source, _SourceSize) \
                            memcpy(_Destination, _Source, _SourceSize)
/* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #define CSTRING_STRCAT(_Destination, _SizeInBytes, _Source) \
                            strcat_s(_Destination, _SizeInBytes, _Source)
    #define CSTRING_STRCPY(_Destination, _SizeInBytes, _Source) \
                            strcpy_s(_Destination, _SizeInBytes, _Source)
    #define CSTRING_MEMCPY(_Destination, _DestinationSize, _Source, _SourceSize) \
                            memcpy_s(_Destination, _DestinationSize, _Source, _SourceSize)
#else
    #error "unknown compiler or platform. supported platforms are: `Linux` and `Windows`"
#endif

// Increases the capacity of the CString using logarithmic scaling.
void denx_cstring_IncreaseCapacity(void*);

/**********************************************/
/*
/* CString Function Members Implementation
/*
/**********************************************/

void* CStringCreate()
{
    denx_cstring* string = (denx_cstring*)calloc(1, sizeof(denx_cstring));
    return (void*)string;
}

size_t CStringDestroy(void* ptr)
{
    if(ptr != NULL)
    {
        if(CSTRING_REF(ptr)->string != NULL)
        {
            free(CSTRING_REF(ptr)->string);
        }
        free(ptr);
        return 0;
    }
    return 1;
}

size_t CStringLength(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_LEN(ptr);
    }
    return 0;
}

size_t CStringSize(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->size;
    }
    return 0;
}

size_t CStringCapacity(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->capacity;
    }
    return 0;
}

char* CStringAt(void* ptr, size_t index)
{
    if(ptr != NULL && index < CSTRING_REF(ptr)->size)
    {
        return &CSTRING_REF(ptr)->string[index];
    }
    return NULL;
}

void CStringClear(void* ptr)
{
    if(ptr != NULL)
    {
        memset(CSTRING_REF(ptr)->string, 0, CSTRING_REF(ptr)->capacity);
        CSTRING_REF(ptr)->size = 0;
        CSTRING_REF(ptr)->length = 0;
    }
}

void* CStringBegin(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->begin;
    }
    return NULL;
}

void* CStringEnd(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->end;
    }
    return NULL;
}

void* CStringRBegin(void* ptr)
{
    return CStringEnd(ptr);
}

void* CStringREnd(void* ptr)
{
    return CStringBegin(ptr);
}

size_t CStringEqual(void* ptr, const char* str)
{
    if(ptr != NULL && str != NULL)
    {
        size_t str_len = strlen(str);

        if(CSTRING_REF(ptr)->string == NULL)
        {
            CSTRING_REF(ptr)->string = (char*)calloc(1, str_len);

            CSTRING_REF(ptr)->begin = (void*)CSTRING_REF(ptr)->string;
            CSTRING_REF(ptr)->end = (void*)CSTRING_REF(ptr)->string + str_len;
        }

        CSTRING_STRCPY(CSTRING_REF(ptr)->string, str_len + 1, str);
        CSTRING_REF(ptr)->length = str_len;

        if(CSTRING_REF(ptr)->length > CSTRING_REF(ptr)->size &&
           CSTRING_REF(ptr)->capacity < CSTRING_REF(ptr)->length)
        {
            CSTRING_REF(ptr)->size = CSTRING_REF(ptr)->length + 1;
            denx_cstring_IncreaseCapacity(ptr); // Increase the capacity of the string.
        }

        if(!strcmp(CSTRING_REF(ptr)->string, str))
        {
            return CSTRING_REF(ptr)->size; 
        }
    }
    return 0;
}

const char* CStringData(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->string;
    }
    return NULL;
}

void denx_cstring_IncreaseCapacity(void* ptr)
{
    if(ptr != NULL)
    {
        size_t ssize = CSTRING_REF(ptr)->size;

        char* temp_str = (char*)malloc(ssize);
        
        size_t ncapacity = ssize + (ssize / 2);

        CSTRING_STRCPY(temp_str, ssize, CSTRING_REF(ptr)->string);

        free(CSTRING_REF(ptr)->string);
        CSTRING_REF(ptr)->string = NULL;

        CSTRING_REF(ptr)->string = (char*)malloc(ssize + (ssize / 2));
        CSTRING_STRCPY(CSTRING_REF(ptr)->string, ssize, temp_str);
        CSTRING_REF(ptr)->capacity = ncapacity;

        free(temp_str);
        temp_str = NULL;
    }
}

size_t CStringEmpty(void* ptr)
{
    if(ptr != NULL)
    {
        return CSTRING_REF(ptr)->length;
    }
    return 1;
}

char* CStringFront(void* ptr)
{
    if(ptr != NULL)
    {
        if(CSTRING_REF(ptr)->string != NULL && CSTRING_REF(ptr)->size > 0)
        {
            return (char*)CStringBegin(ptr);
        }
    }
    return NULL;
}

char* CStringBack(void* ptr)
{
    if(ptr != NULL)
    {
        if(CSTRING_REF(ptr)->string != NULL && CSTRING_REF(ptr)->size > 0)
        {
            return (char*)(CStringEnd(ptr) - 1);
        }
    }
    return NULL;
}

// Returns the maximum number of characters a CString can hold.
const size_t CStringMaxSize()
{
    return 0;
}

size_t CStringReserve(void* ptr, size_t new_cap)
{
    if(ptr == NULL)
    {
        return 0;
    }

    // shrink request
    if(CSTRING_REF(ptr)->capacity > new_cap)
    {
        char* temp_str = (char*)calloc(1, new_cap);
        memcpy(temp_str, CSTRING_REF(ptr)->string, new_cap);

        free(CSTRING_REF(ptr)->string);
        CSTRING_REF(ptr)->string = NULL;

        CSTRING_REF(ptr)->string = (char*)calloc(1, new_cap);
        memcpy(CSTRING_REF(ptr)->string, temp_str, new_cap);
        CSTRING_REF(ptr)->capacity = new_cap;

        // we also need to check if the last character is is not a `\0`.
        // otherwise(possibly), when printing the string, we would go behond the size of the string.
        if(CSTRING_REF(ptr)->string[new_cap - 1] != '\0')
        {
            CSTRING_REF(ptr)->string[new_cap - 1] = '\0';
        }
        CSTRING_REF(ptr)->size = CSTRING_LEN(ptr) + 1;
        CSTRING_REF(ptr)->length = CSTRING_LEN(ptr);

        return new_cap;
    }
    // shrink-to-fit request
    else if(CSTRING_REF(ptr)->size > new_cap)
    {
        CStringShrinkToFit(ptr);
        return CSTRING_REF(ptr)->capacity;
    }
    else
    {
        if(CSTRING_REF(ptr)->capacity == new_cap)
        {
            return new_cap;
        }

        // Expanding the string.
        char* temp_str = (char*)calloc(1, new_cap);
        memcpy(temp_str, CSTRING_REF(ptr)->string, CSTRING_REF(ptr)->capacity);

        free(CSTRING_REF(ptr)->string);
        CSTRING_REF(ptr)->string = NULL;
        CSTRING_REF(ptr)->string = (char*)calloc(1, new_cap);

        memcpy(CSTRING_REF(ptr)->string, temp_str, new_cap);
        CSTRING_REF(ptr)->capacity = new_cap;
        return new_cap;
    }
    
    return 0;
}

size_t CStringShrinkToFit(void* ptr)
{
    if(ptr == NULL)
    {
        return 0;
    }

    if(CSTRING_REF(ptr)->capacity == CSTRING_REF(ptr)->size)
    {
        return 0;
    }

    size_t new_cap = CSTRING_REF(ptr)->size;
    size_t old_cap = CSTRING_REF(ptr)->capacity;

    char* temp_str = (char*)malloc(new_cap);
    CSTRING_MEMCPY(temp_str, new_cap, CSTRING_REF(ptr)->string, CSTRING_REF(ptr)->capacity);

    free(CSTRING_REF(ptr)->string);
    CSTRING_REF(ptr)->string = NULL;
    CSTRING_REF(ptr)->string = (char*)malloc(new_cap);
    CSTRING_MEMCPY(CSTRING_REF(ptr)->string, new_cap, temp_str, new_cap);

    CSTRING_REF(ptr)->capacity = new_cap;

    return (old_cap - new_cap); 
}

// TODO: If the index is 0, nothing is inserted(NEEDS IMPLEMENTATION)
// TODO: If the index is greater than 0, a 'Segmentation-Fault' is thrown.
// TODO: Size and length must be updated.
size_t CStringInsert(void* ptr, char c, size_t indx)
{
     if(ptr == NULL)
     {
         return 1;
     }

    // Here we can use `CStringPushBack` instead.
    if(CSTRING_REF(ptr)->string == NULL)
    {
        // allocate at least 1 byte.
        CSTRING_REF(ptr)->string = (char*)malloc(2);
        if(CSTRING_REF(ptr)->string == NULL)
        {
            return 1;
        }

        CSTRING_REF(ptr)->length = 1;
        CSTRING_REF(ptr)->size = 2;
        CSTRING_REF(ptr)->capacity = 2;
        CSTRING_REF(ptr)->string[0] = c;
        CSTRING_REF(ptr)->string[1] = '\0';
        return 0;
    }

    // Actually, here we could use `CStringPushBack`.
    if(indx >= CSTRING_REF(ptr)->length)
    {
        denx_cstring_IncreaseCapacity(ptr);
        CSTRING_REF(ptr)->string[CSTRING_REF(ptr)->length] = c;
        CSTRING_REF(ptr)->string[CSTRING_REF(ptr)->length + 1] = '\0';
        return 0;
    }
    else if(indx < CSTRING_REF(ptr)->length)
    {
        if(indx > 0)
        {
            char* temp_str = (char*)malloc(indx + 1);
            for(size_t i = 0; i < indx; i++)
            {
                temp_str[i] = CSTRING_REF(ptr)->string[i];
            }
            temp_str[indx] = c;

            char* after_str = (char*)malloc(CSTRING_REF(ptr)->length - indx);
            
            char* final_rslt = (char*)malloc(CSTRING_REF(ptr)->capacity);

            CSTRING_STRCAT(final_rslt, indx + 1, temp_str);
            CSTRING_STRCAT(final_rslt, CSTRING_REF(ptr)->length - indx, after_str);

            free(after_str);
            free(temp_str);
            after_str = NULL;
            temp_str = NULL;

            CSTRING_STRCPY(CSTRING_REF(ptr)->string, CSTRING_REF(ptr)->capacity, final_rslt);
            free(final_rslt);
            final_rslt = NULL;
            return 0;
        }
        
    }
    return 0;
}

size_t CStringErase(void* ptr, size_t indx)
{
    if(ptr == NULL || indx > CSTRING_REF(ptr)->size)
    {
        return 1;
    }

    if(indx == (CSTRING_REF(ptr)->length - 1))
    {
        CSTRING_REF(ptr)->string[indx] = '\0';
        CSTRING_REF(ptr)->length--;
        CSTRING_REF(ptr)->size--;
        return 0;
    }
    else
    {
        if(!indx) { indx = 1; }

        while(indx != 0)
        {
            for(size_t i = 1; CSTRING_REF(ptr)->string[i] != '\0' && i < CSTRING_REF(ptr)->length; i++)
            {
                CSTRING_REF(ptr)->string[i - 1] = CSTRING_REF(ptr)->string[i];
                // CSTRING_REF(ptr)->string[indx] = CSTRING_REF(ptr)->string[indx + 1];
            }
            indx--;
        }
        CSTRING_REF(ptr)->length--;
        CSTRING_REF(ptr)->size--;
        CSTRING_REF(ptr)->string[CSTRING_REF(ptr)->length] = '\0';
        return 0;
    }

    return 1;
}

size_t CStringPushBack(void* ptr, char c)
{
    if(ptr == NULL)
    {
        return 1;
    }

    if(CSTRING_REF(ptr)->string == NULL)
    {
        CSTRING_REF(ptr)->string = (char*)malloc(2);
        // error: couldn't allocate memory for string.
        if(CSTRING_REF(ptr)->string == NULL)
        {
            return 1;
        }

        CSTRING_REF(ptr)->string[0] = c;
        CSTRING_REF(ptr)->string[1] = '\0';

        CSTRING_REF(ptr)->capacity = 2;
        CSTRING_REF(ptr)->size = 2;
        CSTRING_REF(ptr)->length = 1;

        return 0;
    }

    size_t orig_size = CSTRING_REF(ptr)->size;
    char* temp_str = (char*)malloc(orig_size + 1);

    memcpy(temp_str, CSTRING_REF(ptr)->string, orig_size);

    temp_str[orig_size - 1] = c;
    temp_str[orig_size] = '\0';

    free(CSTRING_REF(ptr)->string);
    CSTRING_REF(ptr)->string = NULL;

    CSTRING_REF(ptr)->string = (char*)malloc(orig_size + 1);
    CSTRING_MEMCPY(CSTRING_REF(ptr)->string, orig_size + 1, temp_str, orig_size + 1);
    CSTRING_REF(ptr)->size = orig_size + 1;
    CSTRING_REF(ptr)->length = strlen(CSTRING_REF(ptr)->string);

    free(temp_str);
    temp_str = NULL;

    return 0;
}

size_t CStringPopBack(void* ptr)
{
    if(ptr != NULL)
    {
        return CStringErase(ptr, CStringLength(ptr) - 1);
    }
    return 1;
}

size_t CStringAppend(void* ptr, char c)
{
    return CStringPushBack(ptr, c);
}

int CStringCompare(void* ptr0, void* ptr1)
{
    if(ptr0 == NULL || ptr1 == NULL)
    {
        return -1;
    }

    while(*CSTRING_REF(ptr0)->string)
    {
        if(*CSTRING_REF(ptr0)->string != *CSTRING_REF(ptr1)->string)
        {
            break;
        }
        CSTRING_REF(ptr0)->string++;
        CSTRING_REF(ptr1)->string;
    }
    return *(const unsigned char*)CSTRING_REF(ptr0)->string - *(const unsigned char*)CSTRING_REF(ptr1)->string;
}

size_t CStringStartsWith(void* ptr, char c)
{
    if(ptr != NULL && CSTRING_REF(ptr)->string != NULL && CSTRING_REF(ptr)->length > 0)
    {
        return CSTRING_REF(ptr)->string[0] == c;
    }
    return 0;
}

size_t CStringEndsWith(void* ptr, char c)
{
    if(ptr != NULL && CSTRING_REF(ptr)->string != NULL && CSTRING_REF(ptr)->length > 0)
    {
        return CSTRING_REF(ptr)->string[CSTRING_REF(ptr)->length - 1] == c;
    }
    return 0;
}

size_t CStringReplace(void* ptr, const char* str, size_t pos, size_t len)
{
    if(ptr != NULL && str != NULL && len > 0)
    {
        if(len > CSTRING_REF(ptr)->length)
        {
            return 0;
        }
        if(CSTRING_REF(ptr)->string != NULL && str != NULL)
        {
            size_t lindex = 0;
            while(CSTRING_REF(ptr)->string[lindex + pos] != '\0' && str[lindex] != '\0' && lindex <= (len - 1))
            {
                CSTRING_REF(ptr)->string[lindex + pos] = str[lindex];
                lindex++;
            }
            return lindex;
        }
    }
    return 0;
}

void* CStringSubStr(void* ptr, size_t start, size_t end)
{
    if(ptr != NULL)
    {
        denx_cstring* obj = (denx_cstring*)malloc(sizeof(denx_cstring));
        if(obj == NULL)
        {
            return NULL;
        }

        if(!end)
        {
            end = CSTRING_REF(ptr)->size;
        }

        SUBSTR:
        if(start < end)
        {
            CSTRING_REF(obj)->string = (char*)calloc(1, end - start + 1);
            if(CSTRING_REF(obj)->string == NULL)
            {
                return NULL;
            }

            CSTRING_REF(obj)->size = end - start + 1;
            CSTRING_REF(obj)->length = end - start;
            CSTRING_REF(obj)->capacity = CSTRING_REF(obj)->size;

            if(CSTRING_REF(obj)->string == NULL)
            {
                return NULL;
            }

            size_t lindex = 0;
            while(start != end)
            {
                CSTRING_REF(obj)->string[lindex++] = CSTRING_REF(ptr)->string[start++];
            }
        }
        else if(end < start)
        {
            start = start + end;
            end = start - end;
            start = start - end;
            goto SUBSTR;
        }
        return (void*)obj;
    }
    return NULL;
}

size_t CStringCopy(void* ptr, void* cptr)
{
    if(ptr == NULL || cptr == NULL)
    {
        return 0;
    }

    CSTRING_REF(ptr)->string = (char*)calloc(1, CSTRING_REF(cptr)->capacity);
    CSTRING_REF(ptr)->capacity = CSTRING_REF(cptr)->capacity;
    CSTRING_REF(ptr)->size = CSTRING_REF(cptr)->size;
    CSTRING_REF(ptr)->length = CSTRING_REF(cptr)->length;
    CSTRING_STRCPY(CSTRING_REF(ptr)->string, CSTRING_REF(cptr)->size, CSTRING_REF(cptr)->string);
    
    return CSTRING_REF(ptr)->size;
}

size_t CStringResize(void* ptr, size_t sz, char c)
{
    if(ptr != NULL)
    {
        if(CSTRING_REF(ptr)->string == NULL || !CSTRING_REF(ptr)->size || !CSTRING_REF(ptr)->length)
        {
            if(CSTRING_REF(ptr)->string != NULL)
            {
                free(CSTRING_REF(ptr)->string);
            }

            CSTRING_REF(ptr)->string = (char*)calloc(1, sz);
            CSTRING_REF(ptr)->size = sz;
            CSTRING_REF(ptr)->capacity = sz;
            CSTRING_REF(ptr)->length = 0;
            return 0;
        }
        else if(sz > CSTRING_REF(ptr)->size)
        {
            char* temp_string = malloc(CSTRING_REF(ptr)->size);
            CSTRING_STRCPY(temp_string, CSTRING_REF(ptr)->size, CSTRING_REF(ptr)->string);

            free(CSTRING_REF(ptr)->string);
            CSTRING_REF(ptr)->string = (char*)calloc(1, sz);
            CSTRING_STRCPY(CSTRING_REF(ptr)->string, CSTRING_REF(ptr)->length, temp_string);

            for(size_t i = CSTRING_REF(ptr)->size; i < sz; i++)
            {
                CSTRING_REF(ptr)->string[i] = c;
            }

            CSTRING_REF(ptr)->size = sz;
            CSTRING_REF(ptr)->length = CSTRING_LEN(ptr);
            CSTRING_REF(ptr)->capacity = sz;

            free(temp_string);
            temp_string = NULL;
        }
        else if(sz < CSTRING_REF(ptr)->size)
        {
            CSTRING_REF(ptr)->string[sz - 1] = c;
            for(size_t i = sz; i < CSTRING_REF(ptr)->size; i++)
            {
                CSTRING_REF(ptr)->string[i] = c;
            }

            CSTRING_REF(ptr)->size = sz;
        }
        return 0;
    }
    return 1;
}

size_t CStringSwap(void* ptr0, void* ptr1)
{
    if(ptr0 != NULL && ptr1 != NULL)
    {
        // Swap only if both strings are allocated.
        if(CSTRING_REF(ptr0)->string != NULL && CSTRING_REF(ptr1)->string != NULL)
        {
            char* temp_string0 = (char*)calloc(1, CSTRING_REF(ptr0)->capacity);
            char* temp_string1 = (char*)calloc(1, CSTRING_REF(ptr1)->capacity);

            size_t cap0 = CSTRING_REF(ptr0)->capacity;
            size_t cap1 = CSTRING_REF(ptr1)->capacity;

            size_t sz0 = CSTRING_REF(ptr0)->size;
            size_t sz1 = CSTRING_REF(ptr1)->size;

            size_t len0 = CSTRING_REF(ptr0)->length;
            size_t len1 = CSTRING_REF(ptr1)->length;

            free(CSTRING_REF(ptr0)->string);
            free(CSTRING_REF(ptr1)->string);

            CSTRING_REF(ptr0)->string = (char*)calloc(1, cap1);
            CSTRING_REF(ptr1)->string = (char*)calloc(1, cap0);

            CSTRING_STRCPY(CSTRING_REF(ptr0)->string, len1, temp_string1);
            CSTRING_STRCPY(CSTRING_REF(ptr1)->string, len0, temp_string0);

            CSTRING_REF(ptr0)->capacity = cap1;
            CSTRING_REF(ptr1)->capacity = cap0;

            CSTRING_REF(ptr0)->size = sz1;
            CSTRING_REF(ptr1)->size = sz0;

            CSTRING_REF(ptr0)->length = CSTRING_LEN(CSTRING_REF(ptr0)->string);
            CSTRING_REF(ptr1)->length = CSTRING_LEN(CSTRING_REF(ptr1)->string);

            // Both swaps must match with the swapped string!
            if(strcmp(CSTRING_REF(ptr0)->string, temp_string1) || strcmp(CSTRING_REF(ptr1)->string, temp_string0))
            {
                return 1;
            }

            free(temp_string0);
            free(temp_string1);

            return 0;
        }
    }
    return 1;
}

size_t CStringFind(void* ptr, const char* chrs)
{
    if(ptr == NULL || chrs == NULL)
    {
        return CSTRING_NPOS;
    }
    else if(!strlen(chrs))
    {
        return CSTRING_NPOS;
    }

    size_t chrs_len = strlen(chrs);
    size_t index = 0;
    size_t cindex = 0;

    do
    {
        if(chrs[cindex] != CSTRING_REF(ptr)->string[index])
        {
            cindex = 0;
        }
        if(cindex == chrs_len - 1)
        {
            break;
        }
        cindex++;
        index++;
    }while(index < CSTRING_REF(ptr)->length);

    if(index > CSTRING_REF(ptr)->length)
    {
        return CSTRING_NPOS;
    }

    index -= (chrs_len - 1);
    return index;
}

// !TODO: This function does not work properly. Needs to be re-thinked/re-written.
// !>BUG
size_t CStringRFind(void* ptr, const char* chrs)
{
    if(ptr == NULL || chrs == NULL)
    {
        return CSTRING_NPOS;
    }
    else if(!strlen(chrs))
    {
        return CSTRING_NPOS;
    }

    size_t str_len = CSTRING_REF(ptr)->length;
    size_t chr_len = strlen(chrs);

    for(size_t i = (str_len - 1); i >= 0; i--)
    {
        int j = (chr_len - 1);
        while(j < chr_len && CSTRING_REF(ptr)->string[i-j] == chrs[j])
        {
            j--;
        }
        if(j < 0)
        {
            return i;
        }

    }
    return -1;
}

size_t CStringFindFirstOf(void* ptr, const char* chrs)
{
    return CStringFind(ptr, chrs);
}

size_t CStringFindLastOf(void* ptr, const char* chrs)
{
    return CStringRFind(ptr, chrs);
}

size_t CStringFindFirstNotOf(void* ptr, const char* chrs)
{
    if(ptr == NULL || CSTRING_REF(ptr)->string == NULL || chrs == NULL)
    {
        return -1;
    }

    size_t str_len = strlen(CSTRING_REF(ptr)->string);
    size_t chrs_len = strlen(chrs);
    for(int i = 0; i <= str_len - chrs_len; i++)
    {
        size_t j = 0;
        if(CSTRING_REF(ptr)->string[i+j] != chrs[j])
        {
            return i;
        }
        while(j < chrs_len && CSTRING_REF(ptr)->string[i+j] == chrs[j])
        {
            j++;
        }
    }
    return -1;
}

// !TODO: Like `CStringFindLastOf`, this function doesn't actually work
// !BUG
size_t CStringFindLastNotOf(void* ptr, const char* chrs)
{
    if(ptr == NULL || CSTRING_REF(ptr)->string == NULL || chrs == NULL)
    {
        return -1;
    }

    size_t str_len = strlen(CSTRING_REF(ptr)->string);
    size_t chrs_len = strlen(chrs);
    for(int i = str_len - chrs_len; i >= 0; i--)
    {
        size_t j = chrs_len - 1;
        if(CSTRING_REF(ptr)->string[i+j] != chrs[j])
        {
            return i;
        }
        while(j > 0 && CSTRING_REF(ptr)->string[i+j] == chrs[j])
        {
            j--;
        }
    }
    return -1;
}

#endif
