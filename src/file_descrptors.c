/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** file_descrptors
*/

#include "server.h"

void setup_fds(ftp_server_t *server)
{
    fd_set *readfds = malloc(sizeof(fd_set));
    int max_sock = 0;
    ftp_client_node_t *tmp = server->clients;

    FD_ZERO(readfds);
    FD_SET(server->sockfd, readfds);
    max_sock = server->sockfd;
    while (tmp != NULL) {
        FD_SET(tmp->connfd, readfds);
        if (tmp->connfd > max_sock)
            max_sock = tmp->connfd;
        tmp = tmp->next;
    }
    server->readfds = readfds;
    server->max_sd = max_sock;
}
