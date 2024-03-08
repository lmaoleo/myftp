/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** com_utils
*/

#include <strings.h>

#include "utils.h"

int ftp_send_buff(int fd, char *buff, char *msg)
{
    if (buff == NULL)
        return -1;
    bzero(buff, 4 + strlen(msg) + 2);
    sprintf(buff, "%s%s", msg, CRLF);
    return write(fd, buff, strlen(buff));
}

int ftp_send(int fd, char *msg)
{
    char buff[1024];

    return ftp_send_buff(fd, buff, msg);
}

char *ftp_receive(int fd, char *buff)
{
    int ret = 0;

    if (buff == NULL)
        return NULL;
    bzero(buff, 1024);
    ret = read(fd, buff, 1024);
    if (ret <= 0) {
        free(buff);
        return NULL;
    }
    return buff;
}
