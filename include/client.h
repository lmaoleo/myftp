/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** client
*/

#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef CLIENT_H_
#define CLIENT_H_

typedef struct ftp_client_node_s {
    int connfd;
    struct sockaddr_in cli;
    struct ftp_client_node_s *next;
} ftp_client_node;

ftp_client_node *init_client(int sockfd, struct sockaddr_in cli);
void add_client(ftp_client_node **head, int sockfd, struct sockaddr_in cli);
void remove_client(ftp_client_node **head, int sockfd);

#endif /* !CLIENT_H_ */
