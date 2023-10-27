#include "headers/server.h"
#include "headers/gameplay.h"

ClientList* root;

ClientList* newNode(int sockfd, char* ip)
{
    ClientList *np = (ClientList *)malloc( sizeof(ClientList) );
    np->data = sockfd;
    np->prev = NULL;
    np->link = NULL;
    strncpy(np->ip, ip, 16);
    strncpy(np->name, "NULL", 5);
    return np;
}

/* ------------------------------------ */

void catch_ctrl_c_and_exit(int sig) 
{
    ClientList *tmp;

    while (root != NULL) 
    {
        printf("\nClose socketfd: %d\n", root->data);

        /* Close all socket include server_sockfd */
        close(root->data);

        tmp = root;
        root = root->link;

        free(tmp);
    }

    printf("Bye\n");
    exit(sig);
}

void send_to_all_clients(char tmp_buffer[]) 
{
    ClientList *tmp = root->link;

    while (tmp != NULL) 
    {
        printf("Send to sockfd %d: %s \n", tmp->data, trim_whitespace(tmp_buffer));
        send(tmp->data, tmp_buffer, LENGTH_SEND, 0);

        tmp = tmp->link;
    }
}

void* client_handler(void* client_arg)
{
    ClientArg *args = (ClientArg *)client_arg;
    struct gameplay_T* _gameplay = args->_gameplay;

    int leave_flag = 0;
    char nickname[LENGTH_NAME]; 
    char recv_buffer[LENGTH_MSG];
    char send_buffer[LENGTH_SEND];
    ClientList *np = (ClientList *)args->p_client;

    /* Naming */
    if (recv(np->data, nickname, LENGTH_NAME, 0) <= 0 || strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME - 1) 
    {
        printf("%s didn't input name.\n", np->ip);
        leave_flag = 1;
    } 
    
    else 
    {
        strncpy(np->name, nickname, LENGTH_NAME);
        printf("%s (%s)(%d) joined the game!\n\n", np->name, np->ip, np->data);
        sprintf(send_buffer, "%s (%s) joined the game!\n", np->name, np->ip);
        send_to_all_clients(send_buffer);

        NetworkPlayer* new = malloc(sizeof(NetworkPlayer));

        new->name = malloc(sizeof(char) * LENGTH_NAME);
        strcpy(new->name, np->name);

        new->points = 0;

        cvector_push_back(_gameplay->network_points, new);
    }

    printf("%"PRIu64"\n", cvector_size(_gameplay->network_points));

    sprintf(send_buffer, "Previous word is: %s\n", _gameplay->current_word);
    send_to_all_clients(send_buffer);

    /* Conversation */
    while (1) 
    {
        if (leave_flag) 
        {
            break;
        }

        int receive = recv(np->data, recv_buffer, LENGTH_MSG, 0);
        if (receive > 0)
        {
            if (strlen(recv_buffer) == 0) 
            {
                continue;
            }

            sprintf(send_buffer, "%s:%s from %s", np->name, recv_buffer, np->ip);
            send_to_all_clients(send_buffer);

            int result = gameplay(_gameplay, np, recv_buffer, true);

            if (result == -1)
            {
                for (size_t i = 0; i < cvector_size(_gameplay->network_points); i++)
                {
                    if (strcmp(_gameplay->network_points[i]->name, np->name) == 0)
                    {
                        _gameplay->network_points[i]->points += 1;
                    }
                }

                for (size_t i = 0; i < cvector_size(_gameplay->network_points); i++)
                {
                    sprintf(send_buffer, "Player %s has %"PRIu64" points!\n", _gameplay->network_points[i]->name, _gameplay->network_points[i]->points);
                    send_to_all_clients(send_buffer);
                }

                leave_flag = 1;
            }

            else if (result == 1)
            {
                for (size_t i = 0; i < cvector_size(_gameplay->network_points); i++)
                {
                    if (strcmp(_gameplay->network_points[i]->name, np->name) == 0)
                    {
                        _gameplay->network_points[i]->points += 1;
                    }
                }
            }

            else
            {
                
            }
        }
        
        else if (receive == 0 || strcmp(recv_buffer, "exit") == 0) 
        {
            printf("%s(%s)(%d) leave the chatroom.\n", np->name, np->ip, np->data);
            sprintf(send_buffer, "%s(%s) leave the chatroom.", np->name, np->ip);
            leave_flag = 1;
        } 
        
        else 
        {
            printf("Fatal Error: -1\n");
            leave_flag = 1;
        }

        sprintf(send_buffer, "Previous word is: %s\n", _gameplay->current_word);
        send_to_all_clients(send_buffer);
    }

    /* Remove node */
    close(np->data);

    /* Remove an edge node */
    if (np == args->now) 
    {
        args->now = np->prev;
        args->now->link = NULL;
    } 
    
    /* Remove a middle node */
    else 
    {
        np->prev->link = np->link;
        np->link->prev = np->prev;
    }

    for (size_t i = 0; i < cvector_size(_gameplay->network_points); i++)
    {
        free(_gameplay->network_points[i]->name);
        free(_gameplay->network_points[i]);
    }

    free(np);
    return NULL;
}
