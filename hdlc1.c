#include <stdio.h>
#include <stdint.h>
#define FLAG 0x7E
#define ESCAPE 0x7D
#define XOR_MASK 0x20
#define MAX_FRAME_SIZE 256
size_t hdlc_process(const uint8_t *input, size_t input_len, uint8_t *output, int encode) {
    size_t out_idx = 0;
    int escape_next = 0;
    if (encode) {
        output[out_idx++] = FLAG; // Start flag
        for (size_t i = 0; i < input_len; i++) {
            if (input[i] == FLAG || input[i] == ESCAPE) {
                output[out_idx++] = ESCAPE;
                output[out_idx++] = input[i] ^ XOR_MASK;
            } else {
                output[out_idx++] = input[i];
            }
        }
        output[out_idx++] = FLAG; // End flag
    } else {
        for (size_t i = 1; i < input_len - 1; i++) { // Skip start and end flags
            if (escape_next) {
                output[out_idx++] = input[i] ^ XOR_MASK;
                escape_next = 0;
            } else if (input[i] == ESCAPE) {
                escape_next = 1;
            } else {
                output[out_idx++] = input[i];
                }
        }
    }
    return out_idx;
}
int main() {
    uint8_t data[] = {0x48, 0x65, 0x6C, 0x6F, 0x42}; // Example data: "HelloB"
    size_t data_len = sizeof(data) / sizeof(data[0]);
    uint8_t processed[MAX_FRAME_SIZE];
    size_t encoded_len = hdlc_process(data, data_len, processed, 1);
    printf("Encoded Data: ");
    for (size_t i = 0; i < encoded_len; i++) {
        printf("%02X ", processed[i]);
    }
    printf("\n");
    uint8_t decoded[MAX_FRAME_SIZE];
    size_t decoded_len = hdlc_process(processed, encoded_len, decoded, 0);
    printf("Decoded Data: ");
    for (size_t i = 0; i < decoded_len; i++) {
        printf("%02X ", decoded[i]);
    }
    printf("\n");
    return 0;
}
