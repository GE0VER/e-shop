#include "common.h"

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ORDERS_PER_CLIENT; i++) {
        int product_id = rand() % NUM_PRODUCTS;
        write(sock, &product_id, sizeof(product_id));

        char response[100];
        read(sock, response, sizeof(response));
        printf("Response: %s\n", response);

        sleep(1); // Αναμονή μεταξύ παραγγελιών
    }

    close(sock);
    return 0;
}
