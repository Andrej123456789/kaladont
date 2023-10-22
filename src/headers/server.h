#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "utils.h"

#define LENGTH_NAME 31
#define LENGTH_MSG 101
#define LENGTH_SEND 201

struct gameplay_T;

/**
 * Struct containing client's information
 * @param data some data
 * @param prev previous client
 * @param link some link
 * @param ip client's ip
 * @param name client's name
 * @param points client's number of points
 * @param wait_turn did player play his turn
*/
typedef struct ClientNode 
{
    int data;

    struct ClientNode* prev;
    struct ClientNode* link;

    char ip[16];
    char name[31];

    uint64_t points;
    bool wait_turn;
} ClientList;

/**
 * Create new node on clients list
 * @param sockfd socket stuff
 * @param ip client's IP
*/
static ClientList *newNode(int sockfd, char* ip) 
{
    ClientList *np = (ClientList *)malloc( sizeof(ClientList) );
    np->data = sockfd;
    np->prev = NULL;
    np->link = NULL;
    np->wait_turn = false;
    strncpy(np->ip, ip, 16);
    strncpy(np->name, "NULL", 5);
    return np;
}

/**
 * Struct containing all arguments for `client_handler` function
 * @param root root
 * @param now now
 * @param p_client client
*/
typedef struct ClientArg
{
    ClientList* root;
    ClientList* now;
    void *p_client;
    struct gameplay_T* _gameplay;
} ClientArg ;

/**
 * Catch Ctrl-C and handle itž
 * @param root root
 * @param sig signal number
*/
void catch_ctrl_c_and_exit(ClientList* root, int sig);

/**
 * Send number to all clients
 * @param root root
 * @param tmp_buffer message to send to all clients
*/
void send_to_all_clients(ClientList* root, char tmp_buffer[]);

/**
 * Handle clients
 * @param client_arg arguments in struct because we pass this function to `pthread_create`
*/
void client_handler(void* client_arg);
