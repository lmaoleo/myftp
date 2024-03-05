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

ftp_client_node *init_client(int sockfd, struct sockaddr_in *cli)
{
    ftp_client_node *client = malloc(sizeof(ftp_client_node));

    client->connfd = sockfd;
    client->cli = *cli;
    client->next = NULL;
    return client;
}

void add_client(ftp_client_node **head, int sockfd, struct sockaddr_in *cli)
{
    ftp_client_node *new_client = init_client(sockfd, cli);
    ftp_client_node *last = *head;

    if (*head == NULL) {
        *head = new_client;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_client;
}

void remove_client(ftp_client_node **head, int sockfd)
{
    ftp_client_node *temp = *head;
    ftp_client_node *prev = NULL;

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
    free(temp);
}
