/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** com_utils
*/

#include "utils.h"

#include <strings.h>
#include <stdarg.h>

int ftp_send(int fd, char *buff, char *msg, ...)
{
    va_list args;
    char other_buff[1024];
    char new_msg[1024];

    va_start(args, msg);
    if (buff == NULL)
        buff = other_buff;
    bzero(buff, 4 + strlen(msg) + 2);
    vsprintf(new_msg, msg, args);
    sprintf(buff, "%s%s", new_msg, CRLF);
    return write(fd, buff, strlen(buff));
}

char *ftp_receive(int fd, char *buff)
{
    int ret = 0;

    if (buff == NULL)
        return NULL;
    bzero(buff, 1024);
    if (fd == -1)
        return NULL;
    ret = read(fd, buff, 1024);
    if (ret <= 0) {
        return NULL;
    }
    return buff;
}
