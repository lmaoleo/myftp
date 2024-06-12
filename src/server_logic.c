/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** server_logic
*/

#include "server.h"
#include "utils.h"
#include "commands.h"
#include "user.h"

#include <netinet/in.h>
#include <arpa/inet.h>

static ftp_client_node_t *new_connection(ftp_client_node_t **head_client,
    int sockdf, server_t *server)
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
        printf("Connection from %s:%d\n", inet_ntoa(cli.sin_addr),
        ntohs(cli.sin_port));
    add_client(head_client, connfd, &cli, server);
    new_client = get_client(*head_client, connfd);
    return new_client;
}

static void action_on_client(ftp_server_t *server,
    ftp_client_node_t *client, char *buff)
{
    int ret = run_ftp_server(client, buff);

    if (ret == 0)
        remove_client(&server->clients, client->connfd);
}

int server_clients_loop(ftp_server_t *server,
    ftp_client_node_t *new_client, char *buff)
{
    if (FD_ISSET(server->sockfd, server->readfds)) {
        new_client = new_connection(&server->clients, server->sockfd, server);
        if (new_client == NULL)
            return 84;
        ftp_send(new_client->connfd, buff, CONNECTED);
    }
    for (ftp_client_node_t *client = server->clients; client != NULL;
    client = client->next) {
        if (FD_ISSET(client->connfd, server->readfds)) {
            action_on_client(server, client, buff);
        }
    }
    return 0;
}
