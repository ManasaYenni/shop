#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FLAG 0x7E
#define I_FRAME 0x00
#define S_FRAME 0x01
#define U_FRAME 0x02
size_t i;
typedef struct {
    unsigned char frame_type;
    unsigned char address;
    unsigned char control;
    unsigned char *data;
    unsigned char fcs;
} HDLCFrame;
unsigned char calculate_fcs(unsigned char address, unsigned char control, unsigned char *data, size_t data_len) {
    unsigned int total_sum = address + control;
    for ( i = 0; i < data_len; i++) {
        total_sum += data[i];
    }
    return total_sum % 256;
}
void create_frame(HDLCFrame *frame, unsigned char frame_type, unsigned char address, unsigned char control, unsigned char *data, size_t data_len) {
    frame->frame_type = frame_type;
    frame->address = address;
    frame->control = control;
    frame->data = data;
    frame->fcs = calculate_fcs(address, control, data, data_len);
}
void transmit(unsigned char *byte_data, size_t len) {
    printf("Transmitting: ");
    for ( i = 0; i < len; i++) {
        printf("%02X ", byte_data[i]);
    }
    printf("\n");
}
void send_frame(unsigned char frame_type, unsigned char address, unsigned char control, unsigned char *data, size_t data_len) {
    HDLCFrame frame;
    create_frame(&frame, frame_type, address, control, data, data_len);
    size_t frame_size = 3 + data_len + 2; // FLAG + ADDRESS + CONTROL + DATA + FCS + FLAG
    unsigned char *byte_data = (unsigned char *)malloc(frame_size);
    byte_data[0] = FLAG;
    byte_data[1] = frame.address;
    byte_data[2] = frame.control;
    memcpy(&byte_data[3], frame.data, data_len);
    byte_data[3 + data_len] = frame.fcs;
    byte_data[4 + data_len] = FLAG;
    transmit(byte_data, frame_size);
    free(byte_data);
}
int main() {
    while (1) {
        printf("HDLC Frame Creator\n");
        printf("1. Create I-Frame\n");
        printf("2. Create S-Frame\n");
        printf("3. Create U-Frame\n");
        printf("4. Exit\n");
        int option;
        printf("Choose an option: ");
        scanf("%d", &option);
        if (option == 4) {
            break;
        }
        unsigned int address, control;
        printf("Enter address (in hex, e.g., 0x01): ");
        scanf("%x", &address);
        printf("Enter control (in hex, e.g., 0x03): ");
        scanf("%x", &control);
        if (option == 1) {
            char data_input[256];
            printf("Enter data (comma-separated hex values, e.g., 0x01,0x02,0x03): ");
            scanf("%s", data_input);
            unsigned char data[256];
            size_t data_len = 0;
            char *token = strtok(data_input, ",");
            while (token != NULL) {
                data[data_len++] = (unsigned char)strtol(token, NULL, 16);
                token = strtok(NULL, ",");
            }
            send_frame(I_FRAME, (unsigned char)address, (unsigned char)control, data, data_len);
        } else if (option == 2) {
            send_frame(S_FRAME, (unsigned char)address, (unsigned char)control, NULL, 0);
        } else if (option == 3) {
            send_frame(U_FRAME, (unsigned char)address, (unsigned char)control, NULL, 0);
        }
    }
    return 0;
}
