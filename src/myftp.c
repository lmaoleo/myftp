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

static void show_if_help(char *arg)
{
    if (arg == NULL)
        return;
    if (strcmp(arg, "-help") != 0)
        return;
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory ");
    printf("for the Anonymous user\n");
    exit(0);
}

int run_ftp_server(ftp_client_node_t *client, char *buff)
{
    int ret = 0;

    bzero(buff, 1024);
    ftp_receive(client->connfd, buff);
    printf("Received: %s", buff);
    ret = exec_cmd(client, buff);
    if (ret == 1) {
        return 0;
    }
    if (ret == 0) {
        printf("Client %d requested to quit\n", client->connfd);
        return 1;
    }
    return -1;
}

int server_loop(ftp_server_t *server)
{
    char buff[1024];
    int ret = 0;
    ftp_client_node_t *new_client = NULL;

    setup_fds(server);
    if (select(server->max_sd + 1, server->readfds,
    NULL, NULL, NULL) < 0) {
        printf("Select failed...\n");
        return 84;
    }
    ret = server_clients_loop(server, new_client, buff);
    if (ret < 0)
        return ret;
    return -1;
}

int main(int ac, char **av)
{
    ftp_server_t *server = NULL;
    int ret = 0;
    int port = 0;
    char path;

    show_if_help(av[1]);
    if (ac != 3)
        return 84;
    port = atoi(av[1]);
    strcpy(&path, av[2]);
    server = create_server(port, &path);
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
