#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 5

struct CircularBuffer {
    char buffer[SIZE];
    int head;
    int tail;
    int count;
};

void init(struct CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

bool isFull(struct CircularBuffer *cb) {
    return cb->count == SIZE;
}

bool isEmpty(struct CircularBuffer *cb) {
    return cb->count == 0;
}

void write(struct CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("Buffer Overflow\n");
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count++;
}

char read(struct CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer Underflow\n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;
    return data;
}

int main() {
    struct CircularBuffer cb;
    init(&cb);

    char name[100];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    strcat(name, "CE-ESY");

    for (int i = 0; i < strlen(name); i++) {
        write(&cb, name[i]);
    }

    printf("Data from Buffer: ");
    while (!isEmpty(&cb)) {
        char c = read(&cb);
        if (c != '\0')
            printf("%c", c);
    }
    printf("\n");

    return 0;
}
