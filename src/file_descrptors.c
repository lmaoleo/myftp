/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** file_descrptors
*/

#include "server.h"

void setup_readfds(ftp_server_t *server)
{
    fd_set *readfds = malloc(sizeof(fd_set));
    int max_sock = 0;
    int fd = 0;

    FD_ZERO(readfds);
    FD_SET(server->sockfd, readfds);
    max_sock = server->sockfd;
    for (ftp_client_node_t *tmp = server->clients; tmp; tmp = tmp->next) {
        fd = tmp->connfd;
        FD_SET(fd, readfds);
        if (fd > max_sock)
            max_sock = fd;
    }
    server->readfds = readfds;
    server->max_sd = max_sock;
}
