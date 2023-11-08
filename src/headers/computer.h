#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "gameplay.h"
#include "utils.h"

struct gameplay_T;
struct start_T;

#define UNUSED(x) (void)(x)

#define WORD_LIMIT 64

/**
 * Binary tree structure
 * @param word word
 * @param evaluation value which tells us how good word is
 * @param childrens our children nodes
*/
typedef struct Tree
{
    char word[WORD_LIMIT];
    int16_t evaluation;

    cvector_vector_type(struct Tree*) childrens;
} Tree;

/**
 * Tuple for `search_tree` function
 * @param word word
 * @param evaluation value which tells us how good word is
*/
typedef struct Tuple
{
    char word[WORD_LIMIT];
    int16_t evaluation;
} Tuple;

/**
 * Generate tree of all playable words
 * @param words words list
 * @param current_word current word
 * @param depth depth of the tree
 * @return `Tree` struct
*/
Tree* generate_tree(cvector_vector_type(char*) words, char* current_word, uint64_t depth);

/**
 * Evaluate a word
 * @param word word to be evaluated
 * @return int16_t
*/
int16_t evaluate_word(char* word);

/**
 * Print a tree
 * @param tree tree
 * @param depth depth of a tree
*/
void print_tree(Tree* tree, uint16_t depth);

/**
 * Search best word for computer
 * @param tree tree containing all words
 * @param depth depth of search
 * @return `Tuple` struct
*/
Tuple search_tree(Tree* tree, int16_t depth);

/**
 * Return word which computer played
 * @param _gameplay `Gameplay` struct
 * @param _start `Start` struct
 * @return char*
*/
char* computer_turn(struct gameplay_T* _gameplay, struct start_T* _start);
