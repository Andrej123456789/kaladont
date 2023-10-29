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


int minimax(Tree* tree, int depth, bool max)
{
    if (depth == 0)
    {
        return tree->value;
    }

    if (max)
    {
        int maxEval = -1000;
        for (int i = 0; i < 2; i++)
        {
            if (tree->childrens[i] == NULL)
            {
                maxEval = tree->value;
                break;
            }

            int eval = minimax(tree->childrens[i], depth - 1, false);
            maxEval = maximum(maxEval, eval);
        }

        return maxEval;
    }

    else
    {
        int minEval = 1000;
        for (int i = 0; i < 2; i++)
        {
            if (tree->childrens[i] == NULL)
            {
                minEval = tree->value;
                break;
            }

            int eval = minimax(tree->childrens[i], depth - 1, true);
            minEval = minimum(minEval, eval);
        }

        return minEval;
    }
}

char* computer_turn()
{
    Tree* t1 = create_node(0);

    Tree* n1 = create_node(0);
    Tree* n2 = create_node(0);

    Tree* n1n1 = create_node(-4);
    Tree* n1n2 = create_node(0);

    Tree* n2n1 = create_node(-8);
    Tree* n2n2 = create_node(8);

    n1->childrens[0] = n1n1;
    n1->childrens[1] = n1n2;

    n2->childrens[0] = n2n1;
    n2->childrens[1] = n2n2;

    t1->childrens[0] = n1;
    t1->childrens[1] = n2;

    printf("Value: %d\n", minimax(t1, 10, true));

    free(t1);
    free(n1);
    free(n2);

    return "test";
}
