#include "headers/gameplay.h"

bool find_element(cvector_vector_type(char*) vec, char* str)
{
    for (size_t i = 0; i < cvector_size(vec); i++)
    {
        if (strcmp(str, vec[i]) == 0)
        {
            return true;
        }
    }
    
    return false;
}

char* get_last_N_characters(const char* input, int N)
{
    char result[255];

    if (N <= 0) 
    {
        result[0] = '\0';
        return;
    }

    int length = strlen(input);
    if (length < N) 
    {
        N = length;
    }

    strncpy(result, input + (length - N), N);
    result[N] = '\0';

    return strdup(result);
}

char* get_first_N_characters(const char* input, int N)
{
    char result[255];

    if (N <= 0) 
    {
        result[0] = '\0';
        return;
    }

    strncpy(result, input, N);
    result[N] = '\0';

    return strdup(result);
}

/* ------------------------------------ */

void next_player(Gameplay* _gameplay, Start* _start)
{
    _gameplay->player += 1;
    if (_gameplay->player > _start->players)
    {
        _gameplay->player = 0;
    }
}

char* random_word(Gameplay* _gameplay)
{
    /* Seed the random number generator with the current time */
    srand(time(0));

    /* Get random vector position */
    size_t pos = (rand() % (cvector_size(_gameplay->words) - 0 + 1)) + 0;

    /* Return string at selected position */
    return _gameplay->words[pos];
}

void set_random_word(Gameplay* _gameplay)
{
    char* rand_word = random_word(_gameplay);

    cvector_push_back(_gameplay->timeline, rand_word);
    strcpy(_gameplay->current_word, rand_word);

    printf("Current word is: %s\n", rand_word);
}

void gameplay(Gameplay* _gameplay, Start* _start)
{
    bool game_finished = false;
    _gameplay->player = 0;

    char user_input[1024];
    while (!game_finished)
    {
        set_random_word(_gameplay);

        printf("Player %lu: ", _gameplay->player);
        scanf("%1023s", user_input);

        if (strcmp(user_input, "exit") == 0)
        {
            printf("Exiting...\n");
            return;
        }

        if (strcmp(get_first_N_characters(user_input, 2), get_last_N_characters(_gameplay->current_word, 2)) == 0 && find_element(_gameplay->words, user_input))
        {
            printf("You have one point!\n");
        }

        else
        {
            printf("You don't have one point!\n");
        }

        next_player(_gameplay, _start);
    } 
}
