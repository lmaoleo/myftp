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
