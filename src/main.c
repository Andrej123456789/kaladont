#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>
#include <unistd.h>

#include <json-c/json.h>
#include "headers/gameplay.h"

/**
 * Free all allocated stuff
 * @param _computer `Bot` struct
 * @param _gameplay `Gameplay` struct
*/
void cleanup(Computer* _computer, Gameplay* _gameplay)
{
    free(_gameplay->current_word);

    cvector_free(_computer->sequence); 
    cvector_free(_gameplay->network_points);
    cvector_free(_gameplay->timeline);
    cvector_free(_gameplay->words);
}

/**
 * Load settings and words list
 * @param _computer `Bot` struct, destionation for bot information
 * @param _gameplay `Gameplay` struct, destination for words list
 * @param _network `Network` struct, destination for network information
 * @param _start `Start` struct, destination for settings (house rules, number of players & others)
 * @param path path to `.json` file
 * @return int
*/
int start(Computer* _computer, Gameplay* _gameplay, Network* _network, Start* _start, char* path)
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
            for (size_t i = 0; i < json_object_array_length(val); i++) 
            {
                struct json_object *element = json_object_array_get_idx(val, i);
                cvector_push_back(_start->words_path, strdup(json_object_get_string(element)));
            }
        }

        else if (strcmp(key, "computer") == 0)
        {
            struct json_object* bot;

            struct json_object_iterator it2;
            struct json_object_iterator itEnd2;

            for (size_t i = 0; i < json_object_array_length(val); i++) 
            {
                struct json_object *element = json_object_array_get_idx(val, i);
                bot = json_tokener_parse(json_object_get_string(element));
            }

            it2 = json_object_iter_init_default();
            it2 = json_object_iter_begin(bot);
            itEnd2 = json_object_iter_end(bot);

            while (!json_object_iter_equal(&it2, &itEnd2))
            {
                const char* key2 = json_object_iter_peek_name(&it2);
                json_object* val2 = json_object_iter_peek_value(&it2);

                if (strcmp(key2, "sequence") == 0)
                {
                    char* temp_sequence = realloc(temp_sequence, sizeof(char) * json_object_get_string_len(val2) + 1);
                    strcpy(temp_sequence, json_object_get_string(val2));

                    for (size_t i = 0; i < strlen(temp_sequence); i++)
                    {
                        cvector_push_back(_computer->sequence, temp_sequence[i]);
                    }

                    /* Free the string */
                    free(temp_sequence);
                }

                else if (strcmp(key2, "depth") == 0)
                {
                    _start->depth = (uint16_t)json_object_get_int(val2);
                }

                json_object_iter_next(&it2);
            }
        }

        else if (strcmp(key, "network") == 0)
        {
            struct json_object* network;

            struct json_object_iterator it2;
            struct json_object_iterator itEnd2;

            for (size_t i = 0; i < json_object_array_length(val); i++) 
            {
                struct json_object *element = json_object_array_get_idx(val, i);
                network = json_tokener_parse(json_object_get_string(element));
            }

            it2 = json_object_iter_init_default();
            it2 = json_object_iter_begin(network);
            itEnd2 = json_object_iter_end(network);

            while (!json_object_iter_equal(&it2, &itEnd2))
            {
                const char* key2 = json_object_iter_peek_name(&it2);
                json_object* val2 = json_object_iter_peek_value(&it2);

                if (strcmp(key2, "enabled") == 0)
                {
                    _network->enabled = json_object_get_boolean(val2);
                }

                else if (strcmp(key2, "port") == 0)
                {
                    _network->port = (uint16_t)json_object_get_int(val2);
                }

                json_object_iter_next(&it2);
            }
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);

    /* Load words */
    FILE* file;
    char buffer[255];

    _gameplay->words = NULL;
    for (size_t i = 0; i < cvector_size(_start->words_path); i++)
    {
        file = fopen(_start->words_path[i], "r");

        if (file == NULL)
        {
            printf("Failed to load file %s!\n", _start->words_path[i]);
            return 1;
        }

        uint64_t j = 0;
        while (fgets(buffer, sizeof(buffer), file))
        {
            buffer[strcspn(buffer, "\n")] = '\0'; /* remove \n */
            cvector_push_back(_gameplay->words, strdup(buffer));

            j += 1;
        }

        fclose(file);
    }

    return 0;
}

/**
 * Entry point
*/
int main()
{
    Computer* _computer = malloc(sizeof(Computer));
    Gameplay* _gameplay = malloc(sizeof(Gameplay));
    Network* _network = malloc(sizeof(Network));
    Start* _start = malloc(sizeof(Start));

    _computer->sequence = NULL;

    _gameplay->current_word = malloc(sizeof(char) * 1024);
    _gameplay->network_points = NULL;

    if (start(_computer, _gameplay, _network, _start, "settings/settings.json") != 0)
    {
        goto end;
    }

    if (_network->enabled)
    {
        network_gameplay(_gameplay, _network);
    }

    else
    {
        local_gameplay(_computer, _gameplay, _start);
    }


end:
    cleanup(_computer, _gameplay);
    return 0;
}
