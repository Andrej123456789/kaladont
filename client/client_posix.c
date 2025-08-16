/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: kaladont
 * LICENSE: MIT license
 * DESCRIPTION: Client code (POSIX)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define WORD_SIZE 62
#define BUF (WORD_SIZE + 1)

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

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "use: %s <host> <port>\n", argv[0]);
        return 1;
    }

    /* --- connect --- */
    int    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    struct sockaddr_in srv = { .sin_family = AF_INET,
                               .sin_port   = htons(atoi(argv[2])) };
    if (inet_pton(AF_INET, argv[1], &srv.sin_addr) != 1 ||
        connect(sock, (struct sockaddr*)&srv, sizeof srv) != 0)
    { perror("connect"); return 1; }

    set_nonblocking(sock);
    set_nonblocking(STDIN_FILENO);

    printf("Connected to %s:%s   (Ctrl-C to quit)\n", argv[1], argv[2]);

    char sbuf[BUF] = {0};   /* socket - stdout */
    char kbuf[BUF] = {0};   /* stdin - socket */
    size_t klen = 0;

    /* --- main loop --- */
    while (1)
    {
        fd_set r;  FD_ZERO(&r);
        FD_SET(sock, &r);
        FD_SET(STDIN_FILENO, &r);
        int maxfd = (sock > STDIN_FILENO ? sock : STDIN_FILENO);

        if (select(maxfd + 1, &r, NULL, NULL, NULL) < 0)
        {
            if (errno == EINTR) continue;
            perror("select"); break;
        }

        /* --- data from server */
        if (FD_ISSET(sock, &r))
        {
            ssize_t n = read(sock, sbuf, sizeof sbuf - 1);
            if (n <= 0) { puts("\n[disconnected]"); break; }
            sbuf[n] = '\0';
            printf("%s", sbuf);
            fflush(stdout);
        }

        /* --- data from keyboard */
        if (FD_ISSET(STDIN_FILENO, &r))
        {
            char ch;
            ssize_t n = read(STDIN_FILENO, &ch, 1);
            if (n == 1) {
                if (ch == '\n')
                {
                    kbuf[klen++] = '\n';
                    write(sock, kbuf, klen);
                    klen = 0;
                    memset(kbuf, 0, sizeof kbuf);
                }

                else if (klen < BUF-2)
                {
                    kbuf[klen++] = ch;
                }
            }
        }
    }

    close(sock);
    return 0;
}
