/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include "regex_util.h"
    #include "server.h"
    #include "client.h"

    #define CRLF "\r\n"

    #define COMMAND_OK "200 Command okay."
    #define CONNECTED "220 Service ready for new user."
    #define SERVICE_CLOSING_1 " control connection. Logged out if appropriate."
    #define SERVICE_CLOSING "221 Service closing" SERVICE_CLOSING_1
    #define HELP_1 "On how to use the server or the meaning of a particular\n"
    #define HELP_2 "non-standard command.  "
    #define HELP_3 "This reply is useful only to the human user."
    #define HELP "214 Help message.\n" HELP_1 HELP_2 HELP_3
    #define PATH_CREATED "257 %s created."
    #define LOGIN_SUCESS "230 User logged in, proceed."
    #define FILE_ACTION_OK "250 Requested file action okay, completed."
    #define USERNAME_OK "331 User name okay, need password."
    #define NEED_ACCOUNT "332 Need account for login."

    #define INVALID_CREDENTIALS "430 Invalid username or password."
    #define FILE_ACTION_NOT_OK "450 Requested file action not taken."
    #define COMMAND_NOT_IMPLEMENTED "502 Command not implemented."
    #define NOT_LOGGED "530 Not logged in."


typedef struct regex_cmd_s {
    char *regex;
    int (*func)(ftp_client_node_t *client, regex_result_t *res);
} regex_cmd_t;

int exec_cmd(ftp_client_node_t *client, char *cmd);
char *get_arg(regex_result_t *res, int i);

int ftp_send(int fd, char *buff, char *msg, ...);
char *ftp_receive(int fd, char *buff);

#endif /* !UTILS_H_ */
