#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bit_ops.h"
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    // Get the bits originally in position 0, 2, 3, and 5
    unsigned bit0 = get_bit((unsigned)*reg, 0);
    unsigned bit2 = get_bit((unsigned)*reg, 2);
    unsigned bit3 = get_bit((unsigned)*reg, 3);
    unsigned bit5 = get_bit((unsigned)*reg, 5);
    // Calculate the new bit
    unsigned new_bit = bit0 ^ bit2 ^ bit3 ^ bit5;
    // Shift the register to the right
    *reg = *reg >> 1;
    // Set the new bit in position 15
    set_bit((unsigned *)reg, 15, new_bit);
}
