#include "headers/computer.h"

int16_t evaluate_word(char* word)
{
    UNUSED(word);

    int16_t combinations[11] = {-6, 3, -4, 1, 10, 1, 2, 3, 4, 5};

    int16_t result = combinations[rand() % 
        (11 - 0 + 1) + 0];

    return result;
}

int16_t search(Gameplay _gameplay, Evaluation* evaluation, uint16_t depth)
{
    int16_t bestEval = 1000;    // -1000 if first node white; +1000 if first node black
                                // basically, we give worst value so we can "filter" real value

    if (depth == 0)
    {
        return evaluate_word(_gameplay.current_word);
    }

    cvector_vector_type(char*) possible_words = get_all_words_starting_on(_gameplay.words, get_last_N_characters(_gameplay.current_word, 2));

    if (possible_words == 0)
    {
        return -1000;
    }

    for (size_t i = 0; i < cvector_size(possible_words); i++)
    {
        Gameplay copy;

        copy.current_word = malloc(sizeof(char) * strlen(possible_words[i]) + 1);
        strcpy(copy.current_word, possible_words[i]);

        copy.words = _gameplay.words;

        int16_t eval = -search(_gameplay, evaluation, depth - 1);
        bestEval = minimum(eval, bestEval);

        if (bestEval == eval)
        {
            evaluation->bestWord = realloc(evaluation->bestWord, sizeof(char) * strlen(possible_words[i]) + 1);
            strcpy(evaluation->bestWord, possible_words[i]);
        }
    }

    return bestEval;
}

char* computer_turn(struct gameplay_T* _gameplay, struct start_T* _start)
{
    char* word = malloc(sizeof(char) * 1);

    Evaluation* evaluation = malloc(sizeof(Evaluation));

    evaluation->bestWord = malloc(sizeof(char) * 1);
    strcpy(evaluation->bestWord, "\0");

    search(*_gameplay, evaluation, _start->depth);

    word = realloc(word, sizeof(char) * strlen(evaluation->bestWord) + 1);
    strcpy(word, evaluation->bestWord);

    free(evaluation->bestWord);
    free(evaluation);

    return word;
}
