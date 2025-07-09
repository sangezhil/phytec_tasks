#include <stdint.h>
#include <stdio.h>

#define BUFFER_SIZE 128  // Power of 2 is efficient

typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} CircularBuffer;

// === Initialization ===
void CircularBuffer_Init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
}

// === Check if Buffer is Empty ===
int CircularBuffer_IsEmpty(CircularBuffer *cb) {
    return cb->head == cb->tail;
}

// === Check if Buffer is Full ===
int CircularBuffer_IsFull(CircularBuffer *cb) {
queue    return ((cb->head + 1) % BUFFER_SIZE) == cb->tail;
}

// === Add Data to Buffer ===
int CircularBuffer_Put(CircularBuffer *cb, uint8_t data) {
    if (CircularBuffer_IsFull(cb)) {
        return -1;  // Buffer is full
    }
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    return 0;
}

// === Get Data from Buffer ===
int CircularBuffer_Get(CircularBuffer *cb, uint8_t *data) {
    if (CircularBuffer_IsEmpty(cb)) {
        return -1;  // Buffer is empty
    }
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    return 0;
}

// === Example Usage ===
int main(void) {
    CircularBuffer uartBuffer;
    CircularBuffer_Init(&uartBuffer);

    // Simulate receiving data (like from UART)
    CircularBuffer_Put(&uartBuffer, 'H');
    CircularBuffer_Put(&uartBuffer, 'i');
    CircularBuffer_Put(&uartBuffer, '!');

    // Simulate processing data
    uint8_t byte;
    while (CircularBuffer_Get(&uartBuffer, &byte) == 0) {
        printf("Got byte: %c\n", byte);
    }

    return 0;
}
