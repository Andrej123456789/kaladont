#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CSTRING_NPOS ((size_t)-1)

/**********************************************/
/*
/* CString Function Members Definition
/*
/**********************************************/

/**
 * Create an empty CString object and returns a pointer to its data.
*/
void* CStringCreate();

/**
 * Destroys the CString and returns a 0 (no error) or 1 (error).
 * @param ptr `CString` object
*/
size_t CStringDestroy(void* ptr);

/**
 * Calculates the length of the CString and returns it.
 * @param ptr `CString` object
*/
size_t CStringLength(void* ptr);

/**
 * Calculates the size of the CString and returns it. 
 * Unlike `CStringLength`, this will calculate the actual size of the string in memory.
 * @param ptr `CString` object
*/
size_t CStringSize(void* ptr);

/**
 * Calculates the capacity of the CString object and returns it.
 * @param ptr `CString` object
*/
size_t CStringCapacity(void* ptr);

/**
 * Returns a pointer to a character of the string or `NULL` if the index isn't valid.
 * @param ptr `CString` object
 * @param index vector's position we want to access
*/
char* CStringAt(void* ptr, size_t index);

/**
 * Clears the CString. This won't affect its capacity and size.
 * @param ptr `CString` object
*/
void CStringClear(void* ptr);

/**
 * Returns a pointer to the first character of the CString.
 * @param ptr `CString` object
*/
void* CStringBegin(void* ptr);

/**
 * Returns a pointer to the last character of the CString.
 * @param ptr `CString` object
*/
void* CStringEnd(void* ptr);

/**
 * Returns a pointer to the last character of the CString (reversed beginning).
 * @param ptr `CString` object
*/
void* CStringRBegin(void* ptr);

/**
 * Returns a pointer to the first character of the CString (reversed ending).
 * @param ptr `CString` ptr
*/
void* CStringREnd(void*);

/**
 * Copies the content of the string passed as argument to the CString. Returns the number of bytes copied.
 * @param ptr `CString` object
 * @param str string
*/
size_t CStringEqual(void*, const char*);

/**
 * Returns the actual string.
 * @param ptr `CString` object`
*/
const char* CStringData(void* ptr);

/**
 * Check if the CString is empty. Returns 0 (not empty) or 1 (empty). If CString is `NULL`, 1 is returned.
 * @param ptr `CString` object
*/
size_t CStringEmpty(void* ptr);

/**
 * Returns a pointer to the first character of the CString or NULL.
 * @param ptr `CString` object
*/
char* CStringFront(void* ptr);

/**
 * Returns a pointer to the last character of the CString or NULL.
 * @param ptr `CString` object
*/
char* CStringBack(void* ptr);

/**
 * # FIX ME
 * Returns the maximum number of characters a CString can hold. 
 * At the moment, function will always return 0 because I don't know where could I find the maximum number of characters of a string in C.
*/
const size_t CStringMaxSize();

/**
 * Reserves the amount of bytes specified. Returns the new capacity of the CString.
 * If the amount of bytes to be reserved are less then `CStringCapacity`, then it's a shrink request.
 * If the amount of bytes to be reserved are less then `CStringSize`, then it's a `shrink-to-fit` request.
 * @param ptr `CString` object
 * @param new_cap new size of `CString` object
*/
size_t CStringReserve(void* ptr, size_t new_cap);

/**
 * Shrinks the CString to fit. This will make the capacity of the CString match the size of the CString. Returns the number of bytes shrinked.
 * If the size of the CString already matches the capacity of the CString, nothing is done (0 is returned).
 * @param ptr `CString` objects
*/
size_t CStringShrinkToFit(void* ptr);

/**
 * TODO: If the index is 0, nothing is inserted(NEEDS IMPLEMENTATION)
 * TODO: If the index is greater than 0, a 'Segmentation-Fault' is thrown.
 * TODO: Size and length must be updated.
 * 
 * Inserts a character at the given location in the CString. Returns 0 (character inserted) or 1 (error).
 * Any index greater than the length/size/capacity of the CString is interpreted as: insert the character at the end.
 * @param ptr `CString` object
 * @param c character to be inserted
 * @param indx index where character will be inserted
*/
size_t CStringInsert(void* ptr, char c, size_t indx);

/**
 * Erases a character at the given location. Returns 0 (character deleted) or 1 (error, invalid position).
 * @param ptr `CString` object
 * @param indx index of character that will be erased
*/
size_t CStringErase(void* ptr, size_t indx);

/**
 * Insert a single character at the end of the CString. Returns 0 (no errors) or 1 (error).
 * @param ptr `CString` object
 * @param c character to be inserted
*/
size_t CStringPushBack(void* ptr, char c);

/**
 * Pops back the last character. Effectively erases the last character of the CString. Returns 0 (no errors) or 1 (error).
 * @param ptr `CString` object
*/
size_t CStringPopBack(void* ptr);

/**
 * Insert a single character at the end of the CString. Returns 0 (no errors) or 1 (error).
 * @param ptr `CString` object
 * @param c character to be inserted
*/
size_t CStringAppend(void* ptr, char c);

/**
 * Compares the two CStrings. Returns 0, N<0 or N>0.
 * N<0 if the first character that does not match has a lower value in the first CString than in the second CString.
 * 0 if the contents of both CStrings are equal.
 * N>0 if the first character that does not match has a greater value in the first CString than in the second CString.
 * If either the first CString or the second CString is a NULL pointer, -1 is returned.
 * 
 * @param ptr0 `CString` object, subject
 * @param ptr1 `CString` object, object
*/
int CStringCompare(void* ptr0, void* ptr1);

/**
 * Compares the first character of the CString with the given character. Returns 1 (starts with) or 0 (not starting with).
 * @param ptr `CString` object
 * @param c character
*/  
size_t CStringStartsWith(void* ptr, char c);

/**
 * Compares the last character of the CString with the given character. Returns 1 (ends with) or 0 (not ending with).
 * @param ptr `CString` object
 * @param c character
*/
size_t CStringEndsWith(void* ptr, char c);

/**
 * Replaces the portion of the string that the begins at the given position and spans for the given string's lenght.
 * Returns the number of bytes written on the CString.
 * @param ptr `CString` position
 * @param str string
 * @param pos starting position
 * @param len length of string
*/
size_t CStringReplace(void* ptr, const char* str, size_t pos, size_t len);

/**
 * Returns a CString object with its value initialized to a copy of a substring
 * of the given CString object.
 * @param ptr `CString` object
 * @param start starting position of substring
 * @param end ending position of substring
 * @return `CString` (valid positions) or `NULL` (invalid positions or `ptr` is NULL).
*/
void* CStringSubStr(void*, size_t start, size_t end);

/**
 * Copies the content of the second CString object to the first CString object.
 * Returns the number of bytes copied.
 * @note: The content of the first CString object is deleted.
*/
size_t CStringCopy(void*, void*);

/**
 * Resizes the CString to a length of N characters.
 * If N is smaller than the current CString length, the current value is shortened to its first N character, removing the characters beyond the Nth.
 * If n is greater than the current CString length, the current content is extended by inserting at the end as many characters as needed to reach a size of N. 
 * New elements are all initialized with the value of the given character.
 * @param ptr `CString` object
 * @param sz size
 * @param c character
 * @return 0 (no errors) or 1 (error)
*/
size_t CStringResize(void* ptr, size_t sz, char c);

/**
 * Swaps the content of two CStrings.
 * @param ptr0 `CString` object, subject
 * @param ptr1 `CString` object, object
 * @return 0 (no errors) or 1 (error).
*/
size_t CStringSwap(void* ptr0, void* ptr1);

/**
 * Finds the first sub-strings equal to the given character sequence.
 * Returns the position of the first match or `CSTRING_NPOS` if no match
 * @param ptr `CString` object`
 * @param str substring
*/
size_t CStringFind(void*, const char*);

/**
 * # TODO: This function does not work properly. Needs to be re-thinked/re-written.
 * 
 * Find the first sub-string equal to the given character sequence starting from the end of the
 * CString.
 * Returns the position of the first match or `CSTRING_NPOS` if no match.
 * @param ptr `CString` object
 * @param chrs substring
*/
size_t CStringRFind(void* ptr, const char* chrs);

/**
 * Finds the first sub-strings equal to the given character sequence
 * Returns the position of the first match or `CSTRING_NPOS` if no match.
 * @param ptr `CString` object
 * @param chrs substring
*/
size_t CStringFindFirstOf(void* ptr, const char* chrs);

/**
 * Find the first sub-strings equal to the given character sequence starting from the end of the
 * CString.
 * Returns the position of the first match or `CSTRING_NPOS` if no match.
 * @param ptr `CString` object
 * @param chrs substring
*/
size_t CStringFindLastOf(void* ptr, const char* chrs);

/** 
 * Find the first character not equal to the given character sequence.
 * Returns the position of the first non-matching character or `CSTRING_NPOS` if all matched.
 * @param ptr `CString` object
 * @param chrs substring
*/
size_t CStringFindFirstNotOf(void*, const char*);

/**
 * # TODO: Like `CStringFindLastOf`, this function doesn't actually work
 * 
 * Finds the first character not equal to the given character sequence starting from the end of the
 * CString.
 * Returns the position of the first non-matching character or `CSTRING_NPOS` if all matched.
 * @param ptr `CString` object
 * @param chrs substring
*/
size_t CStringFindLastNotOf(void*, const char*);

/**********************************************/
/*
/* CString Structures and Utility Macros
/*
/**********************************************/

/**
 * CString struct
 * @param string string as `char*`
 * @param length length of string
 * @param size size of string
 * @param capacity capacity of string
 * @param begin starting position
 * @param end ending position
*/
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

/**
 * Increases the capacity of the CString using logarithmic scaling.
 * @param ptr `denx_cstring` object
*/
void denx_cstring_IncreaseCapacity(void* ptr);
