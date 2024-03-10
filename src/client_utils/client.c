/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myftp-leo.maurel [WSL: Fedora]
** File description:
** client
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "myftp.h"
#include "client.h"

static ftp_client_node_t *init_client(int sockfd, struct sockaddr_in *cli,
    server_t *server)
{
    ftp_client_node_t *client = malloc(sizeof(ftp_client_node_t));

    client->conn_server = server;
    client->connfd = sockfd;
    client->cli = *cli;
    client->username = NULL;
    client->is_logged = false;
    client->cwd = NULL;
    client->next = NULL;
    return client;
}

void add_client(ftp_client_node_t **head, int sockfd, struct sockaddr_in *cli,
    server_t *server)
{
    ftp_client_node_t *new_client = init_client(sockfd, cli, server);
    ftp_client_node_t *last = *head;

    if (*head == NULL) {
        *head = new_client;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_client;
}

void remove_client(ftp_client_node_t **head, int sockfd)
{
    ftp_client_node_t *temp = *head;
    ftp_client_node_t *prev = NULL;

    close(sockfd);
    if (temp != NULL && temp->connfd == sockfd) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->connfd != sockfd) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free_client(temp);
}

void remove_all_clients(ftp_client_node_t **head)
{
    ftp_client_node_t *current = *head;
    ftp_client_node_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free_client(current);
        current = next;
    }
    *head = NULL;
}

ftp_client_node_t *get_client(ftp_client_node_t *head, int sockfd)
{
    ftp_client_node_t *current = head;

    while (current != NULL) {
        if (current->connfd == sockfd)
            return current;
        current = current->next;
    }
    return NULL;
}
