#include <stdio.h>
typedef enum {
    IDLE,
    SENDING,
    WAITING_ACK,
    RECEIVING
} State;
typedef enum {
    EV_SEND_REQUEST,
    EV_MSG_ARRIVED,
    EV_ACK_RECEIVED,
    EV_TIMEOUT
} Event;
State current_state = IDLE;
void send_message() {
    printf("[Action] Sending message...\n");
}

void wait_for_ack() {
    printf("[Action] Waiting for ACK...\n");
}

void process_incoming_message() {
    printf("[Action] Processing incoming message...\n");
}

void reset_to_idle() {
    printf("[Action] Timeout occurred. Returning to IDLE...\n");
}
void handle_event(Event ev) {
    switch (current_state) {
        case IDLE:
            if (ev == EV_SEND_REQUEST) {
                send_message();
                current_state = SENDING;
            } else if (ev == EV_MSG_ARRIVED) {
                process_incoming_message();
                current_state = RECEIVING;
            }
            break;

        case SENDING:
            if (ev == EV_ACK_RECEIVED) {
                printf("[Info] ACK received. Going to IDLE.\n");
                current_state = IDLE;
            } else if (ev == EV_TIMEOUT) {
                reset_to_idle();
                current_state = IDLE;
            }
            break;

        case RECEIVING:
            if (ev == EV_ACK_RECEIVED) {
                printf("[Info] Message received and acknowledged.\n");
                current_state = IDLE;
            }
            break;

        default:
            printf("[Error] Unknown state!\n");
            break;
    }
}
void simulate_event(Event ev) {
    printf("\n[Event Triggered] ");
    switch (ev) {
        case EV_SEND_REQUEST:  printf("Send Request\n"); break;
        case EV_MSG_ARRIVED:   printf("Message Arrived\n"); break;
        case EV_ACK_RECEIVED:  printf("ACK Received\n"); break;
        case EV_TIMEOUT:       printf("Timeout\n"); break;
    }

    handle_event(ev);
}
int main() {
    simulate_event(EV_SEND_REQUEST);
    simulate_event(EV_ACK_RECEIVED);
    simulate_event(EV_MSG_ARRIVED);
    simulate_event(EV_ACK_RECEIVED);
    simulate_event(EV_SEND_REQUEST);
    simulate_event(EV_TIMEOUT);

    return 0;
}

