#include <stdio.h>
#include "midi.h"

int main(int argc, char *argv[]) {
    // Message type string
    const char * name;
    // Currently checked message type
    uint8_t value = 128;
    // Iterate through all possible messages,
    // display message types and channels
    while (value != 0) {
        name = get_midi_msg_type(value);
        printf("%s\n", name);
        value++;
    }
    // Exit normally
    return 0;
}
