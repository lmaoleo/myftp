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

int server_clients_loop(ftp_server_t *server,
    ftp_client_node_t *new_client, char *buff)
{
    int ret = 0;

    if (FD_ISSET(server->sockfd, server->readfds)) {
        new_client = new_connection(&server->clients, server->sockfd);
        if (new_client == NULL)
            return 84;
        ftp_send_buff(new_client->connfd, buff, CONNECTED);
    }
    for (ftp_client_node_t *client = server->clients; client != NULL;
    client = client->next) {
        ret = run_ftp_server(client, buff);
        if (ret == 0)
            remove_client(&server->clients, client->connfd);
    }
    return 0;
}
