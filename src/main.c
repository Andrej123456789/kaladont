#include <stdio.h>
#include <stdlib.h>

#include <limits.h>
#include <unistd.h>

#include "headers/gameplay.h"

void cleanup(Start* _start)
{
    free(_start->words);
}

void start(Start* _start)
{
    /* Load words */
    FILE* file;
    char buffer[255];

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
       printf("Current working dir: %s\n", cwd);
    }

    strcpy(_start->words_path, "words.txt");

    file = fopen(_start->words_path, "r");
    if (file == NULL)
    {
        printf("Failed to load file %s!\n", _start->words_path);
        return;
    }

    uint64_t word_count = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        word_count += 1;
    }

    _start->words = (char**)malloc(word_count * sizeof(char*));
    if (_start->words == NULL)
    {
        printf("Failed to allocate memory space!\n");
    }

    rewind(file);

    uint64_t i = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        _start->words[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(_start->words[i], buffer);

        i += 1;
    }

    fclose(file);

    // For example, let's print the words
    for (uint64_t j = 0; j < word_count; j++) {
        printf("Word %ld: %s\n", j + 1, _start->words[j]);
    }

    // Free the allocated memory
    for (uint64_t j = 0; j < word_count; j++) {
        free(_start->words[j]);
    }
}

int main()
{
    Start* _start = malloc(sizeof(Start));

    start(_start);
    cleanup(_start);

    return 0;
}
