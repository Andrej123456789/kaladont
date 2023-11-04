#pragma once

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "gameplay.h"
#include "utils.h"

struct gameplay_T;
struct start_T;

/**
 * Binary tree structure
*/
typedef struct Tree
{
    char word[1024];
    int16_t evaluation;

    cvector_vector_type(struct Tree*) childrens;
} Tree;

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
 * Return word which computer played
 * @param _gameplay `Gameplay` struct
 * @param _start `Start` struct
 * @return char*
*/
char* computer_turn(struct gameplay_T* _gameplay, struct start_T* _start);
