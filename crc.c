#include <stdio.h>
#include <string.h>
void xor(char *dividend, char *divisor, int len) {
    for (int i = 0; i < len; i++) {
        dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
    }
}
void mod2div(char *dividend, char *divisor, int dividend_len, int divisor_len) {
    int len = divisor_len;
    char tmp[divisor_len + 1];
    strncpy(tmp, dividend, divisor_len);
    tmp[divisor_len] = '\0'; 
    while (len < dividend_len) {
        if (tmp[0] == '1') {
            xor(tmp, divisor, divisor_len);
        }
        memmove(tmp, tmp + 1, divisor_len - 1);
        tmp[divisor_len - 1] = dividend[len];
        tmp[divisor_len] = '\0';
        len++;
    }
    if (tmp[0] == '1') {
        xor(tmp, divisor, divisor_len);
    }
    memcpy(dividend + (dividend_len - divisor_len + 1), tmp + 1, divisor_len - 1);
}
void encodeData(char *data, char *key, char *transmitted_data) {
    int data_len = strlen(data);
    int key_len = strlen(key);
    strcpy(transmitted_data, data);
    for (int i = 0; i < key_len - 1; i++) {
        transmitted_data[data_len + i] = '0';
    }
    transmitted_data[data_len + key_len - 1] = '\0';
    mod2div(transmitted_data, key, data_len + key_len - 1, key_len);
}
int main() {
    char data[100], key[100], transmitted_data[200], received_data[200];
    int i, key_len, error = 0;
    printf("Enter the data: ");
    scanf("%s", data);
    printf("Enter the generated polynomial: ");
    scanf("%s", key);
    key_len = strlen(key);
    encodeData(data, key, transmitted_data);
    printf("CRC: %s\n", transmitted_data + strlen(data));
    printf("Transmitted data: %s\n", transmitted_data);
    printf("Received data: ");
    scanf("%s", received_data);
    mod2div(received_data, key, strlen(received_data), key_len);
    for (i = strlen(received_data) - key_len + 1; i < strlen(received_data); i++) {
        if (received_data[i] == '1') {
            error = 1;
            break;
        }
    }
    if (error) {
        printf("Error detected\n");
    } else {
        printf("No error detected\n");
    }
    return 0;
}
