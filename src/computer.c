#include "headers/computer.h"

Tree* create_node(int value)
{
    Tree* result = malloc(sizeof(Tree));

    if (result != NULL)
    {
        result->childrens[0] = NULL;
        result->childrens[1] = NULL;
        result->value = value;
    }

    return result;
}

int maximum(int a, int b) 
{
    return (a > b) ? a : b;
}

int minimum(int a, int b) 
{
    return (a < b) ? a : b;
}

int minimax(Tree* tree, int depth)
{
    if (depth == 0)
    {
        return tree->value;
    }

    int bestEval = 1000;    /* -1000 if first node white; +1000 if first node black */
                            /* basically, we give worst value so we can "filter" real value */

    for (int i = 0; i < 2; i++)
    {
        if (tree->childrens[i] == NULL)
        {
            return tree->value;
        }

        int eval = -minimax(tree->childrens[i], depth - 1);
        bestEval = minimum(eval, bestEval);     /* `maximum` if first node white; `minimum` if first node black */
                                                /* basically, we give worst value so we can "filter" real value */
    }

    return bestEval;
}

char* computer_turn()
{
    Tree* t1 = create_node(0);

    Tree* n1 = create_node(0);
    Tree* n2 = create_node(0);

    Tree* n1n1 = create_node(-6);
    Tree* n1n2 = create_node(-8);

    Tree* n2n1 = create_node(9);
    Tree* n2n2 = create_node(10);

    n1->childrens[0] = n1n1;
    n1->childrens[1] = n1n2;

    n2->childrens[0] = n2n1;
    n2->childrens[1] = n2n2;

    t1->childrens[0] = n1;
    t1->childrens[1] = n2;

    printf("Minimax: %d\n", minimax(t1, 2));

    free(t1);
    free(n1);
    free(n2);

    return "test";
}
