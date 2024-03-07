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
#include <strings.h>
#include <stdbool.h>

#include "myftp.h"
#include "client.h"
#include "server.h"
#include "utils.h"

int run_ftp_server(ftp_client_node_t *client, char *buff)
{
    int ret = 0;

    bzero(buff, 1024);
    ftp_receive(client->connfd, buff);
    ret = exec_cmd(client, buff);
    if (ret == 1)
        return 0;
    return -1;
}

ftp_client_node_t *new_connection(ftp_client_node_t **head_client, int sockdf)
{
    int connfd = 0;
    socklen_t len;
    struct sockaddr_in cli;
    ftp_client_node_t *new_client = NULL;

    len = sizeof(cli);
    connfd = accept(sockdf, (struct sockaddr *)&cli, &len);
    if (connfd < 0) {
        printf("Server acccept failed...\n");
        return NULL;
    } else
        printf("Server acccept the client...\n");
    add_client(head_client, connfd, &cli);
    new_client = get_client(*head_client, connfd);
    return new_client;
}

int server_loop(ftp_server_t *server)
{
    char buff[1024];
    int ret = 0;
    ftp_client_node_t *new_client = NULL;

    setup_readfds(server);
    if (select(server->max_sd + 1, server->readfds,
    NULL, NULL, NULL) < 0) {
        printf("Select failed...\n");
        return 84;
    }
    ret = server_client_loop(server, new_client, buff);
    if (ret >= 0)
        return ret;
    return -1;
}

int main(int ac, char **av)
{
    ftp_server_t *server = create_server();
    int ret = 0;
    int port;

    if (server == NULL)
        return 84;
    while (true) {
        ret = server_loop(server);
        if (ret >= 0)
            break;
    }
    free_server(server);
    return ret;
}
