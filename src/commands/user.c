/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** user
*/

#include "server.h"
#include "client.h"
#include "utils.h"
#include "user.h"

const user_t avaliable_users[] = {
    {"Anonymous", ""},
    {NULL, NULL}
};

int user_cmd(ftp_client_node_t *client, regex_result_t *res)
{
    char *username = get_arg(res, 1);

    if (username == NULL) {
        ftp_send(client->connfd, INVALID_CREDENTIALS);
        return 1;
    }
    for (int i = 0; avaliable_users[i].username != NULL; i++) {
        if (strcmp(avaliable_users[i].username, username) == 0) {
            client->username = strdup(username);
            ftp_send(client->connfd, USERNAME_OK);
            return 0;
        }
    }
    ftp_send(client->connfd, INVALID_CREDENTIALS);
    return 0;
}

int pass_cmd(ftp_client_node_t *client, regex_result_t *res)
{
    char *password = get_arg(res, 1);

    if (client->username == NULL) {
        ftp_send(client->connfd, NEED_ACCOUNT);
        return 1;
    }
    password = (password == NULL) ? strdup("") : password;
    for (int i = 0; avaliable_users[i].username != NULL; i++) {
        if (strcmp(avaliable_users[i].username, client->username) != 0)
            continue;
        if (strcmp(avaliable_users[i].password, password) == 0) {
            client->is_logged = true;
            ftp_send(client->connfd, LOGIN_SUCESS);
            free(password);
            return 0;
        }
    }
    ftp_send(client->connfd, INVALID_CREDENTIALS);
    free(password);
    return 0;
}
