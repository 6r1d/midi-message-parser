#include <stdio.h>
#include "midi.h"

int main(int argc, char *argv[]) {
   const char * name;
   uint8_t value = 128;
   while (value != 0) {
      name = get_midi_msg_type(value);
      printf("%s\n", name);
      value++;
   }

   return 0;
}
