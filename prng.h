/*
 * Attribtion: https://en.wikipedia.org/wiki/Lehmer_random_number_generator
 */

#ifndef PRNG_H
#define PRNG_H

#include <stdint.h> // for uint32_t

uint32_t lcg_parkmiller(uint32_t *state);

#endif
