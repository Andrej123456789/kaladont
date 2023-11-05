#include "headers/computer.h"

/*int minimax(Tree* tree, int depth)
{
    if (depth == 0)
    {
        return tree->value;
    }

    int bestEval = 1000;    // -1000 if first node white; +1000 if first node black
                            // basically, we give worst value so we can "filter" real value

    for (int i = 0; i < 2; i++)
    {
        if (tree->childrens[i] == NULL)
        {
            return tree->value;
        }

        int eval = -minimax(tree->childrens[i], depth - 1);
        bestEval = minimum(eval, bestEval);     // `maximum` if first node white; `minimum` if first node black
                                                // basically, we give worst value so we can "filter" real value
    }

    return bestEval;
}*/

void print_tree(Tree* tree, uint16_t depth) 
{
    if (tree == NULL) return;

    for (uint16_t i = 0; i < depth; i++) 
    {
        printf("  ");
    }

    printf("|- %s\n", tree->word);

    for (size_t i = 0; i < cvector_size(tree->childrens); i++) 
    {
        print_tree(tree->childrens[i], depth + 1);
    }
}

Tree* generate_tree(cvector_vector_type(char*) words, char* current_word, uint64_t depth)
{
    if (depth == 0)
    {
        Tree* children = malloc(sizeof(Tree));
        strcpy(children->word, "end");
        children->evaluation = evaluate_word("end");

        return children;
    }

    Tree* tree = malloc(sizeof(Tree));

    strcpy(tree->word, current_word);
    tree->childrens = NULL;

    cvector_vector_type(char*) possible_words = get_all_words_starting_on(words, get_last_N_characters(current_word, 2)); 

    if (cvector_size(possible_words) == 0)
    {
        Tree* children = malloc(sizeof(Tree));
        strcpy(children->word, current_word);
        children->evaluation = evaluate_word(current_word);

        return children;
    }   

    if (tree->childrens == NULL)
    {
        for (size_t i = 0; i < cvector_size(possible_words); i++)
        {
            if (strcmp(possible_words[i], current_word) == 0)
            {
                continue;
            }

            Tree* children = malloc(sizeof(Tree));
            children = generate_tree(words, possible_words[i], depth - 1);

            cvector_push_back(tree->childrens, children);
        }
    }

    return tree;
}

int16_t evaluate_word(char* word)
{
    UNUSED(word);
    return 0;
}

char* computer_turn(struct gameplay_T* _gameplay, struct start_T* _start)
{
    Tree* tree = generate_tree(_gameplay->words, _gameplay->current_word, _start->depth);
    print_tree(tree, _start->depth);

    free(tree);
    return "test";
}
