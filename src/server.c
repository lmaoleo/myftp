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
#include <arpa/inet.h>

#include "myftp.h"
#include "server.h"

static int make_sockfd(void)
{
    int sockdf;

    sockdf = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockdf, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    if (sockdf == -1) {
        printf("Socket creation failed...\n");
        return 84;
    } else
        printf("Socket successfully created..\n");
    return sockdf;
}

static void make_servaddr(ftp_server_t *server, int port)
{
    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);
    printf("Port: %d\n", ntohs(servaddr.sin_port));
    server->servaddr = servaddr;
}

static int bind_socket(int sockdf, struct sockaddr_in *servaddr)
{
    if ((bind(sockdf, (struct sockaddr *)servaddr, sizeof(*servaddr))) != 0) {
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

ftp_server_t *create_server(int port, char *path)
{
    ftp_server_t *server = malloc(sizeof(ftp_server_t));

    printf("Port: %d\n", port);
    if (port < 1024 || port > 65535)
        return NULL;
    if (server == NULL)
        return NULL;
    server->sockfd = make_sockfd();
    make_servaddr(server, port);
    server->clients = NULL;
    if (bind_socket(server->sockfd, &server->servaddr) == 84)
        return NULL;
    server->anonymous_path = strdup(path);
    return server;
}

void free_server(ftp_server_t *server)
{
    close(server->sockfd);
    remove_all_clients(&server->clients);
    free(server->readfds);
    free(server->anonymous_path);
    free(server);
}
