#include "headers/computer.h"

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

int counter = 0;

int16_t evaluate_word(char* word)
{
    UNUSED(word);

    int16_t combinations[11] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};

    int16_t result = combinations[counter];
    counter++;

    return result;
}

void print_tree(Tree* tree, uint16_t depth) 
{
    if (tree == NULL) return;

    for (uint16_t i = 0; i < depth; i++) 
    {
        printf("  ");
    }

    printf("|- %s (%"PRId16")\n", tree->word, tree->evaluation);

    for (size_t i = 0; i < cvector_size(tree->childrens); i++) 
    {
        print_tree(tree->childrens[i], depth + 1);
    }
}

Tuple search_tree(Tree* tree, int16_t depth)
{
    int16_t bestEval = 1000;    // -1000 if first node white; +1000 if first node black
                                // basically, we give worst value so we can "filter" real value

    if (tree->childrens == NULL)
    {
        Tuple tuple;
    
        strcpy(tuple.word, tree->word);
        tuple.evaluation = tree->evaluation;

        return tuple;   
    }

    for (size_t i = 0; i < cvector_size(tree->childrens); i++)
    {
        Tuple tuple = search_tree(tree->childrens[i], depth - 1);

        int16_t eval = -tuple.evaluation;
        bestEval = minimum(eval, bestEval);     // `maximum` if first node white`
                                                // `minimum` if first node black

        tree->evaluation = eval;

        if (bestEval < tree->evaluation)        // > if first node is white
                                                // < if first node is black
        {
            strcpy(tree->word, tuple.word);
        }
    }

    Tuple tuple;

    strcpy(tuple.word, tree->word);
    tuple.evaluation = bestEval;

    return tuple; 
}

char* computer_turn(struct gameplay_T* _gameplay, struct start_T* _start)
{
    char* word = malloc(sizeof(char) * WORD_LIMIT);

    Tree* tree = generate_tree(_gameplay->words, _gameplay->current_word, _start->depth);
    search_tree(tree, _start->depth);

    print_tree(tree, _start->depth);
    printf("Result is: %s | %"PRId16"\n", tree->word, tree->evaluation);

    strcpy(word, tree->word);
    free(tree);

    return word;
}
