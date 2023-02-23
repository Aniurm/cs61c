#include <stdio.h>
#include "bit_ops.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // move the nth bit to the least significant position
    x = x >> n;
    // mask off all but the least significant bit
    return x & 1;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // make a mask to clear the nth bit of x
    unsigned mask = ~(1 << n);
    // clear the nth bit of x
    *x = *x & mask;
    // make a mask to set the nth bit of x to v
    mask = (v << n);
    // set the nth bit of x to v
    *x = *x | mask;
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // get the nth bit of x
    unsigned nthBit = get_bit(*x, n);
    // flip the nth bit
    nthBit = nthBit ^ 1;
    // set the nth bit of x to the flipped bit
    set_bit(x, n, nthBit);
}