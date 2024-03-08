/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** normal_commands
*/

#include "commands.h"

int quit_cmd(ftp_client_node_t *client, regex_result_t *res)
{
    (void)res;
    ftp_send(client->connfd, SERVICE_CLOSING);
    return 1;
}
