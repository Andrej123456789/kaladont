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
