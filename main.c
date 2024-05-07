#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

char *html = "HTTP/1.1 200 OK\r\n"
              "Content-Type: text/html; charset=UTF-8\r\n\r\n"
              "<!DOCTYPE html>\r\n"
              "<html><head><title>Luiza</title></head>\r\n"
              "<body><h1>Para: Luiza</h1></body></html>\r\n"
              "<p>Te amo!!!</p>\r\n";

int main(void) {
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Criando socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Falha na criação do socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("Falha no bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0) {
        perror("Falha no listen");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("\nAguardando conexões...\n");

        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("Falha no accept");
            exit(EXIT_FAILURE);
        }

        write(new_socket , html , strlen(html));
        printf("Página HTML enviada para o cliente\n");
        close(new_socket);
    }

    return 0;
}