// raw_socket.c
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    printf("Raw socket created. (ICMP type)\n");
    close(sockfd);
    return 0;
}

