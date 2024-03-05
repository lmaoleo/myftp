/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

#include "myftp.h"
#include "server.h"

static int make_sockfd()
{
    int sockdf;

    sockdf = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(sockdf, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    if (sockdf == -1) {
        printf("Socket creation failed...\n");
        return 84;
    } else
        printf("Socket successfully created..\n");
    return sockdf;
}

static void make_servaddr(ftp_server *server)
{
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    server->servaddr = servaddr;
}

static int bind_socket(int sockdf, struct sockaddr_in servaddr)
{
    if ((bind(sockdf, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed...\n");
        return 84;
    } else
        printf("Socket successfully binded..\n");

    if ((listen(sockdf, 0)) != 0) {
        printf("Listen failed...\n");
        return 84;
    } else
        printf("Server listening..\n");
    return 0;
}

void setup_readfds(ftp_server *server)
{
    fd_set *readfds = malloc(sizeof(fd_set));
    int max_sock = 0;
    int fd = 0;

    FD_ZERO(readfds);
    FD_SET(server->sockfd, readfds);
    max_sock = server->sockfd;
    for (ftp_client_node *tmp = server->clients; tmp; tmp = tmp->next) {
        fd = tmp->connfd;
        FD_SET(fd, readfds);
        if (fd > max_sock)
            max_sock = fd;
    }
    server->readfds = readfds;
    server->max_sd = max_sock;
}

ftp_server *create_server()
{
    ftp_server *server = malloc(sizeof(ftp_server));

    server->sockfd = make_sockfd();
    make_servaddr(server);
    server->clients = NULL;
    if (bind_socket(server->sockfd, server->servaddr) == 84)
        return NULL;
    return server;
}