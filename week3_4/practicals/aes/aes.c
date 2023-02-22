#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

void mix_columns(uint8_t *in) {
    uint8_t copy[4];
    uint8_t multiplied_2[4];
    uint8_t h;

    for (uint8_t i = 0; i < 4; i++) {
        copy[i] = in[i];

        h = (in[i] >> 7) & 1;          // If the high bit is set, h is set.
        multiplied_2[i] = in[c] << 1;  // Use shift to multiply
        multiplied_2[i] ^= h * 0x1B;   // XOR for the Galois field
    }

    in[0] = multiplied_2[0] ^ copy[3] ^ copy[2] ^ multiplied_2[1] ^ copy[1];
    in[1] = multiplied_2[1] ^ copy[0] ^ copy[3] ^ multiplied_2[2] ^ copy[2];
    in[2] = multiplied_2[2] ^ copy[1] ^ copy[0] ^ multiplied_2[3] ^ copy[3];
    in[3] = multiplied_2[3] ^ copy[2] ^ copy[1] ^ multiplied_2[0] ^ copy[0];
}
