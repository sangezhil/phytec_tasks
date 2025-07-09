#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server = {AF_INET, htons(8080), INADDR_ANY};

    bind(server_fd, (struct sockaddr*)&server, sizeof(server));
    listen(server_fd, 1);

    int client_fd = accept(server_fd, NULL, NULL);
    char buffer[100];
    read(client_fd, buffer, sizeof(buffer));
    printf("Client says: %s\n", buffer);
    write(client_fd, "Hello from TCP server!", 23);

    close(client_fd);
    close(server_fd);
    return 0;
}

