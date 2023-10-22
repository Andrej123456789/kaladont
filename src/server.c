#include "headers/server.h"
#include "headers/gameplay.h"

void catch_ctrl_c_and_exit(ClientList* root, int sig) 
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
    exit(EXIT_SUCCESS);
}

void send_to_all_clients(ClientList* root, char tmp_buffer[]) 
{
    ClientList *tmp = root->link;

    while (tmp != NULL) 
    {
        printf("Send to sockfd %d: %s \n", tmp->data, trim_whitespace(tmp_buffer));
        send(tmp->data, tmp_buffer, LENGTH_SEND, 0);

        tmp = tmp->link;
    }
}

void client_handler(void* client_arg)
{
    ClientArg *args = (ClientArg *)client_arg;
    struct gameplay_T* _gameplay = args->_gameplay;

    int leave_flag = 0;
    char nickname[LENGTH_NAME] = {};
    char recv_buffer[LENGTH_MSG] = {};
    char send_buffer[LENGTH_SEND] = {};
    ClientList *np = (ClientList *)args->p_client;

    /* Naming */
    if (recv(np->data, nickname, LENGTH_NAME, 0) <= 0 || strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME-1) 
    {
        printf("%s didn't input name.\n", np->ip);
        leave_flag = 1;
    } 
    
    else 
    {
        strncpy(np->name, nickname, LENGTH_NAME);
        printf("%s (%s)(%d) joined the game!\n\n", np->name, np->ip, np->data);
        sprintf(send_buffer, "%s (%s) joined the game!\n", np->name, np->ip);
        send_to_all_clients(args->root, send_buffer);
    }

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
            send_to_all_clients(args->root, send_buffer);

            if (strcmp(recv_buffer, "next") == 0)
            {
                sprintf(send_buffer, "%s don't have a point!\n", np->name);
                send_to_all_clients(args->root, send_buffer);
            }

            if (strcmp(get_first_N_characters(recv_buffer, 2), get_last_N_characters(_gameplay->current_word, 2)) == 0 
                                                                && find_element(_gameplay->words, recv_buffer)
                                                                && strlen(recv_buffer) > 2)
            {

                sprintf(send_buffer, "%s have one point!\n", np->name);
                send_to_all_clients(args->root, send_buffer);

                np->points += 1;

                if (strcmp(get_last_N_characters(recv_buffer, 2), "nt") == 0)
                {
                    send_to_all_clients(args->root, "Game ended... \n");

                    break;
                }

                strcpy(_gameplay->current_word, recv_buffer);

                sprintf(send_buffer, "Previous word is: %s!\n", _gameplay->current_word);
                send_to_all_clients(args->root, send_buffer);
            }

            else
            {
                sprintf(send_buffer, "%s don't have a point!\n", np->name);
                send_to_all_clients(args->root, send_buffer);
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

    free(np);
}
