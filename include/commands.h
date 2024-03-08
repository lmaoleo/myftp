/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** commands
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #include "myftp.h"
    #include "client.h"
    #include "server.h"
    #include "utils.h"

int quit_cmd(ftp_client_node_t *client, regex_result_t *res);
int cwd_cmd(ftp_client_node_t *client, regex_result_t *res);

#endif /* !COMMANDS_H_ */
