/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** client_free
*/

#include "client.h"

void free_client(ftp_client_node_t *client)
{
    free(client->username);
    free(client);
}
