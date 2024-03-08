/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** user
*/

#ifndef USER_H_
    #define USER_H_

    #include "client.h"
    #include "server.h"
    #include "utils.h"

typedef struct user_s {
    char *username;
    char *password;
    char *home;
} user_t;

int user_cmd(ftp_client_node_t *client, regex_result_t *res);
int pass_cmd(ftp_client_node_t *client, regex_result_t *res);

#endif /* !USER_H_ */
