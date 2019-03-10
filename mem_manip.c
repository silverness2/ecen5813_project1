/*******************************************************************************
 *
 * Copyright (C) 2019 by Shilpi Gupta
 *
 ******************************************************************************/

/*
 * @file mem_manip.c
 * @brief Library definitions for interactive memory manipulaton.
 *
 * @author Shilpi Gupta
 * @date March 11, 2019
 * @version Sprint 3
*/

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free, NULL
#include <string.h>
#include <time.h>
#include "mem_manip.h"
#include "prng.h"

int is_mem_valid(int32_t **words)
{
    if (*words == NULL)
    {
        printf("ERROR: No memory allocated.\n");
        return 0;
    }
    return 1;
}

int is_offset_valid(int word_offset, int total_words)
{
    if (word_offset >= total_words)
    {
        printf("ERROR: Cannot write. Invalid memory location.\n");
        return 0;
    }
    return 1;
}

void alloc_mem(int32_t **words, int total_words)
{
    // Verify memory not already allocated.
    if (*words != NULL)
    {
        printf("alloc_mem(): ERROR: Cannot allocate memory because memory " \
               "already allocated. Please free memory first.\n");
        return;
    }

    // Allocate memory & set all values to 0.
    *words = malloc(total_words * sizeof(int32_t));
    memset(*words, 0, total_words*sizeof(int32_t));

    // Verify success.
    if (*words == NULL)
    {
        printf("alloc_mem(): ERROR: Unable to allocate %d words of memory.\n", \
               total_words);
	return;
    }
    else
    {
        printf("alloc_mem(): Allcoated %d words (%d bytes) of memory.\n", \
               total_words, (total_words * (int32_t)sizeof(int32_t)));
    }
}

void free_mem(int32_t **words, int total_words)
{
    // Free memory.
    if (*words)
    {
        free(*words);
        *words = NULL;
          
        printf("free_mem(): Freed all allocated memory.\n");
    }
    else
    {
        printf("free_mem(): No memory to free.\n");
    }
}

void write_offset(int value, int word_offset, int **words, int total_words)
{
    // Verify memory.
    if (!is_mem_valid(words)) { return; }
    if (!is_offset_valid(word_offset, total_words)) { return; }

    // Write value at offset.
    *(*words + word_offset) = value;
}

void write_address(int value, int32_t *addr, int **words, int total_words)
{
    // Verify memory.
    if (!is_mem_valid(words)) { return; }

    // Write value at address.
    for (int i = 0; i < total_words; i++)
    {
        if (addr == (*words + i))
        {
            *(*words + i) = value;
            return;
        }
    }

    // No matching address found.
    printf("write_address(): ERROR: Invalid memory address (%p) provided. "
           "Valid addresses are:\n", addr);
    show_all_addr(*words, total_words);
}

void invert(int word_offset, int32_t **words, int total_words)
{
    // Verify memory.
    if (!is_mem_valid(words)) { return; }
    if (!is_offset_valid(word_offset, total_words)) { return; }
  
    // Invert. 
    *(*words + word_offset) =~ *(*words + word_offset);
}

void write_offset_pattern(int word_offset, int num_words, int seed, \
                          int32_t **words, int total_words)
{
    // Verify memory.
    if (!is_mem_valid(words)) { return; }
    if (!is_offset_valid(word_offset, total_words)) { return; }

    // Use PRNG to generate a pattern of randome numbers.
    uint32_t seed_u = (uint32_t)seed; 
    uint32_t *state = &seed_u;
    for (int i = 0; i < num_words; i++)
    {
        *state = lcg_parkmiller(state);
        write_offset((int32_t)(*state), word_offset + i, words, total_words);
    }
}

void write_address_pattern(int32_t *addr, int num_words, int seed, \
                           int32_t **words, int total_words)
{
    // Verify memory.
    if (!is_mem_valid(words)) { return; }

    // Use PRNG to generate a pattern of randome numbers.
    uint32_t seed_u = (uint32_t)seed; 
    uint32_t *state = &seed_u;
    for (int i = 0; i < num_words; i++)
    {
        *state = lcg_parkmiller(state);
        write_address((int32_t)(*state), addr + i, words, total_words);
    }
}

void verify_offset_pattern(int word_offset, int num_words, int seed, \
                           int32_t **words, int total_words)
{
    // Verify memory.
    if (!is_mem_valid(words)) { return; }
    if (!is_offset_valid(word_offset, total_words)) { return; }
    if (word_offset + num_words > total_words)
    {
        printf("verify_offset_pattern(): ERROR: Invalid memory location.\n");
        return;
    }

    // Use PRNG to generate a pattern of random numbers.
    uint32_t seed_u = (uint32_t)seed; 
    uint32_t *state = &seed_u;
    for (int i = 0; i < num_words; i++)
    {
        // Check for a match.
        *state = lcg_parkmiller(state);
        if (*state != *(*words + word_offset + i))
        {
            printf("No Match!: ");
        }
        else
        {
            printf("Match!: ");
        }
        printf("seed=%d, word=%d, expected=%d, and actual=%d\n", seed, \
               word_offset + i, *(*words + word_offset + i), *state);
    }
}

void verify_address_pattern(int32_t *addr, int num_words, int seed, \
                            int32_t **words, int total_words)
{
    // Verify memory.
    if (!is_mem_valid(words)) { return; }

    // Use PRNG to generate a pattern of randome numbers.
    uint32_t seed_u = (uint32_t)seed; 
    uint32_t *state = &seed_u;
    for (int i = 0; i < num_words; i++)
    {
        // Verify address exists.
        int found = 0;
        for (int n = 0; n < total_words; n++)
        {
            if ((addr + i) == (*words + n))
            {
                found = 1;
            }
        }
        if (found == 0)
        {
            printf("verify_address_pattern(): ERROR: Address (%p) does not "
                   "exist.\n", (addr + i));
            continue;
        }

        // Check for a match.
        *state = lcg_parkmiller(state);
        if (*state != *(addr + i))
        {
            printf("No Match!: ");
        }
        else
        {
            printf("Match!: ");
        }
        printf("seed=%d, addr=%p, expected=%d, and actual=%d\n", seed, \
               (addr + i), *(addr + i), *state);
    }
}

void show(int word_offset, int num_words, int32_t *words, int total_words)
{
    if (words == NULL)
    {
        printf("show(): ERROR: No memory allocated.\n");
        return;
    }

    if (!is_offset_valid(word_offset, total_words) || 
        (word_offset + num_words) > total_words)
    {
        printf("write(): ERROR: Invalid memory location.\n");
        return;
    }

    for (int i = word_offset; i < word_offset + num_words; i++)
    {
        printf("At word=%d and address=%p, int value=%d and hex value="
               "0x%04x\n", i, (words + i), *(words + i), *(words + i));
    }
}

void show_all_addr(int32_t *words, int total_words)
{

    if (words == NULL)
    {
        printf("show_all_addr(): ERROR: No memory allocated.\n");
        return;
    }

    for (int i = 0; i < total_words; i++)
    {
        printf("At word=%d, address=%p\n", i, (words + i));
    }
}
