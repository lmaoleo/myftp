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
    ftp_send(client->connfd, NULL, SERVICE_CLOSING);
    return 1;
}

int cwd_cmd(ftp_client_node_t *client, regex_result_t *res)
{
    char *path = get_arg(res, 1);

    if (client->is_logged == false) {
        ftp_send(client->connfd, NULL, NOT_LOGGED);
        return 0;
    }
    if (path == NULL) {
        ftp_send(client->connfd, NULL, FILE_ACTION_NOT_OK);
        return 0;
    }
    if (chdir(path) == -1) {
        ftp_send(client->connfd, NULL, FILE_ACTION_NOT_OK);
        return 0;
    }
    free(client->cwd);
    client->cwd = path;
    ftp_send(client->connfd, NULL, FILE_ACTION_OK);
    return 0;
}
