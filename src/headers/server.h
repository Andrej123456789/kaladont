#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "c_vector.h"
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
*/
typedef struct ClientNode 
{
    int data;

    struct ClientNode* prev;
    struct ClientNode* link;

    char ip[16];
    char name[31];
} ClientList;

/**
 * Struct containing network player's informations
 * @param points number of points
*/
typedef struct NetworkPlayer
{
    char name[LENGTH_NAME];
    uint64_t points;
} NetworkPlayer;

/**
 * Create new node on clients list
 * @param sockfd socket stuff
 * @param ip client's IP
*/
ClientList* newNode(int sockfd, char* ip);

extern ClientList* root;

/**
 * Struct containing all arguments for `client_handler` function
 * @param now now
 * @param p_client client
 * @param _gameplay `Gameplay` struct
*/
typedef struct ClientArg
{
    ClientList* now;
    void *p_client;
    struct gameplay_T* _gameplay;
    cvector_vector_type(NetworkPlayer*) players;
} ClientArg ;

/**
 * Catch Ctrl-C and handle it
 * @param sig signal number
*/
void catch_ctrl_c_and_exit(int sig);

/**
 * Send number to all clients
 * @param tmp_buffer message to send to all clients
*/
void send_to_all_clients(char tmp_buffer[]);

/**
 * Handle clients
 * @param client_arg arguments in struct because we pass this function to `pthread_create`
*/
void* client_handler(void* client_arg);
