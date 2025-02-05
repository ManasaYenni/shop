#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
void stop_and_wait_sender(char frames[], int n) {
    printf("Sender started...\n");
    for (int i = 0; i < n; i++) {
        printf("Sending frame: %c\n", frames[i]);
        sleep(1); 
        int ack = rand() % 10;  
        if (ack < 8) {
            printf("Acknowledgment received for frame: %c\n", frames[i]);
        } else {
            printf("Acknowledgment lost for frame: %c. Retransmitting...\n", frames[i]);
            sleep(1); 
            printf("Frame %c retransmitted\n", frames[i]);
            printf("Acknowledgment received for frame: %c\n", frames[i]);
        }
        sleep(1);  
    }
    printf("All frames sent successfully.\n");
}
int main() {
    srand(time(0));  
    char frames[] = {'A', 'B', 'C', 'D'};  
    int n = sizeof(frames) / sizeof(frames[0]);
    stop_and_wait_sender(frames, n);
    return 0;
}
