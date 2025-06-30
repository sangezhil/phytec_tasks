#include <stdio.h>
#define SIZE 5

int buffer[SIZE];
int head = 0, tail = 0, count = 0;

void enqueue(int value) {
    if (count == SIZE) {
        printf("Buffer full, overwriting %d\n", buffer[head]);
        head = (head + 1) % SIZE;
    } else {
        count++;
    }
    buffer[tail] = value;
    tail = (tail + 1) % SIZE;
}

void dequeue() {
    if (count == 0) {
        printf("Buffer empty\n");
        return;
    }
    printf("Removed: %d\n", buffer[head]);
    head = (head + 1) % SIZE;
    count--;
}

void display() {
    if (count == 0) {
        printf("Buffer is empty\n");
        return;
    }
    int i = head;
    for (int j = 0; j < count; j++) {
        printf("%d ", buffer[i]);
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    enqueue(1);
    enqueue(2);
    display();
    dequeue();
    display();
    return 0;
}

