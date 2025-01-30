#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define NUM_PRODUCTS 20
#define MAX_CLIENTS 5
#define ORDERS_PER_CLIENT 10

struct Product {
    char description[50];
    float price;
    int item_count;
};

extern struct Product catalog[NUM_PRODUCTS];

void initialize_catalog();

#endif // COMMON_H
