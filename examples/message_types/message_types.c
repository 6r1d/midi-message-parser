#include <stdio.h>
#include <stdint.h>
#include "midi.h"

void print_bits(size_t const size, void const * const ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
}

int main(int argc, char *argv[]) {
    int status_byte;
    const char * message_type;

    // Iterate through all possible messages,
    // display status bytes, message types and channels
    for (status_byte = 128; status_byte<=255; status_byte++) {
        message_type = get_midi_msg_type(status_byte);
        print_bits(sizeof(uint8_t), &status_byte);
        printf(" %03d 0x%02x\n", (uint8_t)status_byte, (uint8_t)status_byte);
        printf("%s\n\n", message_type);
        free((char*)message_type);
    }

    return 0;
}
