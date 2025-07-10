/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Server code
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "headers/server.h"
#include "headers/gameplay.h"

/**
 * Enables non-blocking mode on a file descriptor.
 * @param fd File descriptor to set.
 * @return int
 */
static int set_nonblocking(int fd)
{
    int fl = fcntl(fd, F_GETFL, 0);
    return (fl < 0) ? -1 : fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}

int net_start_server(uint16_t port, uint16_t max_players)
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) { perror("socket"); return -1; }

    int yes = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    struct sockaddr_in addr = { .sin_family = AF_INET,
                                .sin_addr.s_addr = htonl(INADDR_ANY),
                                .sin_port = htons(port) };

    if (bind(s, (struct sockaddr*)&addr, sizeof addr) < 0 ||
        listen(s, max_players) < 0 ||
        set_nonblocking(s) < 0)
    {
        perror("net_start_server");
        close(s);

        return -1;
    }

    fprintf(stderr, "[server] listening on %u\n", port);
    return s;
}

void net_accept_clients(int listener_fd, Gameplay* g)
{
    for (;;) 
    {
        struct sockaddr_in cli; socklen_t len = sizeof cli;
        int c = accept(listener_fd, (struct sockaddr*)&cli, &len);

        if (c < 0)
        {
            if (errno != EWOULDBLOCK && errno != EAGAIN) perror("accept");
            break;
        }

        if (set_nonblocking(c) < 0) { perror("fcntl"); close(c); continue; }

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
            const char* msg = "Server is full.\n";
            send(c, msg, strlen(msg), 0);  close(c);  continue;
        }

        NetworkPlayer *np = &g->players[i].network_player;
        np->sockfd = c;
        np->ready  = false;
        np->inbuf[0] = '\0';

        fprintf(stderr, "[server] client %d bound to player %d (%s)\n",
                c, i, inet_ntoa(cli.sin_addr));
    }
}

void net_poll_clients(Gameplay* g)
{
    fd_set rfds;  FD_ZERO(&rfds);
    int maxfd = -1;

    for (int i = 0; i < g->number_of_players; ++i) 
    {
        if (g->players_sequence[i] != '2') continue;

        int s = g->players[i].network_player.sockfd;
        if (s > 0) { FD_SET(s, &rfds); if (s > maxfd) maxfd = s; }
    }

    if (maxfd < 0) return;                      /* nobody connected */

    struct timeval tv = {0,0};
    if (select(maxfd+1, &rfds, NULL, NULL, &tv) <= 0) return;

    char ch;
    for (int i = 0; i < g->number_of_players; ++i) 
    {
        if (g->players_sequence[i] != '2') continue;

        NetworkPlayer *np = &g->players[i].network_player;
        if (np->sockfd <= 0 || !FD_ISSET(np->sockfd, &rfds)) continue;

        while (read(np->sockfd, &ch, 1) == 1) 
        {
            if (ch == '\r') continue;
            if (ch == '\n') { np->ready = true; break; }
            size_t l = strlen(np->inbuf);
            if (l < WORD_LIMIT) { np->inbuf[l]=ch; np->inbuf[l+1]='\0'; }
        }
    }
}

/**
 * Formats a message and sends it over a socket.
 * @param fd file descriptor
 * @param fmt message
 * @param ap variable argument list
 */
static void vsend(int fd, const char* fmt, va_list ap)
{
    char buf[WORD_LIMIT + 1];
    int  n = vsnprintf(buf, sizeof buf, fmt, ap);
    if (n < 0) return;
    send(fd, buf, (size_t)n, 0);
}

void send_to_player(Player* p, const char* fmt, ...)
{
    if (p->network_player.sockfd <= 0) return;
    va_list ap; va_start(ap, fmt);
    vsend(p->network_player.sockfd, fmt, ap);
    va_end(ap);
}

void broadcast(Gameplay* g, const char* fmt, ...)
{
    va_list ap1, ap2;
    va_start(ap1, fmt);

    for (int i = 0; i < g->number_of_players; ++i) 
    {
        if (g->players_sequence[i] != '2') continue;

        int s = g->players[i].network_player.sockfd;
        if (s <= 0) continue;

        /* duplicate va_list for each send */
        va_copy(ap2, ap1);
        char buf[WORD_LIMIT+1];
        int n = vsnprintf(buf, sizeof buf, fmt, ap2);
        va_end(ap2);
        if (n > 0) send(s, buf, (size_t)n, 0);
    }

    va_end(ap1);
}
