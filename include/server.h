/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/select.h>

    #include "client.h"

typedef struct ftp_server_s {
    int sockfd;
    struct sockaddr_in servaddr;
    ftp_client_node_t *clients;
    fd_set *readfds;
    int max_sd;
} ftp_server_t;

ftp_server_t *create_server(void);
void setup_readfds(ftp_server_t *server);
void free_server(ftp_server_t *server);

int server_clients_loop(ftp_server_t *server,
    ftp_client_node_t *new_client, char *buff);

#endif /* !SERVER_H_ */
