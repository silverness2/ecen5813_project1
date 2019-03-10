#include "prng.h"

uint32_t lcg_parkmiller(uint32_t *state)
{
    const uint32_t N = 0x000fffff;// 0x7fffffff;
    const uint32_t G = 48271u;

    /*
        Indirectly compute state*G%N.

        Let:
          div = state/(N/G)
          rem = state%(N/G)

        Then:
          rem + div*(N/G) == state
          rem*G + div*(N/G)*G == state*G

        Now:
          div*(N/G)*G == div*(N - N%G) === -div*(N%G)  (mod N)

        Therefore:
          rem*G - div*(N%G) === state*G  (mod N)

        Add N if necessary so that the result is between 1 and N-1.
    */
    uint32_t div = *state / (N / G); // max : 2,147,483,646 / 44,488 = 48,271
    uint32_t rem = *state % (N / G); // max : 2,147,483,646 % 44,488 = 44,487

    uint32_t a = rem * G;       // max : 44,487 * 48,271 = 2,147,431,977
    uint32_t b = div * (N % G); // max : 48,271 * 3,399 = 164,073,129

    return *state = (a > b) ? (a - b) : (a + (N - b));
}
