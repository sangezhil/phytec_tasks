#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MESSAGE_MAX_LEN 32

// Define FSM states
typedef enum {
    STATE_WAIT_START,
    STATE_RECEIVING,
    STATE_PROCESSING
} State;

// Define FSM events
typedef enum {
    EVENT_NONE,
    EVENT_BYTE_RECEIVED,
    EVENT_MESSAGE_COMPLETE
} Event;

// Message buffer structure
typedef struct {
    uint8_t buffer[MESSAGE_MAX_LEN];
    uint8_t length;
} Message;

State currentState = STATE_WAIT_START;
Message currentMessage;
uint8_t byteReceived;

// Check if message is complete (ends with '\n')
int is_message_complete(const Message *msg) {
    return msg->length > 0 && msg->buffer[msg->length - 1] == '\n';
}

// Simulate message processing
void process_message(const Message *msg) {
    printf("Processing message: %.*s", msg->length, msg->buffer);
}

// Simulate sending a response
void send_response() {
    printf("Sending response: OK\n");
}

// FSM core logic
void state_machine_run(Event event) {
    switch (currentState) {
        case STATE_WAIT_START:
            if (event == EVENT_BYTE_RECEIVED) {
                currentMessage.buffer[0] = byteReceived;
                currentMessage.length = 1;
                currentState = STATE_RECEIVING;
            }
            break;

        case STATE_RECEIVING:
            if (event == EVENT_BYTE_RECEIVED) {
                if (currentMessage.length < MESSAGE_MAX_LEN) {
                    currentMessage.buffer[currentMessage.length++] = byteReceived;
                }
                if (is_message_complete(&currentMessage)) {
                    currentState = STATE_PROCESSING;
                }
            }
            break;

        case STATE_PROCESSING:
            process_message(&currentMessage);
            send_response();
            currentState = STATE_WAIT_START;
            currentMessage.length = 0;
            break;

        default:
            currentState = STATE_WAIT_START;
            currentMessage.length = 0;
            break;
    }
}

// Simulate input stream
void simulate_input(const char *input) {
    for (size_t i = 0; i < strlen(input); i++) {
        byteReceived = input[i];
        state_machine_run(EVENT_BYTE_RECEIVED);

        if (currentState == STATE_PROCESSING) {
            state_machine_run(EVENT_NONE);
        }
    }
}

// Main
int main(void) {
    simulate_input("Hello, device!\n");
    simulate_input("How are you?\n");
    return 0;
}

