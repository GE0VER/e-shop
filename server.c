#include "common.h"

struct Product catalog[NUM_PRODUCTS];

void initialize_catalog() {
    for (int i = 0; i < NUM_PRODUCTS; i++) {
        sprintf(catalog[i].description, "Product %d", i + 1);
        catalog[i].price = 10.0 * (i + 1);
        catalog[i].item_count = 2;
    }
}

void handle_client(int client_socket) {
    int product_id;
    char response[100];

    for (int i = 0; i < ORDERS_PER_CLIENT; i++) {
        read(client_socket, &product_id, sizeof(product_id));

        if (catalog[product_id].item_count > 0) {
            catalog[product_id].item_count--;
            sprintf(response, "Order successful: %s", catalog[product_id].description);
        } else {
            sprintf(response, "Order failed: %s out of stock!", catalog[product_id].description);
        }

        write(client_socket, response, sizeof(response));
        sleep(1); // Χρόνος διεκπεραίωσης
    }

    close(client_socket);
}

int main() {
    initialize_catalog();

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    for (int i = 0; i < MAX_CLIENTS; i++) {
        int client_socket = accept(server_fd, NULL, NULL);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client %d connected\n", i + 1);
        handle_client(client_socket);
    }

    close(server_fd);
    return 0;
}
