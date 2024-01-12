#include "headers/computer.h"

void clean_tree(Tree* tree)
{
    if (tree->childrens == NULL)
    {
        free(tree->word);
        free(tree);

        return;
    }

    for (size_t i = 0; i < cvector_size(tree->childrens); i++)
    {
        clean_tree(tree->childrens[i]);
    }

    cvector_free(tree->childrens);
}

Tree* generate_tree(cvector_vector_type(char*) words, char* current_word, uint64_t depth)
{
    Tree* tree = malloc(sizeof(Tree));
    tree->childrens = NULL;

    tree->word = malloc(sizeof(char) * strlen(current_word) + 1);
    strcpy(tree->word, current_word);

    cvector_vector_type(char*) possible_words = get_all_words_starting_on(words, get_last_N_characters(current_word, 2));

    if (cvector_size(possible_words) == 0 || depth == 0)
    {
        Tree* children = malloc(sizeof(Tree));

        children->word = malloc(sizeof(char) * strlen(current_word) + 1);
        strcpy(children->word, current_word);

        children->evaluation = -1000;
        children->childrens = NULL;

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

            if (depth == 0)
            {
                continue;
            }

            Tree* children = malloc(sizeof(Tree));

            erase_element(words, current_word);
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

    int16_t combinations[11] = {-6, 3, -4, 1, 10, 1, 2, 3, 4, 5};

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

Tree* search_tree(Tree* tree, int16_t depth, int16_t max_depth, int16_t alpha, int16_t beta)
{
    int16_t bestEval = 1000;    // -1000 if first node white; +1000 if first node black
                                // basically, we give worst value so we can "filter" real value

    char* bestWord = malloc(sizeof(char) * 1);

    if (tree->childrens == NULL || depth == 0)
    {
        tree->evaluation = evaluate_word(tree->word);
        return tree;
    }

    for (size_t i = 0; i < cvector_size(tree->childrens); i++)
    {
        Tree* node = search_tree(tree->childrens[i], depth - 1, max_depth, alpha, beta);

        int16_t eval = -node->evaluation;
        bestEval = minimum(eval, bestEval);     // `maximum` if first node white`
                                                // `minimum` if first node black

        tree->evaluation = eval;

        if (bestEval == eval)
        {
            bestWord = realloc(bestWord, sizeof(char) * strlen(node->word) + 1);
            strcpy(bestWord, node->word);
        }

        beta = minimum(beta, eval);
        if (beta <= alpha) 
        {
            break;
        }
    }

    tree->evaluation = bestEval;

    tree->word = realloc(tree->word, sizeof(char) * strlen(bestWord) + 1);
    strcpy(tree->word, bestWord);

    free(bestWord);
    return tree;
}

char* computer_turn(struct gameplay_T* _gameplay, struct start_T* _start)
{
    char* word = malloc(sizeof(char) * WORD_LIMIT);

    Tree* tree = generate_tree(_gameplay->words, _gameplay->current_word, _start->depth);

    if (tree == NULL)
    {
        printf("Error generating a tree!\n");
        return "";
    }

    search_tree(tree, _start->depth, _start->depth, -1000, 1000);
    print_tree(tree, _start->depth);
    printf("Computer choice is: %s | %"PRId16"\n", tree->word, tree->evaluation);

    strcpy(word, tree->word);
    clean_tree(tree);

    return word;
}
