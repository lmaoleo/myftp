/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** commands
*/

#include "commands.h"
#include "utils.h"
#include "user.h"

const regex_cmd_t reg_cmds[] = {
    {"USER (\\w+)", &user_cmd},
    {"PASS ([!-~]*)", &pass_cmd},
    {"QUIT", &quit_cmd},
    {"CWD ([!-~]+)", &cwd_cmd},
    {"PWD", &pwd_cmd},
    {NULL, NULL}
};

int exec_cmd(ftp_client_node_t *client, char *cmd)
{
    regex_result_t *regex = NULL;
    int ret = 0;

    for (int i = 0; reg_cmds[i].regex != NULL; i++) {
        regex = execute_regex(reg_cmds[i].regex, cmd);
        if (regex != NULL) {
            ret = reg_cmds[i].func(client, regex);
            return ret;
        }
    }
    ftp_send(client->connfd, NULL, COMMAND_NOT_IMPLEMENTED);
    return -1;
}

char *get_arg(regex_result_t *res, int i)
{
    char *arg = NULL;

    if (res->match[i].rm_so == -1)
        return NULL;
    arg = strndup(res->str + res->match[i].rm_so,
    res->match[i].rm_eo - res->match[i].rm_so);
    return arg;
}
