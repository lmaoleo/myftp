/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>

#include "myftp.h"
#include "client.h"
#include "server.h"

int run_ftp_server(int connfd)
{
    char buff[1024];
    char to_send[] = "Hello World !\n";
    int n;

    bzero(buff, 1024);
    write(connfd, to_send, strlen(to_send));
}

int new_connection(ftp_client_node **head_client, int sockdf, struct sockaddr_in servaddr)
{
    int connfd;
    int len;
    struct sockaddr_in cli;

    len = sizeof(cli);
    connfd = accept(sockdf, (struct sockaddr *)&cli, &len);
    if (connfd < 0) {
        printf("Server acccept failed...\n");
        return 84;
    } else
        printf("Server acccept the client...\n");
    add_client(head_client, connfd, cli);
    return connfd;
}

int main(int ac, char **av)
{
    ftp_server *server = create_server();
    while (true) {
        new_connection(&server->clients, server->sockfd, server->servaddr);
    }
    close(server->sockfd);
    return 0;
}