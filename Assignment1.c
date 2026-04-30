#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * واجب (1) - لغة سي - CE-ESY26
 * تنفيذ المخزن الدائري (Circular Buffer)
 * الطالبة: رهام زيدان الكيصوم
 * الرقم الجامعي: 240129
 */

#define SIZE 15 

typedef struct {
    char buffer[SIZE];
    int head;  
    int tail;  
    int count; 
} CircularBuffer;

void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

bool isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

void write(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\n[Error] Buffer Overflow! Cannot write: %c\n", data);
        return;
    }
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % SIZE;
    cb->count++;
}

char read(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\n[Error] Buffer Underflow!\n");
        return '\0';
    }
    char data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count--;
    return data;
}

int main() {
    CircularBuffer cb;
    char name[100];
    const char *suffix = "CE-ESY";

    init(&cb);

    printf("Enter your name: ");
    if (fgets(name, sizeof(name), stdin)) {
        name[strcspn(name, "\n")] = 0; 
    }

    strcat(name, suffix);
    printf("Processed String: %s\n", name);

    printf("Writing to buffer...\n");
    for (int i = 0; name[i] != '\0'; i++) {
        write(&cb, name[i]);
    }

    printf("Reading from buffer: ");
    while (!isEmpty(&cb)) {
        printf("%c", read(&cb));
    }
    printf("\n");

    if (isEmpty(&cb)) {
        printf("Buffer is now empty. Operation successful.\n");
    }

    return 0;
}
