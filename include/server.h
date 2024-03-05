/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <netinet/in.h>

#include "client.h"

typedef struct ftp_server_s {
    int sockfd;
    struct sockaddr_in servaddr;
    ftp_client_node *clients;
} ftp_server;

ftp_server *create_server();

#endif /* !SERVER_H_ */
