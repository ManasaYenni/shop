#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
bool receiver(int packet) {
    if (rand() % 10 > 2) { 
        printf("Receiver: Packet %d received successfully\n", packet);
        return true;
    } else {
        printf("Receiver: Packet %d lost\n", packet);
        return false;
    }
}
void sender(int total_packets) {
    int window_size, next_packet = 0;
    printf("Enter the window size: ");
    scanf("%d", &window_size);
    while (next_packet < total_packets) 
	{
        int window_end = (next_packet + window_size < total_packets)? next_packet + window_size: total_packets;
        printf("\nCurrent window: ");
        for (int i = next_packet; i < window_end; i++) {
            printf("%d ", i);
        }
        printf("\n");
        for (int i = 0; i < window_size; i++) {
            if (next_packet < total_packets) {
                printf("Sender: Sending packet %d\n", next_packet);
                if (receiver(next_packet)) {
                    printf("Sender: Acknowledgment received for packet %d\n", next_packet);
                    next_packet++;
                } else {
                    printf("Sender: Packet %d failed, retransmitting window\n", next_packet);
                    break;
                }
            }
            sleep(1); 
        }
    }
}
int main() {
    srand(time(0)); 
    int total_packets;
    printf("Enter the number of packets to be transferred: ");
    scanf("%d", &total_packets);
    sender(total_packets);
    return 0;
}
