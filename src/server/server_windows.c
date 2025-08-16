/**
 * @author Andrej...
 * PROJECT: kaladont
 * LICENSE: MIT
 * DESCRIPTION: Windows Server code
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "../headers/server.h"
#include "../headers/gameplay.h"

/**
 * Enables non-blocking mode on a socket.
 * @param s SOCKET
 * @return int
 */
static int set_nonblocking(SOCKET s)
{
    u_long mode = 1;
    return ioctlsocket(s, FIONBIO, &mode);
}

int net_start_server(uint16_t port, uint16_t max_players)
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        fprintf(stderr, "WSAStartup failed\n");
        return -1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) { perror("socket"); return -1; }

    int yes = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof yes);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (bind(s, (struct sockaddr*)&addr, sizeof addr) == SOCKET_ERROR ||
        listen(s, max_players) == SOCKET_ERROR ||
        set_nonblocking(s) != 0)
    {
        fprintf(stderr, "net_start_server: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return -1;
    }

    fprintf(stderr, "[server] listening on %u\n", port);
    return (int)s;
}

void net_accept_clients(int listener_fd, Gameplay* g)
{
    SOCKET listener = (SOCKET)listener_fd;
    for (;;) 
    {
        struct sockaddr_in cli; int len = sizeof cli;
        SOCKET c = accept(listener, (struct sockaddr*)&cli, &len);

        if (c == INVALID_SOCKET)
        {
            int err = WSAGetLastError();
            if (err != WSAEWOULDBLOCK) fprintf(stderr, "accept: %d\n", err);
            break;
        }

        if (set_nonblocking(c) != 0) { fprintf(stderr, "fcntl: %d\n", WSAGetLastError()); closesocket(c); continue; }

        /* find first slot whose sequence == '2' and sockfd == 0                */
        int i;
        for (i = 0; i < g->number_of_players; ++i)
        {
            if (g->players_sequence[i] == '2' && g->players[i].network_player.sockfd <= 0)
            {
                break;
            }
        }

        if (i == g->number_of_players)
        {
            const char msg[] = "Server is full.\n";
            send(c, msg, (int)sizeof(msg), 0);  
            closesocket(c);  
            continue;
        }

        NetworkPlayer *np = &g->players[i].network_player;
        np->sockfd = (int)c;
        np->ready  = false;
        np->inbuf[0] = '\0';

        fprintf(stderr, "[server] client %d bound to player %d (%s)\n",
                (int)c, i, inet_ntoa(cli.sin_addr));
    }
}

void net_poll_clients(Gameplay* g)
{
    fd_set rfds;  FD_ZERO(&rfds);
    SOCKET maxfd = 0;

    for (int i = 0; i < g->number_of_players; ++i) 
    {
        if (g->players_sequence[i] != '2') continue;

        SOCKET s = (SOCKET)g->players[i].network_player.sockfd;
        if (s > 0) { FD_SET(s, &rfds); if (s > maxfd) maxfd = s; }
    }

    if (maxfd == 0) return;  /* nobody connected */

    struct timeval tv = {0,0};
    if (select((int)maxfd+1, &rfds, NULL, NULL, &tv) <= 0) return;

    char ch;
    for (int i = 0; i < g->number_of_players; ++i) 
    {
        if (g->players_sequence[i] != '2') continue;

        NetworkPlayer *np = &g->players[i].network_player;
        SOCKET s = (SOCKET)np->sockfd;
        if (s <= 0 || !FD_ISSET(s, &rfds)) continue;

        while (recv(s, &ch, 1, 0) == 1) 
        {
            if (ch == '\r') continue;
            if (ch == '\n') { np->ready = true; break; }
            size_t l = strlen(np->inbuf);
            if (l < WORD_LIMIT) { np->inbuf[l]=ch; np->inbuf[l+1]='\0'; }
        }
    }
}

static void vsend(SOCKET s, const char* fmt, va_list ap)
{
    char buf[WORD_LIMIT + 1];
    int  n = vsnprintf(buf, sizeof buf, fmt, ap);
    if (n < 0) return;
    send(s, buf, n, 0);
}

void send_to_player(Player* p, const char* fmt, ...)
{
    if (p->network_player.sockfd <= 0) return;
    va_list ap; va_start(ap, fmt);
    vsend((SOCKET)p->network_player.sockfd, fmt, ap);
    va_end(ap);
}

void broadcast(Gameplay* g, const char* fmt, ...)
{
    va_list ap1, ap2;
    va_start(ap1, fmt);

    for (int i = 0; i < g->number_of_players; ++i) 
    {
        if (g->players_sequence[i] != '2') continue;

        SOCKET s = (SOCKET)g->players[i].network_player.sockfd;
        if (s <= 0) continue;

        va_copy(ap2, ap1);
        char buf[WORD_LIMIT+1];
        int n = vsnprintf(buf, sizeof(buf), fmt, ap2);
        va_end(ap2);
        if (n > 0) send(s, buf, n, 0);
    }

    va_end(ap1);
}
