#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <zmq.h>

int main()
{
    /* Define variables */

    char address[1024];

    char ip[1024];
    char port[1024];

    /* Get server IP and port */

    printf("Enter server IP: ");
    scanf("%1023s", ip);

    printf("Enter server port: ");
    scanf("%1023s", port);

    /* Connect to server */

    strcat(address, "tcp://");
    strcat(address, ip);
    strcat(address, ":");
    strcat(address, port);
    strcat(address, "\0");

    printf("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect(requester, address);

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char buffer [10];
        printf ("Sending Hello %d…\n", request_nbr);
        zmq_send (requester, "Hello", 5, 0);
        zmq_recv (requester, buffer, 10, 0);
        printf ("Received World %d\n", request_nbr);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}
