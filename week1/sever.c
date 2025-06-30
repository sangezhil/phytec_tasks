#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_CLIENTS 10
#define BUF_SIZE 1024
#define USERNAME_LEN 32
#define PORT 9090

typedef struct {
    char username[USERNAME_LEN];
    struct sockaddr_in addr;
    socklen_t addr_len;
    int active;
} Client;

typedef enum {
    EVENT_JOIN = 1,
    EVENT_LEAVE,
    EVENT_MSG
} ChatEventType;

typedef struct {
    ChatEventType type;
    char username[USERNAME_LEN];
    char message[BUF_SIZE];
} __attribute__((packed)) ChatPacket;

Client clients[MAX_CLIENTS];
int server_socket;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void broadcast(ChatPacket *pkt, struct sockaddr_in *src) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].active) {
            // Skip comparing if src is NULL (i.e., server message)
            if (src != NULL &&
                memcmp(&clients[i].addr, src, sizeof(struct sockaddr_in)) == 0) {
                continue; // Don't send back to the sender
            }

            sendto(server_socket, pkt, sizeof(ChatPacket), 0,
                   (struct sockaddr*)&clients[i].addr, clients[i].addr_len);
        }
    }
    pthread_mutex_unlock(&lock);
}


void *server_task(void *arg) {
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    ChatPacket pkt;

    while (1) {
        ssize_t recv_len = recvfrom(server_socket, &pkt, sizeof(pkt), 0,
                                    (struct sockaddr*)&client_addr, &addr_len);
        if (recv_len > 0) {
            switch (pkt.type) {
                case EVENT_JOIN:
                    pthread_mutex_lock(&lock);
                    for (int i = 0; i < MAX_CLIENTS; i++) {
                        if (!clients[i].active) {
                            clients[i].active = 1;
                            clients[i].addr = client_addr;
                            clients[i].addr_len = addr_len;
                            strncpy(clients[i].username, pkt.username, USERNAME_LEN);
                            break;
                        }
                    }
                    pthread_mutex_unlock(&lock);
                    printf("User joined: %s\n", pkt.username);
                    break;

                case EVENT_MSG:
                    printf("[%s]: %s", pkt.username, pkt.message);
                    broadcast(&pkt, &client_addr);
                    break;

                case EVENT_LEAVE:
                    pthread_mutex_lock(&lock);
                    for (int i = 0; i < MAX_CLIENTS; i++) {
                        if (clients[i].active &&
                            strcmp(clients[i].username, pkt.username) == 0) {
                            clients[i].active = 0;
                            break;
                        }
                    }
                    pthread_mutex_unlock(&lock);
                    printf("User left: %s\n", pkt.username);
                    break;
            }
        }
    }
    return NULL;
}

int main() {
    struct sockaddr_in server_addr;
    pthread_t tid;

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Socket failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    printf("UDP Chat Server started on port %d\n", PORT);
    pthread_create(&tid, NULL, server_task, NULL);

    // Server terminal input for broadcasting
    char server_input[BUF_SIZE];
    ChatPacket server_pkt;

    while (1) {
        printf("[Server]> ");
        fflush(stdout);
        if (fgets(server_input, BUF_SIZE, stdin)) {
            if (strncmp(server_input, "/exit", 5) == 0) break;

            server_pkt.type = EVENT_MSG;
            strncpy(server_pkt.username, "Server", USERNAME_LEN);
            strncpy(server_pkt.message, server_input, BUF_SIZE);
            broadcast(&server_pkt, NULL);
        }
    }

    close(server_socket);
    return 0;
}
