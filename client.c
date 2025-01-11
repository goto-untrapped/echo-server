#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE] = {0};

    // ソケットを作成する
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // サーバアドレスを設定する
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // サーバアドレス設定とIPアドレスを紐づける
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    // サーバに接続する
    if (connect(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server.\n");

    // メッセージが送受信できる
    while (1) {
        printf("Enter message: ");
        fgets(message, BUFFER_SIZE, stdin);

        // サーバに送信する
        send(server_fd, message, strlen(message), 0);

        // サーバから受信する
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = read(sock, buffer, BUFFER_SIZE);
        if (bytes_received <= 0) {
            printf("Server disconnected.\n");
            break;
        }
        printf("Echo from server: %s", buffer);
    }

    close(server_fd);
    return 0;
}
