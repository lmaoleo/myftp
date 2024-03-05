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

static struct sockaddr_in make_servaddr()
{
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    return servaddr;
}

static void bind_socket(int sockdf, struct sockaddr_in servaddr)
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
}

ftp_server *create_server()
{
    ftp_server *server = malloc(sizeof(ftp_server));

    server->sockfd = make_sockfd();
    server->servaddr = make_servaddr();
    server->clients = NULL;
    bind_socket(server->sockfd, server->servaddr);
    return server;
}