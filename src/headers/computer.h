#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gameplay.h"

/**
 * Binary tree structure
*/
typedef struct Tree
{
    int value;
    struct Tree* childrens[2];
} Tree;

/**
 * Create new node in tree
 * @param value value
*/
Tree* create_node(int value);

/**
 * Learning minimax implementaion in actual code
 * @param tree `Tree` struct
 * @param depth depth of search
*/
int minimax(Tree* tree, int depth);

/**
 * Return word which computer played
*/
char* computer_turn();
