/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <netinet/in.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdbool.h>

typedef struct ftp_server_s server_t;

typedef struct ftp_client_node_s {
    server_t *conn_server;
    int connfd;
    struct sockaddr_in cli;
    char *username;
    bool is_logged;
    char *cwd;
    struct ftp_client_node_s *next;
} ftp_client_node_t;

ftp_client_node_t *init_client(int sockfd, struct sockaddr_in *cli,
server_t *server);
void add_client(ftp_client_node_t **head, int sockfd,
struct sockaddr_in *cli, server_t *server);
void remove_client(ftp_client_node_t **head, int sockfd);
void remove_all_clients(ftp_client_node_t **head);
void free_client(ftp_client_node_t *client);
ftp_client_node_t *get_client(ftp_client_node_t *head, int sockfd);

#endif /* !CLIENT_H_ */
