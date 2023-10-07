#include <stdio.h>
#include <stdlib.h>

#include <limits.h>
#include <unistd.h>

#include <json-c/json.h>
#include "headers/gameplay.h"

void cleanup(Start* _start)
{
    free(_start->words);
}

void start(Start* _start, char* path)
{
    /* Load JSON */
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path);
    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd)) 
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "kaladont_allowed") == 0)
        {
            _start->kaladont_allowed = json_object_get_boolean(val);
        }

        else if (strcmp(key, "players") == 0)
        {
            _start->players = json_object_get_uint64(val);
        }

        else if (strcmp(key, "words_path") == 0)
        {
            strcpy(_start->words_path, json_object_get_string(val));
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);

    /* Load words */
    FILE* file;
    char buffer[255];

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
}

int main()
{
    Start* _start = malloc(sizeof(Start));
    Gameplay* _gameplay = malloc(sizeof(Gameplay));

    start(_start, "settings/settings.json");
    gameplay(_gameplay, _start);

    cleanup(_start);
    return 0;
}
