/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Program's entry point
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <json-c/json.h>

#include "headers/gameplay.h"

/**
 * Frees all allocated stuff
 * @param _gameplay `Gameplay` struct
*/
void cleanup(Gameplay* _gameplay)
{
    if (_gameplay->players != NULL)
    {
        free(_gameplay->players);
    }

    if (_gameplay->players_sequence != NULL)
    {
        free(_gameplay->players_sequence);
    }

    if (_gameplay->words_path != NULL)
    {
        for (size_t i = 0; i < cvector_size(_gameplay->words_path); i++)
        {
            free(_gameplay->words_path[i]);
        }

        cvector_free(_gameplay->words_path);
    }

    if (_gameplay->words != NULL)
    {
        for (size_t i = 0; i < cvector_size(_gameplay->words); i++)
        {
            free(_gameplay->words[i]);
        }

        cvector_free(_gameplay->words);
    }
}

/**
 * Loads settings and list of words
 * @param _gameplay `Gameplay` struct
 * @param path path to the `.json` file
 * @return int
*/
int start(Gameplay* _gameplay, char* path)
{
    /* Load JSON */
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path);
    if (root == NULL)
    {
        return 1;
    }

    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "players") == 0)
        {
            // value will not exceed UINT16_MAX limit
            _gameplay->number_of_players = (uint16_t)json_object_get_int(val);
        }

        else if (strcmp(key, "players_sequence") == 0)
        {
            if (_gameplay->number_of_players != json_object_get_string_len(val))
            {
                printf("Sequence does not match specified number of players!\n");
                return 1;
            }

            _gameplay->players_sequence = malloc(_gameplay->number_of_players * sizeof(char));
            strcpy(_gameplay->players_sequence, json_object_get_string(val));
        }

        else if (strcmp(key, "kaladont_allowed") == 0)
        {
            _gameplay->kaladont_allowed = json_object_get_boolean(val);
        }

        else if (strcmp(key, "wait_for_correct_word") == 0)
        {
            _gameplay->wait_for_correct_word = json_object_get_boolean(val);
        }

        else if (strcmp(key, "words_path") == 0)
        {
            for (size_t i = 0; i < json_object_array_length(val); i++) 
            {
                struct json_object* element = json_object_array_get_idx(val, i);
                cvector_push_back(_gameplay->words_path, strdup(json_object_get_string(element)));
            }
        }

        else if (strcmp(key, "computer") == 0)
        {
            struct json_object* computer;

            struct json_object_iterator it2;
            struct json_object_iterator itEnd2;

            for (size_t i = 0; i < json_object_array_length(val); i++)
            {
                struct json_object* element = json_object_array_get_idx(val, i);
                computer = json_tokener_parse(json_object_get_string(element));
            }

            it2 = json_object_iter_init_default();
            it2 = json_object_iter_begin(computer);
            itEnd2 = json_object_iter_end(computer);

            while (!json_object_iter_equal(&it2, &itEnd2))
            {
                const char* key2 = json_object_iter_peek_name(&it2);
                json_object* val2 = json_object_iter_peek_value(&it2);

                if (strcmp(key2, "depth") == 0)
                {
                    _gameplay->depth = (uint16_t)json_object_get_int(val2);
                }

                json_object_iter_next(&it2);
            }

            json_object_put(computer);
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
                // json_object* val2 = json_object_iter_peek_value(&it2);

                if (strcmp(key2, "enabled") == 0)
                {

                }

                else if (strcmp(key2, "port") == 0)
                {

                }

                json_object_iter_next(&it2);
            }

            json_object_put(network);
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);

    /* Load words */
    FILE* file;
    char buffer[WORD_LIMIT + 1]; // +1 for '\0'

    for (size_t i = 0; i < cvector_size(_gameplay->words_path); i++)
    {
        file = fopen(_gameplay->words_path[i], "r");

        if (file == NULL)
        {
            printf("Failed to load file %s!\n", _gameplay->words_path[i]);
            return 1;
        }

        while (fgets(buffer, sizeof(buffer), file))
        {
            buffer[strcspn(buffer, "\n")] = '\0'; /* remove \n */
            cvector_push_back(_gameplay->words, strdup(buffer));
        }

        fclose(file);
    }

    return 0;
}

/**
 * Entry point
*/
int main(int argc, char* argv[])
{
    Gameplay* _gameplay = malloc(sizeof(Gameplay));

    _gameplay->players = NULL;
    _gameplay->players_sequence = NULL;
    _gameplay->words_path = NULL;
    _gameplay->words = NULL;

    char path[256];
    if (argc < 2)
    {
        printf("Enter the path: ");
        scanf("%255s", path);
    }

    else
    {
        strncpy(path, argv[1], 255);
        path[256] = '\0';
    }

    if (start(_gameplay, path) != 0)
    {
        goto end;
    }

    gameplay_entry(_gameplay);

end:
    cleanup(_gameplay);
    free(_gameplay);

    return 0;
}
