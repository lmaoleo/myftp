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

    bzero(buff, 1024);
    read(connfd, buff, sizeof(buff));
    printf("From client: %s", buff);
    write(connfd, to_send, sizeof(to_send));
    printf("To client: %s", to_send);
    return 0;
}

int new_connection(ftp_client_node **head_client, int sockdf)
{
    int connfd = 0;
    socklen_t len;
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
    (void)ac;
    (void)av;
    ftp_server *server = create_server();
    int sel_ret = 0;

    while (true) {
        setup_readfds(server);
        sel_ret = select(server->max_sd + 1, server->readfds, NULL, NULL, NULL);
        if (sel_ret < 0) {
            printf("Select failed...\n");
            return 84;
        }
        if (FD_ISSET(server->sockfd, server->readfds))
            new_connection(&server->clients, server->sockfd);
        run_ftp_server(server->clients->connfd);
        remove_client(&server->clients, server->clients->connfd);
        printf("Client disconnected\n");
    }
    close(server->sockfd);
    return 0;
}