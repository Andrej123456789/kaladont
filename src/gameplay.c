#include "headers/gameplay.h"

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
}

void network_gameplay(Gameplay* _gameplay, Network* _network)
{
    int server_sockfd = 0;
    int client_sockfd = 0;

    ClientList* now;

    signal(SIGINT, catch_ctrl_c_and_exit);

    /* Create socket */
    server_sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (server_sockfd == -1) 
    {
        printf("Fail to create a socket!\n");
        return;
    }

    /* Socket information */
    struct sockaddr_in server_info, client_info;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY;
    server_info.sin_port = htons(_network->port);

    /* Bind and listen */
    bind(server_sockfd, (struct sockaddr *)&server_info, s_addrlen);
    listen(server_sockfd, 5);

    /* Gameplay stuff */
    set_random_word(_gameplay);

    /* Print server IP */
    getsockname(server_sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
    printf("Game started on: %s:%d!\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
    printf("Previous word is: %s\n\n", _gameplay->current_word);

    /* Initial linked list for clients */
    root = newNode(server_sockfd, inet_ntoa(server_info.sin_addr));
    now = root;

    while (1) 
    {
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);

        /* Print client IP */
        getpeername(client_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
        printf("Client %s:%d joined the game!\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

        /* Append linked list for clients */
        ClientList *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr));
        c->prev = now;
        now->link = c;
        now = c;

        ClientArg arguments;

        arguments.now = now;
        arguments.p_client = c;
        arguments._gameplay = _gameplay;

        pthread_t id;
        if (pthread_create(&id, NULL, client_handler, (void *)&arguments) != 0) 
        {
            perror("Create pthread error!\n");
            return;
        }
    }

    return;
}

void local_gameplay(Gameplay* _gameplay, Start* _start)
{
    bool game_finished = false;
    _gameplay->player = 0;

    Player players[_start->players];
    char user_input[1024];

    for (size_t i = 0; i < _start->players; i++)
    {
        players[i].points = 0;
    }

    set_random_word(_gameplay);
    while (!game_finished)
    {
        while (true)
        {
            printf("Previous word is: %s\n", _gameplay->current_word);

            printf("Player %lu: ", _gameplay->player);
            scanf("%1023s", user_input);

            if (strcmp(user_input, "exit") == 0)
            {
                printf("Exiting...\n");

                game_finished = true;
                break;
            }

            else if (strcmp(user_input, "next") == 0)
            {
                printf("You don't have a point!\n");
                break;
            }

            if (strcmp(get_first_N_characters(user_input, 2), get_last_N_characters(_gameplay->current_word, 2)) == 0 
                                                                && find_element(_gameplay->words, user_input)
                                                                && strlen(user_input) > 2)
            {
                printf("You have one point!\n");
                players[_gameplay->player].points += 1;

                if (strcmp(get_last_N_characters(user_input, 2), "nt") == 0)
                {
                    printf("Game ended... \n");

                    printf("Number of points of each player: \n");
                    for (size_t i = 0; i < _start->players; i++)
                    {
                        printf("Player %lu has %lu points. \n", i, players[i].points);
                    }

                    game_finished = true;
                    break;
                }

                strcpy(_gameplay->current_word, user_input);
                break;
            }
        }

        next_player(_gameplay, _start);
    }
}
