#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>
#include <unistd.h>

#include <json-c/json.h>
#include "headers/gameplay.h"

/**
 * Free all allocated stuff
 * @param _gameplay `Gameplay` struct
*/
void cleanup(Gameplay* _gameplay)
{
    free(_gameplay->current_word);

    cvector_free(_gameplay->timeline);
    cvector_free(_gameplay->words);
}

/**
 * Load settings and words list
 * @param _gameplay `Gameplay` struct, destination for words list
 * @param _start `Start` struct, destination
 * @param path path to `.json` file 
*/
void start(Gameplay* _gameplay, Start* _start, char* path)
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
            if (json_object_get_uint64(val) < UINT64_MAX)
            {
                _start->players = json_object_get_uint64(val);
            }

            else
            {
                printf("Number of players (%ld) is higher than maximum (%ld - 1)!\n", json_object_get_uint64(val), UINT64_MAX);
                printf("Setting number of players to default, 20.\n");
            }
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

    uint64_t i = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = '\0'; /* remove \n */
        cvector_push_back(_gameplay->words, strdup(buffer));

        i += 1;
    }

    fclose(file);
}

/**
 * Entry point
*/
int main()
{
    Start* _start = malloc(sizeof(Start));
    Gameplay* _gameplay = malloc(sizeof(Gameplay));

    _gameplay->current_word = malloc(sizeof(char) * 1024);

    start(_gameplay, _start, "settings/settings.json");
    gameplay(_gameplay, _start);

    cleanup(_gameplay);
    return 0;
}
